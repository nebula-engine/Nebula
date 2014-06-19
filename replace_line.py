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
	
	text = re.sub("namespace px","namespace phx",text)
	text = re.sub("px::","phx::",text)
	
	text = re.sub("namespace Message","namespace message",text)
	text = re.sub("neb::Message::","neb::message::",text)

	text = re.sub("namespace Shape","namespace shape",text)
	text = re.sub("neb::Shape::","neb::core::shape::",text)


	text = re.sub("class Base","class base",text)
	text = re.sub("::Base","::base",text)

        text = re.sub("class Box","class box",text)
	text = re.sub("::Box","::box",text)

	text = re.sub("class Local","class local",text)
	text = re.sub("::Local","::local",text)

	text = re.sub("class Parent","class parent",text)
	text = re.sub("::Parent","::parent",text)

	text = re.sub("class Cast","class cast",text)
	text = re.sub("::Cast","::cast",text)

	text = re.sub("namespace GUI","namespace gui",text)
	text = re.sub("neb::gfx::GUI::","neb::gfx::gui::",text)

	text = re.sub("namespace Layout","namespace layout",text)
	text = re.sub("neb::gfx::gui::Layout::","neb::gfx::gui::layout::",text)


	text = re.sub("namespace Context","namespace context",text)
	text = re.sub("neb::gfx::Context::","neb::gfx::context::",text)

	text = re.sub("namespace Util","namespace util",text)
	text = re.sub("::Util::","::util::",text)

	text = re.sub("namespace App","namespace app",text)
	text = re.sub("::App::","::app::",text)

	text = re.sub("namespace Window","namespace window",text)
	text = re.sub("::Window::","::window::",text)

	text = re.sub("namespace Scene","namespace scene",text)
	text = re.sub("neb::Scene::","neb::scene::",text)
	text = re.sub("neb::message::Scene::","neb::message::scene::",text)

	text = re.sub("neb::scene::","neb::core::scene::",text)

	text = re.sub("namespace RigidActor","namespace rigidactor",text)
	text = re.sub("neb::core::actor::RigidActor","neb::core::actor::rigidactor",text)

	text = re.sub("namespace RigidStatic","namespace rigidstatic",text)
	text = re.sub("::RigidStatic","::rigidstatic",text)

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
for f in glob('PhysX/test'):
	replace(f)



