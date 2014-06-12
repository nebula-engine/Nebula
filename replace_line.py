#!/usr/bin/env python

import re
import sys

pat = re.compile("([\w:]+)_s\s")

with open(sys.argv[1]) as f:
	text = f.read()
		
	m = re.sub("([\w:]+)_s\s","sp::shared_ptr<\\1>",text)
	print m



