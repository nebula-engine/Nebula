

#include <gru/gui/object/object_factory.hpp>
#include <gru/gui/object/edittext.hpp>
#include <gru/gui/object/terminal.hpp>

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



