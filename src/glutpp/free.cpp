#include <GRU/free.h>

void	GRU::draw_text(__s32 x, __s32 y, char * text)
{

}

int isExtensionSupported(const char *extension)
{
	const GLubyte *extensions = NULL;
	const GLubyte *start;
	GLubyte *where, *terminator;

	/* Extension names should not have spaces. */
	where = (GLubyte *) strchr(extension, ' ');
	if (where || *extension == '\0')
		return 0;
	extensions = glGetString(GL_EXTENSIONS);
	/* It takes a bit of care to be fool-proof about parsing the
	   OpenGL extensions string. Don't be fooled by sub-strings,
	   etc. */
	start = extensions;
	for (;;)
	{
		//printf("%s\n",start);

		where = (GLubyte *) strstr((const char *) start, extension);
		if (!where)
			break;
		terminator = where + strlen(extension);
		if (where == start || *(where - 1) == ' ')
			if (*terminator == ' ' || *terminator == '\0')
				return 1;
		start = terminator;
	}
	return 0;
}
int isSupported(const char *extension)
{
	if(isExtensionSupported(extension))
	{
		printf("%s is supported\n",extension);
		return 1;
	}
	
	printf("%s is not supported\n",extension);
	exit(0);
		
}
void CheckExt()
{
	isSupported("GL_ARB_vertex_shader");
	isSupported("GL_ARB_fragment_shader");
}

