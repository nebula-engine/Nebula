#include <utilities/Types/Utilities.h>

#include <Platform/Renderer/GL/PL_RE_GL_Renderer.h>




void GetGLError() {
	GLenum error;
	error = glGetError();
	if ( error != GL_NO_ERROR ) {
		//GLubyte* byte = gluErrorString(	error );
		printf("%s\n", gluErrorString( error ) );
		throw Except( "opengl error 10" );
	}
}
void GetGLError( GLenum error ) {
	if ( error != GL_NO_ERROR ) {
		//GLubyte* byte = gluErrorString(	error );
		printf("%s\n", gluErrorString( error ) );
		throw Except( "opengl error 10" );
	}
}

void	PL_RE_GL_Renderer::init( const boost::shared_ptr<>&  ) {
	PRINTSIG;

	printf( "OpenGL version %s\n", glGetString(GL_VERSION) );
	printf( "GLSL   version %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION) );
	printf( "GLEW   version %s\n", glewGetString(GLEW_VERSION) );

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	GetGLError(err);

	if ( !GLEW_VERSION_2_1 ) throw Except("GLEW version problem");



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
void	PL_RE_GL_Renderer::VDrawCube() {
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
void	PL_RE_GL_Renderer::VDrawSphere() {
	//PRINTSIG;
	
	GLfloat cyan[] = {0.0f, 0.8f, 0.8f, 1.0f};
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat shininess[] = { 2048.0f };

	glMaterialfv( GL_FRONT, GL_DIFFUSE, cyan);
	glMaterialfv( GL_FRONT, GL_SPECULAR, white);
	glMaterialfv( GL_FRONT, GL_SHININESS, shininess );

	glBegin(GL_TRIANGLES);

	Math::Vec3f* v[6];
	v[0] = new Math::Vec3f(1,0,0);
	v[1] = new Math::Vec3f(0,1,0);
	v[2] = new Math::Vec3f(0,0,1);
	v[3] = new Math::Vec3f(-1,0,0);
	v[4] = new Math::Vec3f(0,-1,0);
	v[5] = new Math::Vec3f(0,0,-1);


	int ind[][3] = {
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

}
void platform::renderer::renderer::gl::base::unproject(float winX, float winY, float winZ, float* objX, float* objY, float* objZ)
{
    float modelview[16];
    float projection[16];
    float viewport[4];

    glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
    glGetFloatv(GL_PROJECTION_MATRIX, projection);
    glGetFloatv(GL_VIEWPORT, viewport);
    
    GLint gluUnProject(winX, winY, winZ, modelview, projection, viewport, objX, objY, objZ);
}
void platform::renderer::renderer::gl::2d::draw_window_quad(int win_x, int win_y, int w, int h)
{
    float obj_x1, obj_y1, obj_z1, obj_x2, obj_y2, obj_z2;
    
    
    platform::renderer::renderer::gl::base::unproject(win_x,   win_y,   0, &obj_x1, &obj_y1, &obj_z1);
    platform::renderer::renderer::gl::base::unproject(win_x+w, win_y+h, 0, &obj_x2, &obj_y2, &obj_z2);
    
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex2d(obj_x1, obj_y1);
    glVertex2d(obj_x2, obj_y1);
    glVertex2d(obj_x2, obj_y2);
    glVertex2d(obj_x1, obj_y2);
    glEnd();
    glPopMatrix();
}
void platform::renderer::renderer::gl::2d::draw_quad()
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
void	PL_RE_GL_Renderer::DrawQuad() {
	
	glBegin(GL_QUADS);
	glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
	glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
	glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
	glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
	glEnd();
	
}
void	PL_RE_GL_Renderer::VBeginRender() {
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode( GL_MODELVIEW );
    
	glLoadIdentity();

}
void	PL_RE_GL_Renderer::VLight() {
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0 };
	GLfloat pos[] =     { 0.0, 2.0, 2.0, 1.0 };
	
	glLightfv( GL_LIGHT0, GL_POSITION, pos );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );
}
void	PL_RE_GL_Renderer::VEndRender() {
	glFlush();
	VSwap();
}
void	PL_RE_GL_Renderer::VUpdate() {
	
}
void	PL_RE_GL_Renderer::VSwap() {
	
}
void	PL_RE_GL_Renderer::VLookAt( Math::Vec3f eye, Math::Vec3f center, Math::Vec3f up ) {
	gluLookAt( eye.x,  eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z );
}
void	PL_RE_GL_Renderer::VResize( int width, int height ) {
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
void	PL_RE_GL_Renderer::VPushMatrix() {
	glPushMatrix();
}
void	PL_RE_GL_Renderer::VMultMatrix( Math::Mat44f& matrix ) {
	//PRINTSIG;
	//PrintPxMat44(matrix);
	
	glMultMatrixf( matrix.v );
}
void	PL_RE_GL_Renderer::VScale( float x, float y, float z ) {
	glScalef( x, y, z );
}
void	PL_RE_GL_Renderer::VPopMatrix() {
	glPopMatrix();
}
void	PL_RE_GL_Renderer::CompileShaders( unsigned int& program ) {
	unsigned int tcs;
	unsigned int tes;


	char ** const tcs_source = new char*;
	char ** const tes_source = new char*;

	printf("loading tcs source... ");
	LoadShaderSource( "../../../Nebula/Media/OpenGL/Shaders/Tesselation_Control/tc1.c", tcs_source );
	printf("tcs source loaded\n");
	
	
	printf("loading tes source... ");
	LoadShaderSource( "../../../Nebula/Media/OpenGL/Shaders/Tesselation_Evaluation/te1.c", tes_source );
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
void	PL_RE_GL_Renderer::LoadShaderSource( const char* filename, char ** const shader ) {
	FILE *		file = 0;
	long		size = 0;

	file = fopen( filename, "r" );
	if (!file) throw Except("File error");

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
void	PL_RE_GL_Renderer::VLoadIdentity() {
	glLoadIdentity();
}





