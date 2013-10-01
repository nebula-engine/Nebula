#include <Platform/Input/Linux/PI_IN_LIN_Input.h>

#include <Platform/Renderer/GLX/PL_RE_GLX_Renderer.h>






#include <Platform/Window/Linux/PL_WI_LIN_Window.h>

		PL_WI_LIN_Window::Window() {
}
		PL_WI_LIN_Window::~Window() {
	PRINTSIG;
	
	
}
void	PL_WI_LIN_Window::init(  v )
{
	PRINTSIG;
	
	// create Input object
	m_pl_in_lin_input = new PL_IN_LIN_Input();
	if ( m_pl_in_lin_input == NULL ) throw Except("WTF!");

	m_input = m_pl_in_lin_input;

	// initialize Input object
	AR_Init* i = DynCast<Void,AR_Init>( v );
	i->window = this;

	m_pl_in_lin_input->init( i );





	// Graphics Context
	m_values.cap_style  = CapButt;
	m_values.join_style = JoinBevel;
	
	m_valuemask = GCCapStyle | GCJoinStyle;
	
	m_line_width = 2;
	m_line_style = LineSolid;
	m_cap_style = CapButt;
	m_join_style = JoinBevel;
	
	if ( !m_xdisplay ) throw Except("xdisplay is null");

	// Create a new graphics context
	m_gc = XCreateGC( m_xdisplay, m_xwindow, m_valuemask, &m_values);
	if (m_gc < 0) {
		fprintf(stderr, "XCreateGC: \n");
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





	
	CenterPointer();






	// Create Renderer
	PL_RE_GLX_Renderer* rendererGLX = new PL_RE_GLX_Renderer();
	m_renderer = rendererGLX;
	
	rendererGLX->m_xdisplay = m_xdisplay;
	rendererGLX->m_root_xwindow = m_root_xwindow;
	rendererGLX->m_xwindow = m_xwindow;
	
	// initialize Renderer
	rendererGLX->init( v );
	


	// to prevent multiple key events while holding a key
	XAutoRepeatOff(m_xdisplay);




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
void	PL_WI_LIN_Window::Register_keys()
{
	PL_IN_Input::init( v );

	m_keys[XK_space]		= Key::Space;
	m_keys[XK_BackSpace]	= Key::Backspace;
	m_keys[XK_Linefeed]		= Key::Linefeed;
	m_keys[XK_Left]			= Key::Left;
	m_keys[XK_Right]		= Key::Right;
	m_keys[XK_Down]			= Key::Down;
	m_keys['a']				= Key::a;
	m_keys['b']				= Key::b;
	m_keys['c']				= Key::c;
	m_keys['d']				= Key::d;
	m_keys['e']				= Key::e;
	m_keys['f']				= Key::f;
	m_keys['g']				= Key::g;
	m_keys['h']				= Key::h;
	m_keys['i']				= Key::i;
	m_keys['j']				= Key::j;
	m_keys['k']				= Key::k;
	m_keys['l']				= Key::l;
	m_keys['m']				= Key::m;
	m_keys['n']				= Key::n;
	m_keys['o']				= Key::o;
	m_keys['p']				= Key::p;
	m_keys['q']				= Key::q;
	m_keys['r']				= Key::r;
	m_keys['s']				= Key::s;
	m_keys['t']				= Key::t;
	m_keys['u']				= Key::u;
	m_keys['v']				= Key::v;
	m_keys['w']				= Key::w;
	m_keys['x']				= Key::x;
	m_keys['y']				= Key::y;
	m_keys['z']				= Key::z;
	
	
	
}
void	PL_WI_LIN_Window::shutdown()
{
	//PRINTSIG;
	
	XFreeGC( m_xdisplay, m_gc );
	XDestroyWindow( m_xdisplay, m_xwindow );
}
void	PL_WI_LIN_Window::update()
{
	if ( !m_pl_in_lin_input ) throw Except("m_pl_in_lin_input is null");
	
	XEvent xevent;

	int x,y,k;
	
	XMotionEvent motion;
	
	KeySym keysym;

	while( XCheckWindowEvent( m_xdisplay, m_xwindow, m_event_mask, &xevent ) )
	{
		switch ( xevent.type )
		{
		case Expose:
			ExposeWindow(xevent);
			break;
		case KeyRelease:
			// get Xlib key
			keysym = XLookupKeysym( &xevent.xkey, 0 );

			// convert to universal key
			k = LookupKey(keysym);
			
			sig_key_down_(k, m_no);

			m_pl_in_lin_input->VKeyUp(  );

			break;
		case KeyPress:
			xkey = xevent.xkey;
			
			keysym = XLookupKeysym( &xkey, 0 );
			
			k = m_pl_in_lin_input->LookupKey(keysym);
			
			sig_key_up( k, m_no );
			
			m_pl_in_lin_input->VKeyDown( k, m_no );
			
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

					CenterPointer();
					
					sig_pointer_motion(x,y);
					//m_pl_in_lin_input->VMouseMove(x,y);
				}
			}
			break;
		case FocusIn:
		case FocusOut:
			FocusChange( xevent );
			break;
		}
	}
}
void	PL_WI_LIN_Window::Process( FR_COM_MSG_Message* message ) {
}
void	PL_WI_LIN_Window::ExposeWindow(XEvent xevent)
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
		CenterPointer();

		/*
		renderGLX->DrawQuad();
		renderGLX->VSwap();
		*/
	}
}
void	PL_WI_LIN_Window::FocusChange(XEvent xevent)
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
void	PL_WI_LIN_Window::CenterPointer()
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



