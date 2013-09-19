

// Windows---------------------------
// bitmap font

void print(float x, float y)
{
    sprintf_s( str,64, "v %f %f %f", game->objects.at(0)->body->v.col[0],game->objects.at(0)->body->v.col[1],game->objects.at(0)->body->v.col[2] );
	glRasterPos2f( -0.45f, -0.175f );
	glPrint(str);
}

GLvoid ClientEngine::GL::build_font( GLvoid )        	
{
    // Build Our Bitmap Font
    
    // Windows Font ID
	HFONT	font;
    // Used For Good House Keeping
	HFONT	oldfont;									

    // Storage For 96 Characters
	base = glGenLists(96);								

    // Height Of Font
    // Width Of Font
    // Angle Of Escapement
    // Orientation Angle
    // Font Weight
    // Italic
    // Underline
    // Strikeout
    // Character Set Identifier
    // Output Precision
    // Clipping Precision
    // Output Quality
    // Family And Pitch
    // Font Name
    
	font = CreateFont(	-16,							
		0,								
		0,								
		0,								
		FW_NORMAL,						
		FALSE,							
		FALSE,							
		FALSE,							
		ANSI_CHARSET,					
		OUT_TT_PRECIS,					
		CLIP_DEFAULT_PRECIS,			
		ANTIALIASED_QUALITY,			
		FF_DONTCARE|DEFAULT_PITCH,		
		TEXT("Courier New"));			

     // Selects The Font We Want
	oldfont = (HFONT)SelectObject(hdc, font);
    // Builds 96 Characters Starting At Character 32
	wglUseFontBitmaps(hdc, 32, 96, base);
	SelectObject(hdc, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}
GLvoid ClientEngine::GL::kill_font( GLvoid )									// Delete The Font List
{
	glDeleteLists(base, 96);							// Delete All 96 Characters
}
GLvoid ClientEngine::GL::glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf_s(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}




// Linux-----------------------
// bitmap font

GLuint base;

void makeRasterFont(Display *dpy)
{
    XFontStruct *fontInfo;
    Font id;
    unsigned int first, last;
    fontInfo = XLoadQueryFont(dpy, "-adobe-times-medium-r-normal--17-120-100-100-p-88-iso8859-1");
        
    
    if (fontInfo == NULL)
    {
        printf ("no font found\n");
        exit (0);
    }
    
    id = fontInfo->fid;
    first = fontInfo->min_char_or_byte2;
    last = fontInfo->max_char_or_byte2;
    
    base = glGenLists(last+1);
    if (base == 0)
    {
        printf ("out of display lists\n");
        exit (0);
    }
    glXUseXFont(id, first, last-first+1, base+first);
}

void printString(char *s)
{
    glListBase(base);
    glCallLists(strlen(s), GL_UNSIGNED_BYTE, (unsigned char *)s);
}

void display(void)
{
    GLfloat white[3] = { 1.0, 1.0, 1.0 };
    long i, j;
    char teststring[33];

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3fv(white);
    
    for (i = 32; i < 127; i += 32)
    {
        glRasterPos2i(20, 200 - 18*i/32);
        for (j = 0; j < 32; j++)
        {
            teststring[j] = i+j;
        }
        teststring[32] = 0;
        printString(teststring);
    }
    
    glRasterPos2i(20, 100);
    printString("The quick brown fox jumps");
    glRasterPos2i(20, 82);
    printString("over a lazy dog.");
    glFlush ();
}













