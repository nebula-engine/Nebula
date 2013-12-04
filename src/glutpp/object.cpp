#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <png.h>

#include <glutpp/object.h>
#include <glutpp/window.h>

glutpp::object::object():
	attrib_position_("position"),
	attrib_normal_("normal"),
	attrib_texcoor_("texcoor"),
	type_(NONE)
{}
void	glutpp::object::init(window* window)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	window_ = window;
}
GLuint glutpp::object::png_texture_load(const char * file_name, int * width, int * height)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	png_byte header[8];

	FILE *fp = fopen(file_name, "rb");
	if (fp == 0)
	{
		perror(file_name);
		return 0;
	}

	// read the header
	fread(header, 1, 8, fp);

	if (png_sig_cmp(header, 0, 8))
	{
		fprintf(stderr, "error: %s is not a PNG.\n", file_name);
		fclose(fp);
		return 0;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		fprintf(stderr, "error: png_create_read_struct returned 0.\n");
		fclose(fp);
		return 0;
	}

	// create png info struct
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		fprintf(stderr, "error: png_create_info_struct returned 0.\n");
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(fp);
		return 0;
	}

	// create png info struct
	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info)
	{
		fprintf(stderr, "error: png_create_info_struct returned 0.\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
		fclose(fp);
		return 0;
	}

	// the code in this if statement gets called if libpng encounters an error
	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "error from libpng\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		return 0;
	}

	// init png reading
	png_init_io(png_ptr, fp);

	// let libpng know you already read the first 8 bytes
	png_set_sig_bytes(png_ptr, 8);

	// read all the info up to the image data
	png_read_info(png_ptr, info_ptr);

	// variables to pass to get info
	int bit_depth, color_type;
	png_uint_32 temp_width, temp_height;

	// get info about png
	png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
			NULL, NULL, NULL);

	if (width){ *width = temp_width; }
	if (height){ *height = temp_height; }

	// Update the png info struct.
	png_read_update_info(png_ptr, info_ptr);

	// Row size in bytes.
	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

	// glTexImage2d requires rows to be 4-byte aligned
	rowbytes += 3 - ((rowbytes-1) % 4);

	// Allocate the image_data as a big block, to be given to opengl
	png_byte * image_data;
	image_data = (png_byte*)malloc(rowbytes * temp_height * sizeof(png_byte)+15);
	if (image_data == NULL)
	{
		fprintf(stderr, "error: could not allocate memory for PNG image data\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		return 0;
	}

	// row_pointers is for pointing to image_data for reading the png with libpng
	png_bytep * row_pointers = (png_bytep*)malloc(temp_height * sizeof(png_bytep));
	if (row_pointers == NULL)
	{
		fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		free(image_data);
		fclose(fp);
		return 0;
	}

	// set the individual row_pointers to point at the correct offsets of image_data
	for (unsigned int i = 0; i < temp_height; i++)
	{
		row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
	}

	// read the png into image_data through row_pointers
	png_read_image(png_ptr, row_pointers);

	// Generate the OpenGL texture object
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, temp_width, temp_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// clean up
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	free(image_data);
	free(row_pointers);
	fclose(fp);
	return texture;
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

	fclose(fp);

	return 0;
}
void glutpp::object::init_buffer(GLint program)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	checkerror("unknown");

	// attributes
	
	

	// image
	uniform_image_.init(window_->program_->o_, "image");
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
			1/*attrib_normal_.o_*/,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glutpp::vertex),
			(void*)offsetof(glutpp::vertex, normal));
	checkerror("glVertexAttribPointer normal");
	
	glVertexAttribPointer(
			2/*attrib_texcoor_.o_*/,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glutpp::vertex),
			(void*)offsetof(glutpp::vertex, texcoor));
	checkerror("glVertexAttribPointer texcoor");

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

	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo_); checkerror("glBindBuffer");

	// texture
	glActiveTexture(GL_TEXTURE0);
	texture_image_.bind();
	glUniform1i(texture_image_.o_, 0);

	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_indices_);

	//checkerror();

	//readbuffer(buffer_position_);

	printf("draw\n");

	glDrawElements(GL_TRIANGLES, fh_.len_indices_, GL_UNSIGNED_SHORT, 0);

	//checkerror();

	printf("draw\n");

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	printf("draw\n");

	attrib_position_.disable();
	attrib_normal_.disable();
	attrib_texcoor_.disable();

	printf("draw\n");
}
void	glutpp::object::render_reflection(){}



