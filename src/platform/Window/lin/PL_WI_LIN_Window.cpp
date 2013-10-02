#include <jess/free.hpp>

//#include <jess/ostream.hpp>

#include <nebula/asio/message.hpp>

#include <nebula/platform/key.hpp>

#include <nebula/platform/renderer/gl/glx/base.hpp>

#include <nebula/platform/window/lin/base.hpp>

npwl::base::base()
{
}
npwl::base::~base()
{
	//PRINTSIG;
}
void	npwl::base::init( boost::shared_ptr<npp::base> parent )
{
	//PRINTSIG;
	npw::base::init( parent );
	
	// Graphics Context
	m_values.cap_style  = CapButt;
	m_values.join_style = JoinBevel;
	
	m_valuemask = GCCapStyle | GCJoinStyle;
	
	m_line_width = 2;
	m_line_style = LineSolid;
	m_cap_style = CapButt;
	m_join_style = JoinBevel;
	
	jess::assertion( m_xdisplay );
	
	// Create a new graphics context
	m_gc = XCreateGC( m_xdisplay, m_xwindow, m_valuemask, &m_values);
	if ( m_gc < 0 )
	{
		//jess::cerr << "XCreateGC error" << std::endl;
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
	m_center_x = m_win_width/2;
	m_center_y = m_win_height/2;





	
	center_pointer();






	// create renderer
	boost::shared_ptr<nprgg::base> rnd_glx( new nprgg::base() );

	renderer_ = rnd_glx;

	rnd_glx->m_xdisplay = m_xdisplay;
	rnd_glx->m_root_xwindow = m_root_xwindow;
	rnd_glx->m_xwindow = m_xwindow;
	
	// initialize Renderer
	rnd_glx->init( shared_from_this() );
	


	// to prevent multiple key events while holding a key
	XAutoRepeatOff( m_xdisplay );




	// Display keycodes
	int min_keycodes_return;
	int max_keycodes_return;
	XDisplayKeycodes( m_xdisplay, &min_keycodes_return, &max_keycodes_return );
	
	int keycode_count = max_keycodes_return - min_keycodes_return + 1;
	int keysyms_per_keycode_return;

	KeySym* keysym = XGetKeyboardMapping( m_xdisplay, min_keycodes_return, keycode_count, &keysyms_per_keycode_return );

	int c = 0;
	for ( int a = 0; a < keycode_count; a++ ) {
		for ( int b = 0; b < keysyms_per_keycode_return; b++ ) {
			//printf("%i ",keysym[c]);
			c++;
		}

		//printf("\n");
	}

	XFree(keysym);


}
void	npwl::base::register_keys()
{

	keys_[XK_space]			= np::key::space;
	keys_[XK_BackSpace]		= np::key::backspace;
	keys_[XK_Linefeed]		= np::key::linefeed;
	keys_[XK_Left]			= np::key::left;
	keys_[XK_Right]			= np::key::right;
	keys_[XK_Down]			= np::key::down;
	keys_[XK_Up]			= np::key::up;
	keys_['a']			= np::key::a;
	keys_['b']			= np::key::b;
	keys_['c']			= np::key::c;
	keys_['d']			= np::key::d;
	keys_['e']			= np::key::e;
	keys_['f']			= np::key::f;
	keys_['g']			= np::key::g;
	keys_['h']			= np::key::h;
	keys_['i']			= np::key::i;
	keys_['j']			= np::key::j;
	keys_['k']			= np::key::k;
	keys_['l']			= np::key::l;
	keys_['m']			= np::key::m;
	keys_['n']			= np::key::n;
	keys_['o']			= np::key::o;
	keys_['p']			= np::key::p;
	keys_['q']			= np::key::q;
	keys_['r']			= np::key::r;
	keys_['s']			= np::key::s;
	keys_['t']			= np::key::t;
	keys_['u']			= np::key::u;
	keys_['v']			= np::key::v;
	keys_['w']			= np::key::w;
	keys_['x']			= np::key::x;
	keys_['y']			= np::key::y;
	keys_['z']			= np::key::z;
	

}
void	npwl::base::shutdown()
{
	//PRINTSIG;
	
	XFreeGC( m_xdisplay, m_gc );
	XDestroyWindow( m_xdisplay, m_xwindow );
}
void	npwl::base::update()
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
			
			sig_key_up_( k, no_ );


			break;
		case KeyPress:
			xkey = xevent.xkey;
			
			keysym = XLookupKeysym( &xkey, 0 );
			
			k = lookup_key( keysym );
			
			sig_key_down_( k, no_ );
			
			break;
		case MotionNotify:
			if ( m_hasFocus )
			{
				motion = xevent.xmotion;

				x = motion.x - m_center_x;
				y = motion.y - m_center_y;

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
void	npwl::base::process_message( boost::shared_ptr<na::message> msg )
{
	
}
void	npwl::base::expose_window( XEvent xevent )
{
	XWindowAttributes gwa;
	int status = 0;
	
	int width = 0;
	int height = 0;
	
	if ( m_hasFocus )
	{
		status = XGetWindowAttributes( m_xdisplay, m_xwindow, &gwa );
		switch ( status ) {
		case BadWindow:
			printf("XGetWindowAttributes: BadWindow\n");
			break;
		case BadDrawable:
			printf("XGetWindowAttributes: BadDrawable\n");
			break;
		}
		
		//renderGLX->Viewport( 0, 0, gwa.width, gwa.height );
		
		width = gwa.width;
		height = gwa.height;

		m_center_x = width/2;
		m_center_y = height/2;

		glViewport(0, 0, width, height);

		/*      Set current Matrix to projection*/
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity(); //reset projection matrix

		/*      Time to calculate aspect ratio of
				our window.
		*/
		gluPerspective(54.0f, (GLfloat)width/(GLfloat)height, 1.0f, 1000.0f);

		glMatrixMode(GL_MODELVIEW); //set modelview matrix
		glLoadIdentity(); //reset modelview matrix

		printf("expose\n");
		center_pointer();

		/*
		renderGLX->DrawQuad();
		renderGLX->VSwap();
		*/
	}
}
void	npwl::base::focus_change(XEvent xevent)
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
void	npwl::base::center_pointer()
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
int	npwl::base::lookup_key( int xkey )
{
	return keys_[xkey];
}





