#include <string.h>

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
void	glutpp::gui::object::textview::Display()
{
	//jess::clog << NEB_FUNCSIG << std::endl;

	GRU::draw_text( x_, y_, label_ );
}
int	glutpp::gui::object::textview::handle_key(__u16 code, __s32 value)
{
	if(value==1)
	{
		return handle_key_down(code);
	}
	else if(value==0)
	{
		return handle_key_up(code);
	}
	
	return 1;
}
int	glutpp::gui::object::textview::handle_key_down(__u16 code)
{

	switch(code)
	{
		case KEY_BACKSPACE:
			if ( label_pos_ > 0 )
			{
				--label_pos_;
				memset( (void *)( label_ + label_pos_ ), '\0', 1 );
			}
			return 1;
		case KEY_A:
		case KEY_Z:
			if ( label_pos_ < label_length_ )
			{
				++label_pos_;
				//memset( (void *)( label_ + label_pos_ ), k, 1 );
			}
			return 1;
		case KEY_ENTER:
			handle_enter();
			return 1;
	}
	return 1;
}
int	glutpp::gui::object::textview::handle_key_up(__u16 code)
{
	return 1;
}
int	glutpp::gui::object::textview::handle_enter()
{	
	if ( callback_enter_ )
	{
		return callback_enter_();
	}
	
	return 0;
}


