

#include <glutpp/gui/object/object_factory.h>
#include <glutpp/gui/object/edittext.h>
#include <glutpp/gui/object/terminal.h>

std::shared_ptr<glutpp::gui::object::object>    glutpp::gui::object::object_factory::create(tinyxml2::XMLElement* element) {

	assert(element);
	
	std::shared_ptr<glutpp::gui::object::object> object;
	
	char const * buf = element->Attribute("type");
	assert(buf);
	
	if(strcmp(buf, "textview") == 0)
	{
		object.reset(new glutpp::gui::object::textview);
	}
	else if(strcmp(buf, "edittext") == 0)
	{
		object.reset(new glutpp::gui::object::edittext);
	}
	else if(strcmp(buf, "terminal") == 0)
	{
		object.reset(new glutpp::gui::object::terminal);
	}
	else
	{
		printf("object type not recognized %s\n",buf);
		abort();
	}
	
	object->load_xml(element);
	
	return object;
}



