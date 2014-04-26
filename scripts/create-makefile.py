#!/usr/bin/python2

import os
import os.path
import re

srcDir = "src"
buildDir = "build"

class Module:

	def __init__ (self, name, depFiles):
	
		self.name = name
		self.depFiles = depFiles
		self.srcPath = srcDir+"/"+self.name+".cpp"
		self.objPath = buildDir+"/"+self.name+".o"
	
	def __str__ (self):
	
		return "<"+self.name+"> depends on "+str(self.depFiles)
	
	def __repr__ (self):
	
		return str (self)

def scanDeps (fileName, found = None):

	if found is None:
		found = []
	
	lines = file (srcDir+"/"+fileName).read ().split ("\n")
	for line in lines:
		match = re.match ("[ \t]*#include[ \t]*\"([^\"]+)\"", line)
		if match is not None:
			newFileName = match.group (1)
			if newFileName not in found:
				found.append (srcDir+"/"+newFileName)
				scanDeps (newFileName, found)
	
	return found

execfile ("Project")

CPP = "g++"
modules = []

for fileName in os.listdir (srcDir):
	if fileName.endswith (".cpp"):
		modName = fileName[:-4]
		modDeps = scanDeps (fileName)
		module = Module (modName, modDeps)
		modules.append (module)

target = buildDir+"/"+projectName

outf = open ("Makefile", "w")

outf.write (
""".PHONY : all, rebuild, clean
all : """+target+"""
rebuild : clean all
clean :
	-rm """+buildDir+"""/*
""")

outf.write (target+" : "+" ".join ([a.objPath for a in modules])+"\n")
outf.write (
	"\t"+CPP+" -o "+target+" "+
	" ".join([a.objPath for a in modules])+" "+
	" ".join(["-l"+lib for lib in libs])+"\n"
)

for module in modules:
	outf.write (module.objPath+" : "+module.srcPath+" "+" ".join (module.depFiles)+"\n")
	outf.write (
		"\t"+CPP+" -o "+module.objPath+" -c "+module.srcPath+" -Wno-write-strings\n"
	)

outf.close ()

