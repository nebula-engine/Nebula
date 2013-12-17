#include <glutpp/free.h>

#include <glutpp/gui/object/button.h>

void glutpp::gui::object::button::draw()
{
	draw_2d_quad( x_, y_, w_, h_ );
}






