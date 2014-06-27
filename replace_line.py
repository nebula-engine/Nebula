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

def sub(pattern_str, replacement_str, text):
	
	tail = text
	head = ''	

	m = re.search(pattern_str, tail)
	
	while(m):
		print tail[m.start(0):m.end(0)]
		
		head += tail[:m.start(0)]
		head += replacement_str
		
		tail = tail[m.end(0):]

		m = re.search(pattern_str, tail)

	return text	
	
def replace(filename):
	with open(filename,'r') as f:
		otext = f.read()
	
	text = otext
	
	
	
        text = re.sub("/Util/","/util/",text)
	
	#text = re.sub("NEBULA_ACTOR_BASE_FUNC","if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, \"neb core actor\", debug) << __PRETTY_FUNCTION__", text)
	
	
	if(text != otext):
		print filename
		#print text
		with open(filename,'w') as f:
			f.write(text)





for f in glob('nebula/core/include'): replace(f)
for f in glob('nebula/core/src'): replace(f)
for f in glob('nebula/core/test'): replace(f)

for f in glob('nebula/gfx/include'): replace(f)
for f in glob('nebula/gfx/src'): replace(f)
for f in glob('nebula/gfx/test'): replace(f)

for f in glob('nebula/physx/include'): replace(f)
for f in glob('nebula/physx/src'): replace(f)
for f in glob('nebula/physx/test'): replace(f)

for f in glob('nebula/final/include'): replace(f)
for f in glob('nebula/final/src'): replace(f)
for f in glob('nebula/final/test'): replace(f)


