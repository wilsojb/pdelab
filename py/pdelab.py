
import os
import numpy as np


dat_path = "dat/"
dat_suffix = ".dat"

content = []

def add(next):
	content.append(next)
	content.append("\n")
	
def makeFile(f):	
	with open(f,"w") as f:
		f.write("".join(content))
	
def execute(f):
	f = "pde/" + f + ".pde"
	makeFile(f)
	os.system("make all")
	os.system("pdelab " + f)
	del content[:]
	
def sim(s,t,r):
	add("sim " + s + " " + str(t) + " " + str(r))
	
def script(s,k,t,f,v):
	add("script " + s + " " + str(k) + " " + str(t) + " " + str(f) + " " + str(v))

def script_2VARS(s,k,t,f,v):
	add("script2 " + s + " " + str(k) + " " + str(t) + " " + str(f) + " " + str(v))

def gplot(s):
	add("gnuplot -persist 'gp/"+ s +".gp'")

def set(o,s,d):
	add("set "+ o + " " + s + " " + str(d))
	

def readDatFile(f):
	f = dat_path + f + dat_suffix
	ret1 = []
	ret2 = []
	with open(f,"r") as f:
		for line in f:
			l = line.split()
			ret1.append(float(l[0]))
			ret2.append(float(l[1]))
			
	return np.array(ret1),np.array(ret2)










