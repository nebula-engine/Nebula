#include <jess/except.hpp>
#include <jess/free.hpp>

//#include <jess/ostream.hpp>

#include <nebula/asio/message.hpp>

#include <nebula/platform/key.hpp>

#include <nebula/platform/renderer/gl/glx/base.hpp>

#include <nebula/platform/window/lin/base.hpp>

n22100::base::base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
n22100::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n22100::base::init( jess::shared_ptr<n21000::base> parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n22000::base::init( parent );

	register_keys();

	// Graphics Context
	m_values.cap_style  = CapButt;
	m_values.join_style = JoinBevel;
	
	m_valuemask = GCCapStyle | GCJoinStyle;
	
	m_line_width = 2;
	m_line_style = LineSolid;
	m_cap_style = CapButt;
	m_join_style = JoinBevel;
	
	if ( !m_xdisplay )
	{
		throw jess::except( "m_xdisplay is null" );
	}
	
	// Create a new graphics context
	m_gc = XCreateGC( m_xdisplay, m_xwindow, m_valuemask, &m_values);
	if ( m_gc < 0 )
	{
		throw jess::except( "XCreateGC error" );
	}
	
	// Colors
	XSetForeground( m_xdisplay, m_gc, WhitePixel( m_xdisplay, m_screen_num ));
	XSetBackground( m_xdisplay, m_gc, BlackPixel( m_xdisplay, m_screen_num ));
	
	// Attributes
	XSetLineAttributes( m_xdisplay, m_gc, m_line_width, m_line_style, m_cap_style, m_join_style );
	
	XSetFillStyle( m_xdisplay, m_gc, FillSolid );
	
	// XWindow name
	XStoreName( m_xdisplay, m_xwindow, "VERY SIMPLE APPLICATION");
	
	// Select Inputs
	m_event_mask = KeyPressMask | KeyReleaseMask | ExposureMask | PointerMotionMask | FocusChangeMask;
	XSelectInput( m_xdisplay, m_xwindow, m_event_mask );
	
	// Map Window
	XMapWindow( m_xdisplay, m_xwindow );
	
	// set center
	m_center_x = width_/2;
	m_center_y = height_/2;

	// center pointer
	center_pointer();

	// create renderer
	jess::shared_ptr<n23110::base> rnd_glx( new n23110::base() );

	renderer_ = rnd_glx;

	rnd_glx->m_xdisplay = m_xdisplay;
	rnd_glx->m_root_xwindow = m_root_xwindow;
	rnd_glx->m_xwindow = m_xwindow;
	
	// initialize Renderer
	rnd_glx->init( shared_from_this() );

	// to prevent multiple key events while holding a key
	//XAutoRepeatOff( m_xdisplay );

	// Display keycodes
	int min_keycodes_return;
	int max_keycodes_return;
	XDisplayKeycodes( m_xdisplay, &min_keycodes_return, &max_keycodes_return );
	
	int keycode_count = max_keycodes_return - min_keycodes_return + 1;
	int keysyms_per_keycode_return;

	KeySym* keysym = XGetKeyboardMapping( m_xdisplay, min_keycodes_return, keycode_count, &keysyms_per_keycode_return );

	int c = 0;
	for ( int a = 0; a < keycode_count; a++ )
	{
		for ( int b = 0; b < keysyms_per_keycode_return; b++ )
		{
			//printf("%i ",keysym[c]);
			c++;
		}

		//printf("\n");
	}

	XFree(keysym);

	jess::clog << NEB_FUNCSIG << " exit" << std::endl;
}
void	n22100::base::register_keys()
{

	keys_[XK_space]			= n20000::key::space;
	keys_[XK_BackSpace]		= n20000::key::backspace;
	keys_[XK_Linefeed]		= n20000::key::linefeed;
	keys_[XK_Left]			= n20000::key::left;
	keys_[XK_Right]			= n20000::key::right;
	keys_[XK_Down]			= n20000::key::down;
	keys_[XK_Up]			= n20000::key::up;
	keys_['a']			= n20000::key::a;
	keys_['b']			= n20000::key::b;
	keys_['c']			= n20000::key::c;
	keys_['d']			= n20000::key::d;
	keys_['e']			= n20000::key::e;
	keys_['f']			= n20000::key::f;
	keys_['g']			= n20000::key::g;
	keys_['h']			= n20000::key::h;
	keys_['i']			= n20000::key::i;
	keys_['j']			= n20000::key::j;
	keys_['k']			= n20000::key::k;
	keys_['l']			= n20000::key::l;
	keys_['m']			= n20000::key::m;
	keys_['n']			= n20000::key::n;
	keys_['o']			= n20000::key::o;
	keys_['p']			= n20000::key::p;
	keys_['q']			= n20000::key::q;
	keys_['r']			= n20000::key::r;
	keys_['s']			= n20000::key::s;
	keys_['t']			= n20000::key::t;
	keys_['u']			= n20000::key::u;
	keys_['v']			= n20000::key::v;
	keys_['w']			= n20000::key::w;
	keys_['x']			= n20000::key::x;
	keys_['y']			= n20000::key::y;
	keys_['z']			= n20000::key::z;
	

}
void	n22100::base::shutdown()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
	XFreeGC( m_xdisplay, m_gc );
	XDestroyWindow( m_xdisplay, m_xwindow );
}
void	n22100::base::update()
{
	
	XEvent xevent;
	int x,y,k;
	
	XMotionEvent motion;
	
	KeySym keysym;
	
	XKeyEvent xkey;

	while( XCheckWindowEvent( m_xdisplay, m_xwindow, m_event_mask, &xevent ) )
	{
		switch ( xevent.type )
		{
		case Expose:
			expose_window(xevent);
			break;
		case KeyRelease:
			// get Xlib key
			keysym = XLookupKeysym( &xevent.xkey, 0 );

			// convert to universal key
			k = lookup_key( keysym );
			
			sig_key_up_( k );


			break;
		case KeyPress:
			xkey = xevent.xkey;
			
			keysym = XLookupKeysym( &xkey, 0 );
			
			k = lookup_key( keysym );
		
			jess::clog << "key=" << k << std::endl;
	
			sig_key_down_( k );
			
			break;
		case MotionNotify:
			if ( m_hasFocus )
			{
				motion = xevent.xmotion;

				x = motion.x - m_center_x;
				y = motion.y - m_center_y;

				jess::clog << "center=(" << m_center_x << "," << m_center_y << ")" << std::endl;
				
				if ( ( x != 0 ) || ( y != 0 ) )
				{
					//printf("%i %i\n",x,y);
				
					center_pointer();
					
					sig_pointer_motion_(x,y);
					//m_pl_in_lin_input->VMouseMove(x,y);
				}
			}
			break;
		case FocusIn:
		case FocusOut:
			focus_change( xevent );
			break;
		}
	}
}
void	n22100::base::process_message( jess::shared_ptr<n40000::message> msg )
{
	
}
void	n22100::base::expose_window( XEvent xevent )
{
	XWindowAttributes gwa;
	int status = 0;
	
	//if ( m_hasFocus )
	{
		status = XGetWindowAttributes( m_xdisplay, m_xwindow, &gwa );
		switch ( status )
		{
		case BadWindow:
			printf("XGetWindowAttributes: BadWindow\n");
			break;
		case BadDrawable:
			printf("XGetWindowAttributes: BadDrawable\n");
			break;
		}
		
		//renderGLX->Viewport( 0, 0, gwa.width, gwa.height );
		
		width_ = gwa.width;
		height_ = gwa.height;
		
		m_center_x = width_/2;
		m_center_y = height_/2;
	
		renderer_->resize( width_, height_ );

		/*	
		glViewport(0, 0, width, height);
		
		//      Set current Matrix to projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity(); //reset projection matrix

		//      Time to calculate aspect ratio of our window.
		gluPerspective(54.0f, (GLfloat)width/(GLfloat)height, 1.0f, 1000.0f);

		glMatrixMode(GL_MODELVIEW); //set modelview matrix
		glLoadIdentity(); //reset modelview matrix
*/
		

		center_pointer();		
	}
}
void	n22100::base::focus_change(XEvent xevent)
{
	switch ( xevent.type )
	{
	case FocusIn:
		m_hasFocus = true;
		//CenterPointer();
		break;
	case FocusOut:
		m_hasFocus = false;
		break;
	}
}
void	n22100::base::center_pointer()
{
	// center curser
	::Window src_w = None;
	::Window dest_w = m_xwindow;
	
	int dest_x = m_center_x;
	int dest_y = m_center_y;

	int src_x = 0;
	int src_y = 0;
	unsigned int src_width = 0;
	unsigned int src_height = 0;
	
	XWarpPointer(
		m_xdisplay,
		src_w,
		dest_w,
		src_x,
		src_y, 
		src_width,
		src_height,
		dest_x,
		dest_y);
}
int	n22100::base::lookup_key( int xkey )
{
	return keys_[xkey];
}





