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
	auto p = glutpp::__master.get_program(glutpp::program_name::e::TEXT);
	p->use();

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
	printf("%s\n", __PRETTY_FUNCTION__);

	std::shared_ptr<glutpp::window> w = get_window();

	/*conns_.key_fun_ = w->sig_.key_fun_.connect(
	  std::bind(&glutpp::gui::layout::key_fun,
	  this,
	  std::placeholders::_1,
	  std::placeholders::_2,
	  std::placeholders::_3,
	  std::placeholders::_4
	  ));
	 */
	conns_.mouse_button_fun_ = w->sig_.mouse_button_fun_.connect(
			std::bind(&glutpp::gui::layout::mouse_button_fun,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3
				));


}
int	glutpp::gui::layout::mouse_button_fun(int button, int action, int mods)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	
	switch(action)
	{
		case GLFW_PRESS:
			switch(button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:
					search(button, action, mods);
					break;
			}
			break;
		default:
			return 0;
	}
}
int	glutpp::gui::layout::search(int button, int action, int mods)
{
	printf("%s\n", __PRETTY_FUNCTION__);

	double x, y;
	int w, h;
	glfwGetCursorPos(get_window()->window_, &x, &y);
	glfwGetWindowSize(get_window()->window_, &w, &h);
	
	printf("%f %f %i %i\n", x, y, w, h);
	
	x = x / (float)w * 2.0 - 1.0;
	y = y / (float)h * 2.0 - 1.0;

	printf("%f %f\n", x, y, w, h);
	
	for(auto it = objects_.map_.begin(); it != objects_.map_.end(); ++it)
	{
		std::shared_ptr<glutpp::gui::object::object> o = (*it).second;
	
		printf("object %f %f %f %f\n", o->x_, o->y_, o->w_, o->h_);	
	
		if(x < o->x_) return 0;
		if(x > (o->x_ + o->w_)) return 0;
		if(y < o->y_) return 0;
		if(y > (o->y_ + o->h_)) return 0;
		
		return o->mouse_button_fun(button, action, mods);
	}
}











