#include <string.h>
#include <stdio.h>

//#include <GLee.h>


#include <map>

#include <GL/glew.h>
#include <GL/glut.h>

#include <math/color.h>

#include <glutpp/free.h>
#include <glutpp/window.h>
#include <glutpp/object.h>
#include <glutpp/light.h>
#include <glutpp/shader.h>
#include <glutpp/program.h>

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
	exit(0);
}
void	check_error()
{
	GLenum errCode = glGetError();
	if (errCode != GL_NO_ERROR)
	{
		printf("%s\n",gluErrorString(errCode));
	}
}
glutpp::window::window(
		int setWidth, int setHeight,
		int setInitPositionX, int setInitPositionY,
		const char * title ):
	width(setWidth),
	height(setHeight),
	initPositionX(setInitPositionX),
	initPositionY(setInitPositionY),
	program_(NULL),
	title_(title),
	light_count_(0)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	printf(PNT(GLUTPP_PREFIX));
	
	memset(lights_, 0, LIGHT_MAX);
}
void	glutpp::window::add_object(object* o)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	if(o == NULL)
	{
		printf("object is NULL\n");
		return;
	}
	
	objects_.push_back(o);
	
	o->init(this);
	o->init_buffer();
}
void	glutpp::window::add_light(light* l)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	if(light_count_ == LIGHT_MAX)
	{
		printf("max light\n");
		return;
	}
	
	if(l == NULL)
	{
		printf("light is NULL\n");
		return;
	}
	
	lights_[light_count_] = l;
	
	l->init(this, light_count_);
	
	light_count_++;
}
GLint	glutpp::window::get_program()
{
	if(program_ == NULL)
	{
		printf("program is NULL\n");
		exit(0);
	}
	
	if(program_->o_ == 0)
	{
		printf("program object is 0\n");
		exit(0);
	}
	
	return program_->o_;
}
void	glutpp::window::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(initPositionX, initPositionY);

	glutpp::__master.CallGlutCreateWindow( (char *)title_, this );

	GLenum err = glewInit();
	if (err != GLEW_OK) fatal_error("GLEW: %s", glewGetErrorString(err));
	
	if (!GLEW_VERSION_2_1) fatal_error("wrong glew version");
	
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

	camera_.init(this);
	
	checkerror("unknown");
}
glutpp::window::~window()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	glutDestroyWindow(windowID);
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

	unsigned int mask = 
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
		
		unsigned int f = flag_ & mask;

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

				shaders_[0].load(GLUTPP_SHADER_PREFIX"prog_0/vs.glsl", GL_VERTEX_SHADER);
				shaders_[1].load(GLUTPP_SHADER_PREFIX"prog_0/fs.glsl", GL_FRAGMENT_SHADER);

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
}
void	glutpp::window::uniforms()
{	printf("%s\n",__PRETTY_FUNCTION__);

	uniform_light_count_.init(this,"light_count");
	uniform_model_.init(this,"model");
	uniform_view_.init(this,"view");
	uniform_proj_.init(this,"proj");
}
void	glutpp::window::lights_for_each(std::function<void(glutpp::light*)> func)
{	
	//printf("%s\n",__PRETTY_FUNCTION__);

	for(int i = 0; i < light_count_; ++i)
	{
		if(lights_[i] == NULL)
		{
			printf("light is NULL\n");
			exit(0);
		}
		
		func(lights_[i]);
	}
}
void	glutpp::window::objects_for_each(std::function<void(glutpp::object*)> func)
{	
	//printf("%s\n",__PRETTY_FUNCTION__);

	for(int i = 0; i < objects_.size(); ++i)
	{
		if(lights_[i] == NULL)
		{
			printf("light is NULL\n");
			exit(0);
		}

		func(objects_.at(i));
	}
}
void	glutpp::window::callback_display_ortho()
{
	//Restore other states
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);

	//Set matrices for ortho
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	display_ortho();

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
void	glutpp::window::RenderReflection()
{
	for( auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		(*it)->render_reflection();
	}
}
void	glutpp::window::display_dim()
{
	//glEnable(GL_LIGHTING);

	lights_for_each(&glutpp::light::dim);

	display();
}
void	glutpp::window::display_bright()
{
	//printf("%s\n",__PRETTY_FUNCTION__);

	//3rd pass: Draw with bright light
	lights_for_each(&glutpp::light::load);

	if(all(REFLECT | REFLECT_PLANAR)) RenderReflection();

	if(all(SHADOW | SHADOW_MAP) && !all(SHADER)) lights_for_each(&glutpp::light::draw_shadow_no_shader);

	display();

	check_error();

	if(all(SHADOW | SHADOW_MAP)) lights_for_each(&glutpp::light::RenderShadowPost);
}
void glutpp::window::CallBackDisplayFunc()
{
	//printf("%s\n",__PRETTY_FUNCTION__);

	// uniforms
	uniform_light_count_.load_1i(light_count_);
	lights_for_each(&glutpp::light::load);
	
	if(all(SHADOW | SHADOW_MAP)) lights_for_each(&glutpp::light::RenderLightPOV);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	camera_.load();

	if(all(SHADOW | SHADOW_MAP) && !all(SHADER)) display_dim();

	display_bright();

	if(all(ORTHO)) display_ortho();

	glFinish();
	glutSwapBuffers();
	glutPostRedisplay();
}
void glutpp::window::CallBackReshapeFunc(int w, int h)
{
	width = w;
	height = h;

	glViewport(0,0,width,height);

	camera_.w_ = width;
	camera_.h_ = height;

	CallBackDisplayFunc();
}
void glutpp::window::CallBackIdleFunc(void)
{
	Idle();

	CallBackDisplayFunc();
}
void glutpp::window::StartSpinning()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	glutpp::__master.SetIdleToCurrentWindow();
	glutpp::__master.EnableIdleFunction();
}
void glutpp::window::CallBackKeyboardFunc(unsigned char key, int x, int y)
{
	//printf("%s\n",__PRETTY_FUNCTION__);
	
	map_sig_key_down_[key]();
	
	switch(key)
	{
		case 's':
			toggle(SHADOW);
			break;
		case 'o':
			toggle(ORTHO);
			break;
		case 'r':
			toggle(REFLECT);
			break;
		case 27:
			exit(0);
	}
	//key; x; y;                //dummy function
}
void glutpp::window::CallBackKeyboardUpFunc(unsigned char key, int x, int y)
{
	//printf("%s\n",__PRETTY_FUNCTION__);
	
	map_sig_key_up_[key]();

	//key; x; y;                //dummy function
}
void glutpp::window::CallBackMotionFunc(int x, int y)
{
	//x; y;                     //dummy function
}
void glutpp::window::CallBackMouseFunc(int button, int state, int x, int y)
{
	//button; state; x; y;      //dummy function
}
void glutpp::window::CallBackPassiveMotionFunc(int x, int y)
{
	//x; y;                     //dummy function
}
void glutpp::window::CallBackSpecialFunc(int key, int x, int y)
{
	//key; x; y;
}   
void glutpp::window::CallBackVisibilityFunc(int visible)
{
	//visible;                  //dummy function
}
void glutpp::window::SetWindowID(int newWindowID)
{
	windowID = newWindowID;
}
int glutpp::window::GetWindowID(void)
{
	return( windowID );
}

void glutpp::window::display()
{
	for( auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		(*it)->draw();
	}
}
void	glutpp::window::display_all_but(object* o)
{
	for( auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		if( (*it) != o ) (*it)->draw();
	}
}     
void glutpp::window::display_ortho()
{}   
void glutpp::window::Idle()
{
	camera_.step(1.0/60.0);
}   


void checkerror(char const * msg)
{
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		unsigned char const * str = gluErrorString(err);
		printf("%s: %s\n",msg,str);
		exit(0);
	}


}





