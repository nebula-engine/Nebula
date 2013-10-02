#include <jess/except.hpp>


#include <nebula/platform/renderer/gl/base.hpp>


void GetGLError()
{
	GLenum error;
	error = glGetError();
	if ( error != GL_NO_ERROR )
	{
		//GLubyte* byte = gluErrorString(	error );
		printf("%s\n", gluErrorString( error ) );
		throw jess::except( "opengl error 10" );
	}
}
void GetGLError( GLenum error )
{
	if ( error != GL_NO_ERROR )
	{
		//GLubyte* byte = gluErrorString(	error );
		printf("%s\n", gluErrorString( error ) );
		throw jess::except( "opengl error 10" );
	}
}
void	nprg::base::init( const boost::shared_ptr<npw::base>&  )
{
	//PRINTSIG;

	printf( "OpenGL version %s\n", glGetString(GL_VERSION) );
	printf( "GLSL   version %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION) );
	printf( "GLEW   version %s\n", glewGetString(GLEW_VERSION) );

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	GetGLError(err);

	if ( !GLEW_VERSION_2_1 ) throw jess::except("GLEW version problem");



	GLint numExtensions;
	GLint i;

	glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

	for (i = 0; i < numExtensions; i++)
	{
		const GLubyte * e = glGetStringi(GL_EXTENSIONS, i);
		printf("%s\n",e);
	}



	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);

	glEnable (GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

	glEnable (GL_LIGHT0);
	glShadeModel (GL_SMOOTH); //set the shader to smooth shader

	//unsigned int program = 0;

	//CompileShaders( program );

}
void	nprg::base::draw_cube()
{
	//PRINTSIG;

	GLfloat cyan[] = {0.0f, 0.8f, 0.8f, 1.0f};
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat shininess[] = { 128.0f };

	glMaterialfv( GL_FRONT, GL_DIFFUSE, cyan);
	glMaterialfv( GL_FRONT, GL_SPECULAR, white);
	glMaterialfv( GL_FRONT, GL_SHININESS, shininess );

	glBegin(GL_QUADS);


	glNormal3f(  0.0,  0.0,  1.0 );
	glVertex3f( -0.5, -0.5,  0.5 );
	glVertex3f(  0.5, -0.5,  0.5 );
	glVertex3f(  0.5,  0.5,  0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );

	glNormal3f(  0.0,  0.0, -1.0 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glVertex3f(  0.5, -0.5, -0.5 );
	glVertex3f(  0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );

	glNormal3f(  1.0,  0.0,  0.0 );
	glVertex3f(  0.5, -0.5, -0.5 );
	glVertex3f(  0.5,  0.5, -0.5 );
	glVertex3f(  0.5,  0.5,  0.5 );
	glVertex3f(  0.5, -0.5,  0.5 );

	glNormal3f( -1.0,  0.0,  0.0 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glVertex3f( -0.5, -0.5,  0.5 );

	glNormal3f(  0.0,  1.0,  1.0 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f(  0.5,  0.5, -0.5 );
	glVertex3f(  0.5,  0.5,  0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );

	glNormal3f(  0.0, -1.0,  1.0 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glVertex3f(  0.5, -0.5, -0.5 );
	glVertex3f(  0.5, -0.5,  0.5 );
	glVertex3f( -0.5, -0.5,  0.5 );

	glEnd();

}
void	nprg::base::draw_sphere()
{
	//PRINTSIG;
	/*
	GLfloat cyan[] = {0.0f, 0.8f, 0.8f, 1.0f};
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat shininess[] = { 2048.0f };
	
	glMaterialfv( GL_FRONT, GL_DIFFUSE, cyan);
	glMaterialfv( GL_FRONT, GL_SPECULAR, white);
	glMaterialfv( GL_FRONT, GL_SHININESS, shininess );

	glBegin(GL_TRIANGLES);
	
	bnu::vector<FLOAT> v[6];
	v[0] = new Math::Vec3f(1,0,0);
	v[1] = new Math::Vec3f(0,1,0);
	v[2] = new Math::Vec3f(0,0,1);
	v[3] = new Math::Vec3f(-1,0,0);
	v[4] = new Math::Vec3f(0,-1,0);
	v[5] = new Math::Vec3f(0,0,-1);
	
	
	int ind[][3] =
	{
		{0,1,2},
		{1,3,2},
		{0,2,4},
		{0,5,1},
		{0,4,5},
		{3,1,5},
		{2,3,4},
		{4,3,5}
	};

	for ( int i = 0; i < 8; i++ ) {

		TriFace t( *v[ind[i][0]], *v[ind[i][1]], *v[ind[i][2]] );

		t.Split(3 );


		t.Render();
	}

	glEnd();
	*/
}
void	nprg::base::unproject(int winX, int winY, int winZ, double* objX, double* objY, double* objZ)
{
	GLdouble modelview[16];
	GLdouble projection[16];
	GLint viewport[4];
	
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	/*GLint*/ gluUnProject(winX, winY, winZ, modelview, projection, viewport, objX, objY, objZ);
}
void	nprg::base::draw_window_quad(int win_x, int win_y, int w, int h)
{
	double obj_x1, obj_y1, obj_z1, obj_x2, obj_y2, obj_z2;
	
	
	nprg::base::unproject(win_x,   win_y,   0, &obj_x1, &obj_y1, &obj_z1);
	nprg::base::unproject(win_x+w, win_y+h, 0, &obj_x2, &obj_y2, &obj_z2);

	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex2d(obj_x1, obj_y1);
	glVertex2d(obj_x2, obj_y1);
	glVertex2d(obj_x2, obj_y2);
	glVertex2d(obj_x1, obj_y2);
	glEnd();
	glPopMatrix();
}
void	nprg::base::draw_2d_quad()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex2d(-0.5f, -0.5);
	glVertex2d( 0.5f, -0.5);
	glVertex2d( 0.5f,  0.5);
	glVertex2d(-0.5f,  0.5);
	glEnd();
	glPopMatrix();
}
void	nprg::base::draw_quad()
{

	glBegin(GL_QUADS);
	glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
	glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
	glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
	glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
	glEnd();

}
void	nprg::base::begin_render()
{

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();

}
void	nprg::base::light()
{
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0 };
	GLfloat pos[] =     { 0.0, 2.0, 2.0, 1.0 };

	glLightfv( GL_LIGHT0, GL_POSITION, pos );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );
}
void	nprg::base::end_render()
{
	glFlush();
	swap();
}
void	nprg::base::update()
{

}
void	nprg::base::swap()
{

}
void	nprg::base::look_at( bnu::vector<float> eye, bnu::vector<float> center, bnu::vector<float> up )
{
	gluLookAt( eye(0),  eye(1), eye(2), center(0), center(1), center(2), up(0), up(1), up(2) );
}
void	nprg::base::resize( int width, int height )
{
	// Reset the viewport to new dimensions
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);

	//reset projection matrix
	glLoadIdentity(); 

	// Time to calculate aspect ratio of our window
	gluPerspective(54.0, (GLdouble)width/(GLdouble)height, 1.0, 1000.0);

	//set modelview matrix
	glMatrixMode(GL_MODELVIEW); 

	//reset modelview matrix
	glLoadIdentity();

}
void	nprg::base::push_matrix()
{
	glPushMatrix();
}
void	nprg::base::mult_matrix( bnu::matrix<FLOAT> mat )
{
	//PRINTSIG;
	//PrintPxMat44(matrix);

	glMultMatrixf( &mat.data()[0] );
}
void	nprg::base::scale( bnu::vector<float> v )
{
	glScalef( v(0), v(0), v(2) );
}
void	nprg::base::pop_matrix()
{
	glPopMatrix();
}
void	nprg::base::compile_shaders( unsigned int& program )
{
	unsigned int tcs;
	unsigned int tes;


	char ** const tcs_source = new char*;
	char ** const tes_source = new char*;

	printf("loading tcs source... ");
	load_shader_source( "../../../Nebula/Media/OpenGL/Shaders/Tesselation_Control/tc1.c", tcs_source );
	printf("tcs source loaded\n");


	printf("loading tes source... ");
	load_shader_source( "../../../Nebula/Media/OpenGL/Shaders/Tesselation_Evaluation/te1.c", tes_source );
	printf("tes source loaded\n");
	//printf("shaders loaded\n");


	// compile tcs
	printf("compiling tcs... \n");
	tcs = glCreateShader( GL_TESS_CONTROL_SHADER ); GetGLError();
	glShaderSource( tcs, 1, (const char **)tcs_source, 0 ); GetGLError();
	glCompileShader( tcs ); GetGLError();
	printf("tcs compiled\n");

	printf("compiling tes... \n");
	// compile tes
	tes = glCreateShader( GL_TESS_EVALUATION_SHADER  ); GetGLError();
	glShaderSource( tes, 1, (const char **)tes_source, 0 ); GetGLError();
	glCompileShader( tes ); GetGLError();
	printf("tes compiled\n");

	// create Program
	program = glCreateProgram();
	glAttachShader( program, tcs ); GetGLError();
	glAttachShader( program, tes ); GetGLError();
	glLinkProgram( program ); GetGLError();


	// delete shaders as the program has them now
	glDeleteShader( tcs );
	glDeleteShader( tes );

	printf("shaders loaded\n");
}
void	nprg::base::load_shader_source( const char* filename, char ** const shader )
{
	FILE *		file = 0;
	long		size = 0;

	file = fopen( filename, "r" );
	if (!file) throw jess::except("File error");
	
	// obtain file size:
	fseek (file , 0 , SEEK_END);
	size = ftell (file);
	rewind (file);

	// allocate memory to contain the whole file:
	*shader = new char[sizeof(char)*(size+1)];
	//if (!buffer) throw Except("Memory error");


	// copy the file into the buffer
	fread( (void*)(*shader), 1, size, file );
	//if (result != size) throw Except("Reading error");
	(*shader)[size] = '\0';


	/* the whole file is now loaded in the memory buffer. */

	// close input file
	fclose(file);

	// allocate memory in shader source
	// = new char[size];

	// append buffer to output file
	//memcpy( (void*)(*shader), buffer , size );



	// terminate
	//delete[] buffer;
}
void	nprg::base::load_identity()
{
	glLoadIdentity();
}





