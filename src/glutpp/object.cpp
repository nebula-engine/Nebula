#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <png.h>

#include <glutpp/object.h>
#include <glutpp/window.h>

glutpp::object::object(window* window):
	window_(window),
	texture_image_(window),
	uniform_image_(window,"image"),
	attrib_position_(0,"position"),
	attrib_normal_(1,"normal"),
	attrib_texcoor_(2,"texcoor"),
	material_front_(
			window,
			math::blue,
			math::red,
			math::white,
			math::black,128.0),
	type_(NONE)
{}
void print_vector(GLfloat* v, unsigned int m, unsigned int n)
{
	for(unsigned int a=0;a<m;++a)
	{
		for(unsigned int b = 0; b < n; ++b)
		{
			printf("% .2f ",v[(a*n)+b]);
		}
		printf("\n");
	}

}
void print_vectori(GLushort* v, unsigned int m, unsigned int n)
{
	for(unsigned int a=0;a<m;++a)
	{
		for(unsigned int b = 0; b < n; ++b)
		{
			printf("% 3i ",v[(a*n)+b]);
		}
		printf("\n");
	}

}
void readbuffer(GLuint buffer)
{
	GLfloat data[24*4];

	glBindBuffer(GL_ARRAY_BUFFER, buffer);	
	checkerror("glBindBuffer");

	glGetBufferSubData(GL_ARRAY_BUFFER, 0, 1*4*sizeof(GLfloat), data);
	checkerror("glGetBufferSubData");
}
int	glutpp::object::load(const char * filename)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	FILE * fp;

	printf("load file '%s'\n",filename);

	fp = fopen(filename, "rb");

	if (fp <= 0) 
	{
		perror("fopen");
		return 0;
	}

	// read header
	fread(&fh_, sizeof(file_header), 1, fp);

	printf("vertices: %i elements\n",fh_.len_vertices_);
	printf("indices:  %i elements\n",fh_.len_indices_);

	// allocate
	vertices_ = new glutpp::vertex[fh_.len_vertices_];
	indices_ = new GLushort[fh_.len_indices_];

	fread(vertices_, sizeof(glutpp::vertex), fh_.len_vertices_, fp);
	fread(indices_,  sizeof(GLushort),       fh_.len_indices_,  fp);

	fclose(fp);

	// print
	for(int i = 0; i < fh_.len_vertices_; ++i)
	{
		vertices_[i].print();
	}

	init_buffer(window_->program_->o_);

	return 0;
}
int	glutpp::object::save(const char * filename)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	FILE * fp;

	fp = fopen(filename, "wb");

	if (!fp) 
	{
		perror("fopen");
		return 0;
	}

	//fh_.len_vertices_ = sizeof(vertices_)/sizeof(glutpp::vertex);
	//fh_.len_indices_ = sizeof(indices_)/sizeof(GLushort);

	printf("sizeof(vertex): %i\n",(int)sizeof(glutpp::vertex));
	printf("indices:   %i elements\n",fh_.len_indices_);
	printf("vertices:  %i elements\n",fh_.len_vertices_);

	// read header
	fwrite(&fh_, sizeof(file_header), 1, fp);
	fwrite(vertices_, sizeof(glutpp::vertex), fh_.len_vertices_, fp);
	fwrite(indices_, sizeof(GLushort), fh_.len_indices_, fp);

	// print
	for(int i = 0; i < fh_.len_vertices_; ++i)
	{
		vertices_[i].print();
	}
	printf("'%s' saved\n",filename);

	// close
	fclose(fp);

	return 0;
}
void glutpp::object::init_buffer(GLint program)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	checkerror("unknown");

	// attributes

	// image
	texture_image_.load_png("bigtux.png");

	// indices
	int size = fh_.len_indices_ * sizeof(GLushort);

	glGenBuffers(1, &buffer_indices_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_indices_);
	glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			size,
			indices_,
			GL_STATIC_DRAW);

	checkerror("glBufferData");

	// vertices

	glGenBuffers(1, &vbo_);

	int baseOffset = 0;
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	//glBindVertexBuffer(0, vbo_, baseOffset, sizeof(glutpp::vertex));

	glVertexAttribPointer(
			attrib_position_.o_,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glutpp::vertex),
			offsetof(glutpp::vertex, position));
	checkerror("glVertexAttribPointer");

	glVertexAttribPointer(
			attrib_normal_.o_,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glutpp::vertex),
			(void*)offsetof(glutpp::vertex, normal));
	checkerror("glVertexAttribPointer normal");

	glVertexAttribPointer(
			attrib_texcoor_.o_,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glutpp::vertex),
			(void*)offsetof(glutpp::vertex, texcoor));
	checkerror("glVertexAttribPointer texcoor");

	size = fh_.len_vertices_ * sizeof(glutpp::vertex);
	glBufferData(
			GL_ARRAY_BUFFER,
			size,
			vertices_,
			GL_STATIC_DRAW);

	checkerror("glBufferData");

	//glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}
void glutpp::object::draw()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	checkerror("unknown");

	attrib_position_.enable();
	attrib_normal_.enable();
	attrib_texcoor_.enable();

	printf("draw\n");

	// model matrix
	window_->uniform_model_->load_matrix4fv(model_);

	// material
	material_front_.load();


	// texture
	glActiveTexture(GL_TEXTURE0);checkerror("glActiveTexture");
	texture_image_.bind();
	uniform_image_.load_1i(0);
	//glUniform1i(texture_image_.o_, 0);checkerror("glUniform1i");

	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo_); checkerror("glBindBuffer");
	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_indices_); checkerror("glBindBuffer");

	// draw
	glDrawElements(GL_TRIANGLES, fh_.len_indices_, GL_UNSIGNED_SHORT, 0);checkerror("glDrawElements");

	printf("draw\n");

	glBindBuffer(GL_ARRAY_BUFFER,0);checkerror("glBindBuffer");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);checkerror("glBindBuffer");

	printf("draw\n");

	attrib_position_.disable();
	attrib_normal_.disable();
	attrib_texcoor_.disable();

	printf("draw\n");
}
void	glutpp::object::render_reflection(){}

void	glutpp::vertex::print()
{
	printf("% 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f\n",position.x,position.y,position.z,normal.x,normal.y,normal.z,texcoor.x,texcoor.y);
	//position.print();
	//normal.print();
	//texcoor.print();
}


