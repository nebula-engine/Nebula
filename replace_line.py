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
	
	text = re.sub("([\w:]+)_s([\s\),])","sp::shared_ptr<\\1>\\2",text)
	#text = re.sub("neb::Actor","neb::core::Actor",text)
	#text = re.sub("namespace Actor","namespace actor",text)
	#text = re.sub("::Actor::","::actor::",text)
	text = re.sub("neb::Graphics::","neb::gfx::",text)
	text = re.sub("neb::Core::","neb::core::",text)
	text = re.sub("neb::core::actor::Actor","neb::core::actor::actor",text)
	


	
	if(text != otext):
		print filename
		with open(filename,'w') as f:
			f.write(text)





for f in glob('include'):
	replace(f)
for f in glob('src'):
	replace(f)


