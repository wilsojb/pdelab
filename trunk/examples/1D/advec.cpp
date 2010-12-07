
#include "advec.h"
#include <sstream>
#include <cmath>
using std::stringstream;
using std::exp;

#define U (*_U)
#define U1 (*_U1)

advec::advec() : Example() {
	EQUATION =	"advec";
	PATH =		"dat/1D/" + EQUATION + "/";
	FILENAME =	"ADVEC";
	TITLE =		"Advection Equation";
}

advec::~advec() {
	deleteDynamicVars();
}

void advec::deleteDynamicVars() {
	delete _U;
	delete _U1;
}

void advec::createStaticVars() {
	LENGTH =			1;		//changing this might effect inital conditions
	NX =				256;
	MAX_TIME =			1000;
	CFL =				.5;
	HEIGHT =			.1;
	AMP =				.01;
	START_X =			.5;
	GRAVITY_CONSTANT =	10;
}

void advec::createDerivedVars() {
	DX = LENGTH/NX;
	DT = CFL*DX;
}

void advec::createDynamicVars() {
	_U = new vector<double>(NX);
	_U1 = new vector<double>(NX);
	VAR1_VECT = _U1;
}

void advec::createInitialData(bool store) {
	double offset = LENGTH*START_X;
	double x;
	double k=10;
	for (unsigned int j=0;j<NX;j++) {
		x = (j+0.5)*(DX);
		// Gaussian and fat delta initials
		// amplitude 0.02
		U[j] = AMP*exp(-100*((x-offset)*(x-offset)));
		//U[j] = AMP*(tanh((0.55-x)*1000)+ tanh((x-0.45)*1000));
	}
	if (store) record(-1);
}


void advec::record(int t) {
	stringstream ss;
	
	t++;
	ss << t;
	string file = PATH + FILENAME + ss.str() + ".dat";
	OUTFILE.open(&file[0]);
	for (unsigned int j=0;j<NX;j++) {
		float x = (j+0.5)*DX;
		OUTFILE<<x<<"\t"<<U[j]+HEIGHT<<endl;
	}
	OUTFILE.close();
}


void advec::run(int t) {
	// Forward (time)
	// Upwind/Backward (space)
	
	//solving for u
	for (unsigned j=1;j<NX;j++) {
		U1[j] = U[j] - (DT/DX)*(U[j] - U[j-1]);
	}
	U1[0] = U1[NX-1];
	
	// Update Meshes
	for (unsigned j=0;j<NX;j++) {
		U[j] = U1[j];
	}
}


void advec::definePlotVars(int start,int stop,int skip,int save) {
	SCRIPT_START = start;
	SCRIPT_STOP = stop;
	SCRIPT_SKIP = skip;
	SCRIPT_SAVE = save;
}

void advec::genGnuplotScript() {
	double lower = HEIGHT - 3*AMP;
	double upper = HEIGHT + 3*AMP;
	
	
	string file = "gp/" + EQUATION + ".gp";
	OUTFILE.open(&file[0]);
	OUTFILE << "reset\n";
	OUTFILE << "set term X11\n"
	<< "set style data lines\n"		
	
	<< "set title '"<<TITLE<<" (t=0)'\n"
	<< "set xlabel 'x'\n"
	<< "set ylabel 'y'\n"
	<< "set xrange [0: "<<LENGTH<<"]\n"
	<< "set yrange ["<<lower<<":"<<upper<<"]\n"
	<< "set xtics 0,.1,"<<LENGTH<<"\n";
	
	if (SCRIPT_SAVE) OUTFILE << "set term gif\n";
	
	unsigned i=SCRIPT_START;;
	while (i<=SCRIPT_STOP) {
		if (SCRIPT_SAVE) OUTFILE << "set output '" << PATH << "plot" << i << ".gif'\n";
		
		OUTFILE	<< "set title '"<<TITLE<<" (t="<<i<<")'\n"
		<< "plot '" << PATH <<  FILENAME << "0.dat' using 1:2,'" << PATH
		<< FILENAME << i << ".dat' using 1:2 \n";
		
		if (!SCRIPT_SAVE) OUTFILE<<"pause "<<7*DT<<"\n";	
		
		i = i + SCRIPT_SKIP;	
	}
	
	OUTFILE << "reset\n";
	OUTFILE	<< "set term X11\n";
	OUTFILE.close();
	
	
}
