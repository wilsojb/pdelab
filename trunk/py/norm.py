
import pdelab as plab
import pylab as math

######################################
PROG_NAME		= 'norm'

SIM_NAME1		= 'advec'
FINAL_TIME		= 2000
RECORD_SIM		= 0

INSTRUCT_NAME1	= 'norm'
#######################################

plab.add("# NORM ###########################################")
plab.add("# Calculates the norm of the solution as a function")
plab.add("# of time and plots the result")
plab.add("#")
plab.add("# ################################################")
plab.add(" ")

plab.set(INSTRUCT_NAME1, SIM_NAME1, PROG_NAME)
plab.sim(SIM_NAME1, FINAL_TIME,RECORD_SIM)
plab.execute(PROG_NAME)

list1,list2 = plab.readDatFile(PROG_NAME + "/" + SIM_NAME1)

math.plot(list2)
math.show()
	