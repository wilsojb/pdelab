
### Overview
An object oriented framework for solving and analyzing PDEs. This project grew organically while I worked (read: toiled) on my graduate degree. The goal of the framework was to abstract away the mechanics and other "lower level" code needed to solve PDEs so the researcher can spend more time focusing on their solver (i.e. their "business logic"). 

### Key Features
* **Homegrown solvers**
* **Graphing Utilites**
* **CLI**
* **Examples**

### Installation

````bash
bower install auth0-angular
````

### TL;DR: Quick start guide

The easiest way to get started is to follow the installation guide and then run a test. In a terminal, type

````bash
$ pdelab
pdelab> sim advec 2000
pdelab> script advec 1 0 2000 0
pdelab> gnuplot
gnuplot> load 'gp/advec.gp'
gnuplot> exit
pdelab> exit
$
````

This should simulate and display the advection equation.

### Instruction scripts
Create the following script under the name "pde/foo.pde"...

````bash
# This file will solve the advection equation using finite
# differencing techniques and will plot the resulting
# time series in gnuplot. 500 timesteps are calculated.

# This file will also set an instruction to calculate the norm
# of the solution as a function of time. It will store the
# resulting time series in normdata/advec.dat

set norm advec normdata/ 
sim advec 500 
script advec 1 0 500 0 
gnuplot -persist "gp/advec.gp'
````

then run the set of instructions from a terminal window...

````bash
$ pdelab
pdelab> load foo
````

This runs a simulation, creates a file that gnuplot can read, calculates norms, and plots the results. All that as needed from the researcher to get this working was Example.h and Example.cpp which contains the numerical algorithm for solving the advection equation. 

More complicated analysis is possible using some of the other Instructions (see diffnorm.py) or if there is a need for one
that doesn't exist, you can always make a new one!


### Author

wilsojb@gmail.com





