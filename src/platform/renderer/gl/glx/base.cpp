#include <jess/except.hpp>
#include <jess/ostream.hpp>
#include <jess/free.hpp>

#include <nebula/platform/renderer/gl/glx/base.hpp>

int xerrorhandler( Display* dpy, XErrorEvent* error )
{
	char errorstring[128];
	XGetErrorText( dpy, error->error_code, errorstring, 128 );
	
	std::cerr << "fatal: X error--" << errorstring << std::endl;
	exit(-1);
}

void	n23110::base::init( jess::shared_ptr<n22000::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	//std::cout << this << std::endl;
	/// \todo move this to window
	XSetErrorHandler( xerrorhandler );

	att = new GLint[5];
	att[0] = GLX_RGBA;
	att[1] = GLX_DEPTH_SIZE;
	att[2] = 24;
	att[3] = GLX_DOUBLEBUFFER;
	att[4] = None;

	if ( !m_xdisplay )
	{
		throw jess::except( "m_xdisplay is null" );
	}

	m_vi = glXChooseVisual( m_xdisplay, 0, att );

	if( m_vi == 0 )
	{
		throw jess::except("glXChooseVisual: no appropriate visual found\n");

	} 
	else
	{
		printf( "glXChooseVisual: visual %p selected\n", (void *)m_vi->visualid ); // %p creates hexadecimal output like in glxin10000o
	}

	m_cmap = XCreateColormap( m_xdisplay, m_root_xwindow, m_vi->visual, AllocNone );

	m_swa.colormap = m_cmap;
	m_swa.event_mask = ExposureMask | KeyPressMask;

	m_glc = glXCreateContext( m_xdisplay, m_vi, NULL, GL_TRUE );

	glXMakeCurrent( m_xdisplay, m_xwindow, m_glc );

	if ( glXGetCurrentContext() == NULL )
	{
		throw jess::except("context not created");
	}

	// font
	init_raster_font();

	// must be here so that base class has valid GLContext available
	n23100::base::init( parent );

	jess::clog << NEB_FUNCSIG << " exit" << std::endl;
}
void	n23110::base::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	glXMakeCurrent( m_xdisplay, None, NULL );
	glXDestroyContext( m_xdisplay, m_glc );
}
void	n23110::base::draw_text( int x, int y, std::string str )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	//jess::clog << x << " " << y << " " << str << " " << font_base_ << std::endl;
	
	GLfloat white[3] = { 1.0, 1.0, 1.0 };
	glColor3fv(white);
	
	glRasterPos2i( x, y );

	glPushAttrib( GL_LIST_BIT );

	glListBase( font_base_ ); GetGLError();

	glCallLists( strlen( str.c_str() ), GL_UNSIGNED_BYTE, (unsigned char *)(str.c_str())); GetGLError();

	glPopAttrib();
}
void	n23110::base::viewport( int a, int b, int c, int d )
{
	glViewport( a, b, c, d );
}
void	n23110::base::update()
{

}
void	n23110::base::begin_render()
{
	n23100::base::begin_render();
}
void	n23110::base::end_render()
{
	n23100::base::end_render();
}
void	n23110::base::swap()
{
	glXSwapBuffers( m_xdisplay, m_xwindow );
}
void	n23110::base::look_at( physx::PxVec3 eye, physx::PxVec3 center, physx::PxVec3 up )
{
	n23100::base::look_at( eye, center, up );
}
void	n23110::base::draw_cube()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	n23100::base::draw_cube();
}
void	n23110::base::push_matrix()
{
	n23100::base::push_matrix();
}
void	n23110::base::pop_matrix()
{
	n23100::base::pop_matrix();
}
void	n23110::base::mult_matrix( physx::PxMat44 mat )
{
	n23100::base::mult_matrix( mat );
}
void	n23110::base::scale( physx::PxVec3 v )
{
	n23100::base::scale( v );
}
void	n23110::base::draw_window_quad( int x, int y, int w, int h )
{
	n23100::base::draw_window_quad( x, y, w, h );
}
void	n23110::base::light()
{
	n23100::base::light();
}
void	n23110::base::init_raster_font()
{
	::Display* dpy = m_xdisplay;

	XFontStruct *fontIn10000o;

	Font id;

	unsigned int first, last;

	// list fonts
	int fonts_count = 0;
	char** fonts = XListFonts( dpy, "*normal--20-*", 500, &fonts_count );

	for( int i = 0; i < fonts_count; i++ )
	{
		jess::clog << fonts[i] << "... ";


		fontIn10000o = XLoadQueryFont( dpy, fonts[i] );
		//fontIn10000o = XLoadQueryFont(dpy, "-adobe-times-medium-r-normal--17-120-100-100-p-88-iso8859-1");

		if( fontIn10000o == 0 )
		{
			jess::clog << "failed" << std::endl;
		}
		else
		{
			jess::clog << "success!" << std::endl;
		}
	}
	XFreeFontNames( fonts );
	
	// select font
	fonts = XListFonts( dpy, "*normal--20-*", 300, &fonts_count );

	for( int i = 0; i < fonts_count; i++ )
	{
		jess::clog << fonts[i] << "... ";


		fontIn10000o = XLoadQueryFont( dpy, fonts[i] );
		//fontIn10000o = XLoadQueryFont(dpy, "-adobe-times-medium-r-normal--17-120-100-100-p-88-iso8859-1");

		if( fontIn10000o == 0 )
		{
			jess::clog << "failed" << std::endl;
		}
		else
		{
			jess::clog << "success!" << std::endl;
			break;
		}
	}
	XFreeFontNames( fonts );
	
	if( fontIn10000o == 0 )
	{
		jess::clog << "no font found" << std::endl;
		exit(0);
	}
	
	
	id = fontIn10000o->fid;

	first = fontIn10000o->min_char_or_byte2;

	last = fontIn10000o->max_char_or_byte2;

	font_base_ = glGenLists(last+1); GetGLError();

	jess::clog << "Font " << id << " " << first << " " << last << " " << font_base_ << std::endl;

	if ( font_base_  == 0 )
	{
		printf ("out of display lists\n");

		exit (0);
	}

	glXUseXFont( id, first, last-first+1, font_base_ + first );
	
}






