
# imported modules
import pdelab as plab
import pylab as math
from pylab import linalg as LA

######################################
PROG_NAME		= 'diffnorm'
SIM_NAME1		= 'lin_boussinesq'
SIM_NAME2		= 'lin_sw'

DIR_NAME1		= 'diffnorm1/'
DIR_NAME2		= 'diffnorm2/'

FINAL_TIME		= 150
RECORD_SIM		= 1

NUM_DATA_POINTS	= 5
#######################################
	
plab.add("# DIFFNORM ###############################################")
plab.add("# Simulates lin_boussinesq and lin_sw over several iterations")
plab.add("# At each iteration, the mu is reduced and the norm ")
plab.add("# of the difference is computed")
plab.add("# #######################################################")
plab.add(" ")
	
plab.set("output",SIM_NAME1,DIR_NAME1)
plab.set("output",SIM_NAME2,DIR_NAME2)
plab.set("filename",SIM_NAME1,SIM_NAME1)
plab.set("filename",SIM_NAME2,SIM_NAME2)
	
numIter = math.arange(NUM_DATA_POINTS)
plott = math.zeros(NUM_DATA_POINTS)
for i in numIter: 
	plab.sim(SIM_NAME1,FINAL_TIME,RECORD_SIM)
	plab.sim(SIM_NAME2,FINAL_TIME,RECORD_SIM)
	plab.execute(PROG_NAME)
	
	array1,array2 = plab.readDatFile(DIR_NAME1 + SIM_NAME1 + str(i))
	array3,array4 = plab.readDatFile(DIR_NAME2 + SIM_NAME2 + str(i))
	plott[i] = LA.norm(array4-array2)

math.plot(plott)
math.show()
	

