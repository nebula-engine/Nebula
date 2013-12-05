#include <string.h>
#include <stdio.h>

//#include <GLee.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <math/color.h>

#include <glutpp/free.h>
#include <glutpp/window.h>
#include <glutpp/object.h>
#include <glutpp/light.h>
#include <glutpp/shader.h>
#include <glutpp/program.h>

void	fatal_error(char const * c,...)
{
	char fmt[128];
	strcat(fmt, "error: ");
	strcat(fmt, c);
	strcat(fmt, "\n");
	printf(fmt,...);
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
glutpp::window::window(int setWidth, int setHeight,
		int setInitPositionX, int setInitPositionY,
		const char * title ):
	width(setWidth),
	height(setHeight),
	initPositionX(setInitPositionX),
	initPositionY(setInitPositionY),
	camera_(this)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(initPositionX, initPositionY);

	glutpp::__master.CallGlutCreateWindow( (char *)title, this );

	GLenum err = glewInit();
	if (err != GLEW_OK) fatal_error("GLEW: %s", glewGetErrorString(err));
	
	if (!GLEW_VERSION_2_1) fatal_error("wrong glew version");
	
	//CheckExt();

	printf("%s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	glEnable(GL_LIGHTING);

	//lights_enable();

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

	checkerror("unknown");
}
glutpp::window::~window()
{
	glutDestroyWindow(windowID);
}
void	glutpp::window::shaders()
{
	std::map<unsigned int,int> shader_map;
	
	unsigned int mask = RAY_TRACE | LIGHTING | SHADOW | SHADOW_MAP | REFLECT | REFLECT_PLANAR | REFLECT_CURVED | TEX_IMAGE | TEX_NORMAL_MAP;
	
	// populate map based on platform capability
	shader_map[ LIGHTING ] = 0;
	
	if(all(SHADER))
	{	
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
				
				shaders_[0].load(GLUTPP_SHADER_PREFIX"/prog_0/vs.glsl", GL_VERTEX_SHADER);
				shaders_[1].load(GLUTPP_SHADER_PREFIX"/prog_0/fs.glsl", GL_FRAGMENT_SHADER);
				
				shader_count_ = 2;
				break;
			default:
				fatal_error("shader configuration %i not implemented",f);
				break;
		}
		
		program_->add_shaders(shaders_,shader_count);
		program_->compile();
		program_->use();
	}
}
void	glutpp::window::uniforms()
{
	uniform_light_count_	= new uniform(this,"light_count");
	uniform_model_		= new uniform(this,"model");
	uniform_view_		= new uniform(this,"view");
	uniform_proj_		= new uniform(this,"proj");
}
void	glutpp::window::lights_for_each(std::function<void(glutpp::light*)> func)
{
	for(int i = 0; i < lights_.size(); ++i)
	{
		func(lights_.at(i));
	}
}
void	glutpp::window::objects_for_each(std::function<void(glutpp::object*)> func)
{
	for(int i = 0; i < objects_.size(); ++i)
	{
		func(objects_.at(i));
	}
}
void	glutpp::window::display_ortho()
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

	DisplayOrtho();

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
void	glutpp::window::DisplayDim()
{
	//glEnable(GL_LIGHTING);

	lights_for_each(&glutpp::light::dim);

	Display();
}
void	glutpp::window::display_bright()
{
	//3rd pass: Draw with bright light
	lights_for_each(&glutpp::light::updateGL);
	
	if(all(REFLECT | REFLECT_PLANAR)) RenderReflection();
	
	if(all(SHADOW | SHADOW_MAP)) lights_for_each(&glutpp::light::RenderShadow);
	
	display();
	
	check_error();
	
	if(all(SHADOW | SHADOW_MAP)) lights_for_each(&glutpp::light::RenderShadowPost);
}
void glutpp::window::CallBackDisplayFunc()
{
	// uniforms
	uniform_light_count_->load_1i(lights_.size());
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
	glutpp::__master.SetIdleToCurrentWindow();
	glutpp::__master.EnableIdleFunction();
}
void glutpp::window::CallBackKeyboardFunc(unsigned char key, int x, int y)
{
	printf("%s\n",__FUNCTION__);

	switch(key)
	{
		case 's':
			toggle( SHADOW );
			break;
		case 'o':
			toggle( ORTHO );
			break;
		case 'r':
			toggle( PLANAR_REFLECTION | PLANAR_REFLECTION_STENCIL );
			break;
		case 27:
			exit(0);
	}
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

void glutpp::window::Display()
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
void glutpp::window::DisplayOrtho()
{}   
void glutpp::window::Idle()
{}   


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





