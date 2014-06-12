#!/usr/bin/env python

import re
import os
import sys

def glob(path):
	for root, dirnames, filenames in os.walk(path):
		for f in filenames:
			if '.hpp' in f:
				print os.path.join(root, f)
			if '.hh' in f:
				print os.path.join(root, f)
			if '.cpp' in f:
				print os.path.join(root, f)
			if '.cc' in f:
				print os.path.join(root, f)

def replace(filename):
	with open(filename,'r') as f:
		text = f.read()
		
	text = re.sub("([\w:]+)_s([\s\)])","sp::shared_ptr<\\1>\\2",text)
	
	with open(filename,'w') as f:
		f.write(text)


replace(sys.argv[1])



glob('include')
glob('src')

