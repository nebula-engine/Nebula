#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <png.h>

#include <math/mat44.h>
#include <math/geo/polyhedron.h>

#include <glutpp/object.h>
#include <glutpp/window.h>

glutpp::object::object():
	window_(NULL),
	type_(NONE)
{}
void	glutpp::object::init(window* window)
{
	window_ = window;
	
	uniforms();
	
	material_front_.init(window_);
}
void	glutpp::object::uniforms()
{
	uniform_image_.init(window_, "image");

	attrib_position_.init(window_, 0, "position");
	attrib_normal_.init(window_, 1, "normal");
	attrib_texcoor_.init(window_, 2, "texcoor");
}
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
void	glutpp::object::construct(math::geo::polyhedron* poly)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	fh_.len_vertices_ = 3 * poly->nt_ + 4 * poly->nq_;
	fh_.len_indices_ = 3 * poly->nt_ + 6 * poly->nq_;
	
	printf("vertices: %i elements\n",fh_.len_vertices_);
	printf("indices:  %i elements\n",fh_.len_indices_);
	
	vertices_ = new glutpp::vertex[fh_.len_vertices_];
	indices_ = new GLushort[fh_.len_indices_];
	
	int m = 3 * poly->nt_;
	
	glutpp::vertex* v = vertices_;
	
	// tris
	for(int i = 0; i < poly->nt_; i++)
	{
		for(int j = 0; j < 3; ++j)
		{
			int k = i*3 + j;
			printf("% 2i ",k);
			
			v[i*3+j].position = poly->tris_[i].v_[j].xyz;
			v[i*3+j].normal = poly->tris_[i].v_[j].n;
			
			indices_[i*3+j] = i*3+j;
		}
		printf("\n");
	}

	v = vertices_ + m;
	
	
	// quads
	for(int i = 0; i < poly->nq_; i++)
	{
		for(int j = 0; j < 4; ++j)
		{
			v[i*4 + j].position = poly->quads_[i].v_[j].xyz;
			v[i*4 + j].normal = poly->quads_[i].v_[j].n;
		}
		
		int n = 0;
		for(int l = 0; l < 2; ++l)
		{
			for(int k = 0; k < 3; ++k)
			{	
				int j = (k+n) % 4;
				
				indices_[m + i*6 + l*3 + k] = m + i*4 + j;
				
				printf("% 3i ", m + i*4 + j);
			}
			printf("\n");
			n += 2;
		}
	}

}
int	glutpp::object::load(const char * name)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	char filename[256];
	filename[0] = '\0';

	strcat(filename, GLUTPP_OBJECT_DIR"/");
	strcat(filename, name);

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
	for(int i = 0; i < fh_.len_vertices_; ++i) vertices_[i].print();

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
void glutpp::object::init_buffer()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	if(window_ == NULL)
	{
		printf("window is NULL\n");
		exit(0);
	}

	GLint program = window_->get_program();

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
	
	glutpp::vertex v;
	long off_position = (long)&v.position - (long)&v;
	long off_normal = (long)&v.normal - (long)&v;
	long off_texcoor = (long)&v.texcoor - (long)&v;
	
	glVertexAttribPointer(
			attrib_position_.o_,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glutpp::vertex),
			(void*)off_position);
	checkerror("glVertexAttribPointer");

	glVertexAttribPointer(
			attrib_normal_.o_,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glutpp::vertex),
			(void*)off_normal);
	checkerror("glVertexAttribPointer normal");

	glVertexAttribPointer(
			attrib_texcoor_.o_,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glutpp::vertex),
			(void*)off_texcoor);
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
void	glutpp::object::model_load()
{
	math::mat44 model(pose_);
	model.SetScale(s_);
	
	if(window_->all(glutpp::window::SHADER))
	{
		window_->uniform_model_.load_matrix4fv(model);
	}
	else
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glMultMatrixf(model);
	}
}
void	glutpp::object::model_unload()
{
	if(window_->all(glutpp::window::SHADER))
	{
	}
	else
	{
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
}
void	glutpp::object::draw()
{
	//printf("%s\n",__PRETTY_FUNCTION__);

	checkerror("unknown");

	attrib_position_.enable();
	attrib_normal_.enable();
	attrib_texcoor_.enable();


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
	model_load();

	glDrawElements(GL_TRIANGLES, fh_.len_indices_, GL_UNSIGNED_SHORT, 0);checkerror("glDrawElements");
	glDrawElements(GL_LINES, fh_.len_indices_, GL_UNSIGNED_SHORT, 0);checkerror("glDrawElements");

	model_unload();


	glBindBuffer(GL_ARRAY_BUFFER,0);checkerror("glBindBuffer");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);checkerror("glBindBuffer");


	attrib_position_.disable();
	attrib_normal_.disable();
	attrib_texcoor_.disable();

}
void	glutpp::object::render_reflection(){}

void	glutpp::vertex::print()
{
	printf("% 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f\n",position.x,position.y,position.z,normal.x,normal.y,normal.z,texcoor.x,texcoor.y);
	//position.print();
	//normal.print();
	//texcoor.print();
}


