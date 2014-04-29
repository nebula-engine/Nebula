

#include <gru/gui/object/object_factory.hpp>
#include <gru/gui/object/edittext.hpp>
#include <gru/gui/object/terminal.hpp>

std::shared_ptr<glutpp::gui::object::object>    glutpp::gui::object::object_factory::create(boost::archive::xml_iarchive & ar) {

	std::shared_ptr<glutpp::gui::object::object> object;
	
//	std::string type;

//	ar >> type;
	/*
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
	*/
//	ar >> object;
	
	return object;
}



