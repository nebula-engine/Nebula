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
	

        text = re.sub("Nebula/Actor/","Nebula/core/actor/",text)
        text = re.sub("Nebula/Shape/","Nebula/core/shape/",text)
   
        text = re.sub("Nebula/Graphics/","Nebula/gfx/",text)
        text = re.sub("Nebula/Util/","Nebula/util/",text)
        text = re.sub("Nebula/Core/","Nebula/core/",text)
        text = re.sub("Nebula/Math/","Nebula/math/",text)
        text = re.sub("Nebula/App/","Nebula/app/",text)
        text = re.sub("Nebula/Message/","Nebula/message/",text)
        text = re.sub("Nebula/Network/","Nebula/net/",text)

        text = re.sub("Nebula/Types.hh","Nebula/util/decl.hpp",text)
        text = re.sub("Nebula/gfx/Types.hh","Nebula/gfx/util/decl.hpp",text)
 
        text = re.sub("Nebula/Signals.hh","Nebula/gfx/window/util/signals.hpp",text)
    
	text = re.sub("Nebula/gfx/window/Util/","Nebula/gfx/window/util/",text)
	text = re.sub("Nebula/gfx/Window/","Nebula/gfx/window/",text)

	text = re.sub("Nebula/gfx/Light/","Nebula/core/light/",text)

        text = re.sub("neb::Filter::Filter","phx::filter::filter",text)
        text = re.sub("phx::filter::filter::Type","phx::filter::filter::type",text)

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



