#include <tinyxml/tinyxml.h>

#include <string>
#include <algorithm>

#include <glutpp/gui/object/object.h>
#include <glutpp/gui/object/edittext.h>

#include <glutpp/gui/layout.h>

void	glutpp::gui::layout::init()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
	std::shared_ptr<GUL::object::edittext> object(new GUL::object::edittext);
	
	objects_[0] = object;
}
void	glutpp::gui::layout::load_xml( std::string file_name )
{

}
void	glutpp::gui::layout::Display()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	//jess::clog << "objects_.size()=" << objects_.map_.size() << std::endl;

	for(auto it = objects_.begin(); it != objects_.end(); ++it)
		(*it).second->Display();

}

