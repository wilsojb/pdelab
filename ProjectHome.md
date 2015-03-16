### Overview ###

---


pdelab is a project that has been developing for over a year with the goal of defining an environment where the numerical solutions to ODEs and PDEs can be solved and analyzed seamlessly.  I am using this framework to complete my master's thesis on numerical solutions to the boussinesq equations.  Please see Downloads for current source code and Wiki for further information about installation, example usage, etc.  If you have any problems with the software, please post a comment on the google group page (see Contact Info).

The philosophy of pdelab is that simulations can be solved, modified, and analyzed through a simple user interface.  The idea is to write the solution to a ODE/PDE in an easily adaptable framework ([Example](Example.md)).  By doing this, you expose your code to a variety of analytic tools, graphical plug-ins, and data management software.  For example, if you created the following file, called "pde/foo.pde", with file contents,

```
----- beginning of file --------

# FOO ######################################
# This file will solve the advection equation using finite
# differencing techniques and will plot the resulting
# time series in gnuplot.  500 timesteps are calculated.
#
#This file will also set an instruction to calculate the norm
#of the solution as a function of time.  It will store the 
#resulting time series in normdata/advec.dat 
#
# Files created:  normdata/advec.dat
############################################

set norm advec normdata/
sim advec 500
script advec 1 0 500 0
gnuplot -persist "gp/advec.gp'


------end of file ----------
```

then you can run this file by simply starting the pdelab terminal and typing,

```
pdelab > load foo
```

Looking at the comments in the file, this appears to perform a few different tasks.  It runs a simulation, creates a file that gnuplot can read, calculates norms, and plots the results.  However, all that was needed to get this file working was the creation of an [Example](Example.md), which is just a .h and .cpp file containing the numerical algorithm for solving the advection equation.

More complicated analysis is possible using some of the other [Instruction](Instruction.md)s (see diffnorm.py) or if there is a need for one that doesn't exist, you can always make a new one!


The easiest way to get started is to download the .tgz and follow the instructions found in the install file.  Then you can run a simple test.  In Bash, type

```
$> pdelab
pdelab > sim advec 2000
pdelab > script advec 1 0 2000 0
pdelab > gnuplot
gnuplot> load 'gp/advec.gp'
gnuplot> exit
pdelab > exit
$>
```

This should simulate and display the advection equation.


### Contact Info ###

---


pdelab-discuss@googlegroups.com

wilsojb@gmail.com