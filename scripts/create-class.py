#!/usr/bin/python2

import sys

srcDir = "src"
buildDir = "build"

# check arguments
if len(sys.argv) != 3:
	print "usage: script <classname> <superclass>"
	sys.exit (-1)

classname, supername = sys.argv[1:]

lowername = classname.lower ()
uppername = classname.upper ()
cpath = srcDir+"/"+lowername+".cpp"
hpath = srcDir+"/"+lowername+".h"
incpath = lowername+".h"
guardname = uppername+"_H"

superlower = supername.lower ()
superinc = superlower+".h"

fs = open (hpath, "w")
fs.write ("""
#ifndef """+guardname+"""
#define """+guardname+"""
"""+("\n#include \""+superinc+"\"\n" if supername!="" else "")+"""
class """+classname+(" : public "+supername if supername!="" else "")+"""
{
public:
	"""+classname+""" ();
	~"""+classname+""" ();
};

#endif

""")
fs.close ()

fs = open (cpath, "w")
fs.write ("""
#include \""""+incpath+"""\"

"""+classname+"::"+classname+""" ()
{
}

"""+classname+"::~"+classname+""" ()
{
}

""")
fs.close ()
