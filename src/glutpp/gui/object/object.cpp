#include <string.h>
#include <algorithm>

#include <glutpp/gui/object/object.h>

glutpp::gui::object::object::object():
	x_(0),
	y_(0),
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

