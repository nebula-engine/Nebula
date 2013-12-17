#include <tinyxml/tinyxml.h>

#include <string>
#include <algorithm>

#include <GLFW/glfw3.h>

#include <glutpp/window.h>
#include <glutpp/renderable.h>

#include <glutpp/gui/object/object.h>
#include <glutpp/gui/object/edittext.h>

#include <glutpp/gui/layout.h>

glutpp::gui::layout::layout()
{

}
std::shared_ptr<glutpp::window>	glutpp::gui::layout::get_window()
{
	assert(!renderable_.expired());
	assert(!renderable_.lock()->window_.expired());
	
	return renderable_.lock()->window_.lock();
}
void	glutpp::gui::layout::init(std::shared_ptr<glutpp::renderable> renderable)
{
	//jess::clog << NEB_FUNCSIG << std::endl;

	assert(renderable);
	
	
	renderable_ = renderable;
	
	
	// demo object
	std::shared_ptr<glutpp::gui::object::textview> object(new glutpp::gui::object::textview);
	object->set_label("hello");
	object->x_ = 0.0;
	object->y_ = 0.0;
	
	objects_.push(object);
}
void	glutpp::gui::layout::load_xml(char const * filename)
{

}
void	glutpp::gui::layout::render(double time)
{
	//Restore other states
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);
	
	//if(!all(SHADERS))
	{
		//Set matrices for ortho
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(ortho_);
		//gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		draw();
		//Print text
		//glRasterPos2f(-1.0f, 0.9f);
		//for(unsigned int i=0; i<strlen(fpsString); ++i)
		//	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, fpsString[i]);
	
	}
}
void	glutpp::gui::layout::draw()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	//jess::clog << "objects_.size()=" << objects_.map_.size() << std::endl;

	objects_.foreach(&glutpp::gui::object::object::draw);
}
void	glutpp::gui::layout::connect()
{
	std::shared_ptr<glutpp::window> w = get_window();

	conns_.key_fun_ = w->sig_.key_fun_.connect(
			std::bind(&glutpp::gui::layout::key_fun,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4
				));
}



