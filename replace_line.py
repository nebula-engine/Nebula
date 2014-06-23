#!/usr/bin/env python

import re
import os
import sys

def glob(path):
	for root, dirnames, filenames in os.walk(path):
		for f in filenames:
			if '.hpp' in f:
				yield os.path.join(root, f)
			if '.hh' in f:
				yield os.path.join(root, f)
			if '.cpp' in f:
				yield os.path.join(root, f)
			if '.cc' in f:
				yield os.path.join(root, f)

def replace(filename):
	with open(filename,'r') as f:
		otext = f.read()
	
	text = otext
	
        text = re.sub("Nebula/core/TimeStep.hpp","gal/std/timestep.hpp",text)
        text = re.sub("neb::core::TimeStep","gal::std::timestep",text)

	if(text != otext):
		print filename
		with open(filename,'w') as f:
			f.write(text)





for f in glob('include'):
	replace(f)
for f in glob('src'):
	replace(f)
for f in glob('test'):
	replace(f)

for f in glob('PhysX/include'):
	replace(f)
for f in glob('PhysX/src'):
	replace(f)
for f in glob('PhysX/test'):
	replace(f)



