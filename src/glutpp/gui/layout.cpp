#include <tinyxml/tinyxml.h>

#include <string>
#include <algorithm>

#include <glutpp/gui/object/object.h>
#include <glutpp/gui/object/edittext.h>

#include <glutpp/gui/layout.h>

void	glutpp::gui::layout::init()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
	glutpp::gui::object::edittext* object(new glutpp::gui::object::edittext);
	
	objects_.push(object);
}
void	glutpp::gui::layout::load_xml( std::string file_name )
{

}
void	glutpp::window::render(double time)
{
	//Restore other states
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);
	
	if(!all(SHADERS))
	{
		//Set matrices for ortho
		glMatrixMode(GL_PROJECTION);
		glLoadMatrix(ortho_);
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
oid	glutpp::gui::layout::draw()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	//jess::clog << "objects_.size()=" << objects_.map_.size() << std::endl;
	
	objects_.foreach(&glutpp::gui::object::object::draw);
}
