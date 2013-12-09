#include <tinyxml/tinyxml.h>

#include <string>
#include <algorithm>

#include <GUL/object/object.h>
#include <GUL/object/edittext.h>

#include <GUL/layout.h>

void	GUL::layout::init()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
	std::shared_ptr<GUL::object::edittext> object(new GUL::object::edittext);
	
	objects_[0] = object;
}
void	GUL::layout::load_xml( std::string file_name )
{

}
void	GUL::layout::Display()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	//jess::clog << "objects_.size()=" << objects_.map_.size() << std::endl;

	for(auto it = objects_.begin(); it != objects_.end(); ++it)
		(*it).second->Display();

}
