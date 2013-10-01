#include <stdio.h>

#include <Platform/Renderer/GLX/PL_RE_GLX_Renderer.h>

void	PL_RE_GLX_Renderer::init( const boost::shared_ptr<>&  ) {
	PRINTSIG;
	
	att = new GLint[5];
	att[0] = GLX_RGBA;
	att[1] = GLX_DEPTH_SIZE;
	att[2] = 24;
	att[3] = GLX_DOUBLEBUFFER;
	att[4] = None;



	m_vi = glXChooseVisual( m_xdisplay, 0, att );
	
	if(m_vi == NULL) {
		throw Except("glXChooseVisual: no appropriate visual found\n");
		
	} 
	else {
		printf("glXChooseVisual: visual %p selected\n", (void *)m_vi->visualid); // %p creates hexadecimal output like in glxinfo
	}
	
	m_cmap = XCreateColormap( m_xdisplay, m_root_xwindow, m_vi->visual, AllocNone );
	
	m_swa.colormap = m_cmap;
	m_swa.event_mask = ExposureMask | KeyPressMask;
	
	m_glc = glXCreateContext( m_xdisplay, m_vi, NULL, GL_TRUE );
	
	glXMakeCurrent( m_xdisplay, m_xwindow, m_glc );
	
	if ( glXGetCurrentContext() == NULL ) throw Except("context not created");

	PL_RE_GL_Renderer::init( data );

}
void	PL_RE_GLX_Renderer::shutdown() {
	PRINTSIG;
	
	glXMakeCurrent( m_xdisplay, None, NULL );
	glXDestroyContext( m_xdisplay, m_glc );
}
void	PL_RE_GLX_Renderer::Viewport( int a, int b, int c, int d ) {
	glViewport( a, b, c, d );
}
void	PL_RE_GLX_Renderer::update() {
	
}
void	PL_RE_GLX_Renderer::VBeginRender() {
	PL_RE_GL_Renderer::VBeginRender();
}
void	PL_RE_GLX_Renderer::VEndRender() {
	PL_RE_GL_Renderer::VEndRender();
}
void	PL_RE_GLX_Renderer::VSwap() {
	glXSwapBuffers( m_xdisplay, m_xwindow );
}
void	PL_RE_GLX_Renderer::VLookAt( Math::Vec3f eye, Math::Vec3f center, Math::Vec3f up ) {
	//GLdouble eyeX, GLdouble eyeY,GLdouble eyeZ,GLdouble centerX,GLdouble centerY,GLdouble centerZ,GLdouble upX,GLdouble upY,GLdouble upZ);
	PL_RE_GL_Renderer::VLookAt( eye, center, up );
}




//	double eyeX, double eyeY,double eyeZ,double centerX,double centerY,double centerZ,double upX,double upY,double upZ







