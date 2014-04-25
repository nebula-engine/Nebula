#include <string.h>
#include <algorithm>

#include <tinyxml2.h>

#include <math/xml.hpp>

#include <gru/gui/object/object.hpp>

glutpp::gui::object::object::object():
	x_(0.0),
	y_(0.0),
	w_(0.3),
	h_(0.3),
	font_color_(math::Color::magenta),
	bg_color_(0,0,0,0),
	label_length_(1),
	label_(NULL)
{
	label_ = new char[1];
	label_[0] = '\0';
}
void glutpp::gui::object::object::i(int ni) {
	i_ = ni;
}
glutpp::window::window_s get_window() {
	printf("%s\n", __PRETTY_FUNCTION__);
	printf("not yet supported");
	abort();
}
void	glutpp::gui::object::object::load_xml(tinyxml2::XMLElement* element) {
	
	x_ = math::Xml::parse_float<double>(element->FirstChildElement("x"),0);	
	y_ = math::Xml::parse_float<double>(element->FirstChildElement("y"),0);
	w_ = math::Xml::parse_float<double>(element->FirstChildElement("w"),0);
	h_ = math::Xml::parse_float<double>(element->FirstChildElement("h"),0);

	auto e = element->FirstChildElement("label");
	if(e) {
		char const * label = e->GetText();
		set_label(label);
	}
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

	font_color_ = math::Color::green;

	return 1;
}



