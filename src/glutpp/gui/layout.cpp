#include <tinyxml/tinyxml.h>

#include <string>
#include <algorithm>

#include <glutpp/gui/object/object.h>
#include <glutpp/gui/object/edittext.h>

#include <glutpp/gui/layout.h>

void	glutpp::gui::layout::init()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
	glutpp::gui::object::edittext* object(new glutpp::gui::object::edittext);
	
	objects_.push(object);
}
void	glutpp::gui::layout::load_xml( std::string file_name )
{

}
void	glutpp::gui::layout::Display()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	//jess::clog << "objects_.size()=" << objects_.map_.size() << std::endl;

	
	
	objects_.foreach(&glutpp::gui::object::object::Display);
}



