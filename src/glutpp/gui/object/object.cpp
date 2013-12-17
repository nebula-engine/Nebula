#include <string.h>
#include <algorithm>

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
void	glutpp::gui::object::object::set_label( char const * cstr )
{
	if(label_ != NULL) delete[] label_;

	size_t len = strlen(cstr);
	
	label_ = new char[len];
	
	memcpy(label_, cstr, len);
}
int	glutpp::gui::object::object::mouse_button_fun(int,int,int)
{
	printf("%s\n", __PRETTY_FUNCTION__);

	font_color_ = math::green;

	return 1;
}



