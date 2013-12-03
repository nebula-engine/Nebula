

glutpp::attribute::attribute(char const * name):
	name_(name)
{
	GLuint program;
	glGetIntegerv(GL_CURRENT_PROGRAM,&program)
	
	location_ = glGetAttribLocation(program, name_);
	if(location_position_ == -1)
	{
		fprintf(stderr, "Could not find attribute '%s'\n", name_);
		exit(0);
	}
}


