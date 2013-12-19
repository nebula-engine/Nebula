#include <string.h>
#include <algorithm>

#include <tinyxml2.h>

#include <math/free.h>

#include <glutpp/gui/object/object.h>

glutpp::gui::object::object::object():
	x_(0.0),
	y_(0.0),
	w_(0.3),
	h_(0.3),
	font_color_(math::magenta),
	label_(NULL),
	label_length_(1)
{
	label_ = new char[1];
	label_[0] = '\0';
}
std::shared_ptr<glutpp::window>	get_window() {
	printf("%s\n", __PRETTY_FUNCTION__);
	printf("not yet supported");
	exit(0);
}
int	glutpp::gui::object::object::load_xml(tinyxml2::XMLElement* element) {
	
	x_ = math::xml_parse_float(element->FirstChildElement("x"));	
	y_ = math::xml_parse_float(element->FirstChildElement("y"));
	w_ = math::xml_parse_float(element->FirstChildElement("w"));
	h_ = math::xml_parse_float(element->FirstChildElement("h"));
	
	auto e = element->FirstChildElement("label");
	assert(e);
	char const * label = e->GetText();
	
	set_label(label);
	
}
void	glutpp::gui::object::object::set_label( char const * cstr )
{
	if(label_ != NULL) delete[] label_;

	size_t len = strlen(cstr);
	
	label_ = new char[len+1];
	
	memcpy(label_, cstr, len);
	label_[len] = '\0';
}
int	glutpp::gui::object::object::mouse_button_fun(int,int,int)
{
	printf("%s\n", __PRETTY_FUNCTION__);

	font_color_ = math::green;

	return 1;
}



