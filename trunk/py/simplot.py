#!/usr/local/bin/python2.6

import pdelab as plab

######################################
PROG_NAME		= 'simplot'

SIM_NAME1		= 'advec'
RECORD_SIM		= 1

SKIP_FRAME		= 1
START_TIME		= 0
FINAL_TIME		= 0
SAVE			= 0
#######################################

plab.add("# SIMPLOT ###########################################")
plab.add("# runs a simulation and plots the result in gnuplot")
plab.add("#")
plab.add("# ################################################")
plab.add(" ")

plab.sim(SIM_NAME1, FINAL_TIME,RECORD_SIM)
plab.script(SIM_NAME1,SKIP_FRAME,START_TIME,FINAL_TIME,SAVE)
plab.gplot(SIM_NAME1)
plab.execute(PROG_NAME)
