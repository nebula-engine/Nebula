#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//#include <GLee.h>
#include <GLFW/glfw3.h>

#include <map>

//#include <GL/glew.h>
//#include <GL/glut.h>

#include <math/color.h>

#include <glutpp/free.h>
#include <glutpp/window.h>
#include <glutpp/object.h>
#include <glutpp/light.h>
#include <glutpp/shader.h>
#include <glutpp/program.h>
#include <glutpp/renderable.h>

template <typename... Args>
void	fatal_error(char const * c, Args ...args)
{
	char fmt[128];
	strcat(fmt, "error: ");
	strcat(fmt, c);
	strcat(fmt, "\n");
	printf(fmt, args...);
	exit(0);
}
void	fatal_error(char const * c)
{
	char fmt[128];
	strcat(fmt, "error: ");
	strcat(fmt, c);
	strcat(fmt, "\n");
	printf("%s\n",c);
	exit(0);
}
void	check_error()
{
	GLenum errCode = glGetError();
	if (errCode != GL_NO_ERROR)
	{
		//printf("%s\n",gluErrorString(errCode));
	}
}
glutpp::window::window(int w, int h, int x, int y, const char * title):
	w_(w), h_(h), x_(x), y_(y),
	program_(NULL),
	title_(title)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	printf(GLUTPP_INSTALL_DIR);
	printf("\n");
	
	
	__master.reg(this);
}
GLint	glutpp::window::get_program()
{
	if(program_ == NULL)
	{
		printf("program is NULL\n");
		//exit(0);
		return 0;
	}
	
	if(program_->o_ == 0)
	{
		printf("program object is 0\n");
		//exit(0);
	}
	
	return program_->o_;
}
void	glutpp::window::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	//glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	//glutInitWindowSize(width, height);
	//glutInitWindowPosition(initPositionX, initPositionY);
	
	//glutpp::__master.CallGlutCreateWindow( (char *)title_, this );

		
	//if (!GLEW_VERSION_2_1) fatal_error("wrong glew version");
	
	//CheckExt();
	
	printf("%s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	//Check for necessary extensions
	if(!GL_ARB_depth_texture || !GL_ARB_shadow)
	{
		printf("I require ARB_depth_texture and ARB_shadow extensionsn\n");
		exit(0);//return false;
	}

	//Shading states
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Depth states

	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	
	// shaders
	shaders();

	uniforms();

	renderable_->init(shared_from_this());
	
	checkerror("unknown");
}
glutpp::window::~window()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	glfwDestroyWindow(window_);
}
void	glutpp::window::shaders()
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	// remove old program
	if(program_)
	{
		delete program_;
	}
	
	std::map<unsigned int,int> shader_map;

	unsigned int m = 
		RAY_TRACE |
		LIGHTING | 
		SHADOW |
		SHADOW_MAP | 
		REFLECT |
		REFLECT_PLANAR |
		REFLECT_CURVED |
		TEX_IMAGE |
		TEX_NORMAL_MAP;

	// populate map based on platform capability
	shader_map[ LIGHTING ] = 0;

	if(all(SHADER))
	{
		printf("shaders enabled\n");
		
		unsigned int f = mask(m);

		auto it = shader_map.find(f);

		if(it == shader_map.end()) fatal_error("shader configuration %i not implemented",f);

		int s = it->second;

		program_ = new program;
		program_->init();

		shader_count_ = 0;
		switch(s)
		{
			case 0:
				shaders_ = new shader[2];

				shaders_[0].load(GLUTPP_SHADER_DIR"/prog_0/vs.glsl", GL_VERTEX_SHADER);
				shaders_[1].load(GLUTPP_SHADER_DIR"/prog_0/fs.glsl", GL_FRAGMENT_SHADER);

				shader_count_ = 2;
				break;
			default:
				fatal_error("shader configuration %i not implemented",f);
				break;
		}

		program_->add_shaders(shaders_,shader_count_);
		program_->compile();
		program_->use();
	}
	else
	{
		printf("shaders not enabled\n");
	}
}
void	glutpp::window::uniforms()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	uniform_light_count_.init(this,"light_count");
	uniform_model_.init(this,"model");
	uniform_view_.init(this,"view");
	uniform_proj_.init(this,"proj");
}
void	glutpp::window::draw_ortho()
{
	//Restore other states
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);

	//Set matrices for ortho
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	draw_ortho();

	//Print text
	//glRasterPos2f(-1.0f, 0.9f);
	//for(unsigned int i=0; i<strlen(fpsString); ++i)
	//	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, fpsString[i]);

	//reset matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}
void	glutpp::window::display_dim()
{
	//glEnable(GL_LIGHTING);

	lights_for_each(&glutpp::light::dim);

	draw();
}
void	glutpp::window::display_bright()
{
	//printf("%s\n",__PRETTY_FUNCTION__);

	//3rd pass: Draw with bright light
	lights_for_each(&glutpp::light::load);

	if(all(REFLECT | REFLECT_PLANAR)) objects_for_each(&glutpp::object::render_reflection);

	if(all(SHADOW | SHADOW_MAP) && !all(SHADER)) lights_for_each(&glutpp::light::draw_shadow_no_shader);

	draw();

	check_error();

	if(all(SHADOW | SHADOW_MAP)) lights_for_each(&glutpp::light::RenderShadowPost);
}
void	glutpp::window::callback_window_refresh_fun(GLFWwindow*)
{
}
void	glutpp::window::step(double)
{
}
void	glutpp::window::loop()
{
	double time;
	
	resize();
	
	while (!glfwWindowShouldClose(window_))
	{
		time = glfwGetTime();
		
		step(time);
		
		render(time);
		
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}
}
void	glutpp::window::callback_window_size_fun(GLFWwindow* window, int w, int h)
{
	w_ = w;
	h_ = h;
	
	resize();

	callback_window_refresh_fun(window);
}
void	glutpp::window::callback_window_pos_fun(GLFWwindow* window, int x, int y)
{
	x_ = x;
	y_ = y;

	callback_window_refresh_fun(window);
}
void	glutpp::window::callback_window_close_fun(GLFWwindow* window)
{

}
void	glutpp::window::callback_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	map_sig_key_[key](scancode, action, mods);
	
	switch(key)
	{
	/*	case 's':
			toggle(SHADOW);
			break;
		case 'o':
			toggle(ORTHO);
			break;
		case 'r':
			toggle(REFLECT);
			break;*/
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window_, 1);
			break;
	}
}
void	glutpp::window::resize()
{
	glViewport(0, 0, w_, h_);

	renderable_->resize();
}
void checkerror(char const * msg)
{
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		//unsigned char const * str = gluErrorString(err);
		//printf("%s: %s\n",msg,str);
		exit(0);
	}


}





