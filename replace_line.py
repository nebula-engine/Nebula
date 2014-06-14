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
	
	text = re.sub("namespace Message","namespace message",text)
	text = re.sub("neb::Message::","neb::message::",text)
	
	text = re.sub("class Local","class local",text)
	text = re.sub("::Local","::local",text)


	text = re.sub("namespace RigidActor","namespace rigidactor",text)
	text = re.sub("neb::core::actor::RigidActor","neb::core::actor::rigidactor",text)

	text = re.sub("namespace RigidBody","namespace rigidbody",text)
	text = re.sub("neb::core::actor::RigidBody","neb::core::actor::rigidbody",text)

	text = re.sub("namespace RigidDynamic","namespace rigiddynamic",text)
	text = re.sub("neb::core::actor::RigidDynamic","neb::core::actor::rigiddynamic",text)



        text = re.sub("namespace GUI","namespace gui",text)
        text = re.sub("namespace Object","namespace object",text)

        
        text = re.sub("Neb::","neb::",text)
	text = re.sub("neb::Graphics::","neb::gfx::",text)
	text = re.sub("neb::Core::","neb::core::",text)
	text = re.sub("neb::core::actor::Actor","neb::core::actor::actor",text)
        text = re.sub("neb::gfx::GUI::","neb::gfx::gui::",text)
        text = re.sub("neb::gfx::gui::Object::","neb::gfx::gui::object::",text)
        
        
	
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



