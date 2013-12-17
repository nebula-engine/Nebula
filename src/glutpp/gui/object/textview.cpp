#include <stdio.h>
#include <string.h>

#include <GLFW/glfw3.h>

#include <glutpp/free.h>

#include <glutpp/gui/object/textview.h>

glutpp::gui::object::textview::textview():
	label_pos_(0)
{
}
void	glutpp::gui::object::textview::clear_label()
{
	delete[] label_;

	label_ = new char[16];

	memset( (void *)label_, '\0', 16 );

	label_pos_ = 0;
}
void	glutpp::gui::object::textview::draw()
{
	//printf("%s\n",__PRETTY_FUNCTION__);

	float sx = 1.0/600.0;
	float sy = 1.0/600.0;

	draw_text(x_, y_, sx, sy, label_);
}


