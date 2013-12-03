#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <png.h>

#include <glutpp/object.h>

glutpp::object::object(window* window):
	window_(window)
{
	type_ = NONE;
}
GLuint glutpp::object::png_texture_load(const char * file_name, int * width, int * height)
{
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
void checkerror(char const * msg)
{
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		unsigned char const * str = gluErrorString(err);
		printf("%s: %s\n",msg,str);
		exit(0);
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

	printf("positions: %i elements, %i vectors\n",fh_.len_positions_,fh_.len_positions_/4);
	printf("normals:   %i elements, %i vectors\n",fh_.len_normals_,fh_.len_normals_/3);
	printf("texcoor:   %i elements, %i vectors\n",fh_.len_texcoor_,fh_.len_texcoor_/2);

	printf("indices:   %i elements\n",fh_.len_indices_);

	// allocate
	vertex_positions_ = new GLfloat[fh_.len_positions_];
	vertex_normals_ = new GLfloat[fh_.len_normals_];
	vertex_texcoor_ = new GLfloat[fh_.len_texcoor_];

	vertex_indices_ = new GLushort[fh_.len_indices_];


	// read positions
	fread(vertex_positions_, sizeof(GLfloat), fh_.len_positions_, fp);

	// read normals
	fread(vertex_normals_, sizeof(GLfloat), fh_.len_normals_, fp);
	// read normals
	fread(vertex_texcoor_, sizeof(GLfloat), fh_.len_texcoor_, fp);

	// read indices
	fread(vertex_indices_, sizeof(GLushort), fh_.len_indices_, fp);

	fclose(fp);


	print_vector(vertex_positions_, fh_.len_positions_/4, 4);
	print_vector(vertex_normals_, fh_.len_normals_/3, 3);
	print_vector(vertex_texcoor_, fh_.len_texcoor_/2, 2);
	print_vectori(vertex_indices_, fh_.len_indices_/3, 3);

	return 0;
}
int	glutpp::object::save(const char * filename)
{
	FILE * fp;

	fp = fopen(filename, "wb");

	if (!fp) 
	{
		perror("fopen");
		return 0;
	}

	printf("positions: %i elements, %i vectors\n",fh_.len_positions_,fh_.len_positions_/4);
	printf("normals:   %i elements, %i vectors\n",fh_.len_normals_,fh_.len_normals_/3);
	printf("normals:   %i elements, %i vectors\n",fh_.len_normals_,fh_.len_normals_/3);
	printf("indices:   %i elements\n",fh_.len_indices_);
	
	fh_.len_vertices_ = sizeof(vertices_)/sizeof(glutpp::vertex);
	fh_.len_indices_ = sizeof(indices_)/sizeof(GLushort);
	
	// read header
	fwrite(&fh_, sizeof(file_header), 1, fp);
	
	
	// read positions
	fwrite(vertices_, sizeof(glutpp::vertex), fh_.len_vertices_, fp);
	
	// read normals
	fwrite(vertex_normals_, sizeof(GLfloat), fh_.len_normals_, fp);
	// read normals
	fwrite(vertex_texcoor_, sizeof(GLfloat), fh_.len_texcoor_, fp);

	// read indices
	fwrite(vertex_indices_, sizeof(GLushort), fh_.len_indices_, fp);

	fclose(fp);

	return 0;
}

void glutpp::object::init_buffer(GLint program)
{
	checkerror("unknown");

	// attribute
	location_image_ = glGetUniformLocation(program, "image");checkerror("glGetUniformLocation");
	
	int w,h;
	texture_image_ = png_texture_load("bigtux.png",&w,&h);


	
	// texture
/*
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture_image_);checkerror("glGenTextures");
	glBindTexture(GL_TEXTURE_2D, texture_image_);checkerror("glBindTexture");


	// Black/white checkerboard
	float pixels[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f
	};

	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			2, 2,
			0,
			GL_RGB,
			GL_FLOAT,
			pixels);checkerror("glTexImage2D");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);checkerror("glTexParameteri");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
*/
	// buffers


	// position
	GLsizeiptr size = fh_.len_positions_ * sizeof(GLfloat);// sizeof(vertex_positions_);

	glGenBuffers(1, &buffer_position_);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_position_);
	glBufferData(
			GL_ARRAY_BUFFER,
			size,
			vertex_positions_,
			GL_DYNAMIC_DRAW);

	printf("size: %i\n",(int)size);


	checkerror("glBufferData");

	// normal
	size = fh_.len_normals_ * sizeof(GLfloat);

	glGenBuffers(1, &buffer_normal_);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_normal_);
	glBufferData(
			GL_ARRAY_BUFFER,
			size,
			vertex_normals_,
			GL_STATIC_DRAW);


	// texcoor
	size = fh_.len_texcoor_ * sizeof(GLfloat);

	glGenBuffers(1, &buffer_texcoor_);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_texcoor_);
	glBufferData(
			GL_ARRAY_BUFFER,
			size,
			vertex_texcoor_,
			GL_STATIC_DRAW);



	// index
	size = fh_.len_indices_ * sizeof(GLushort);

	glGenBuffers(1, &buffer_indices_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_indices_);
	glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			size,
			vertex_indices_,
			GL_STATIC_DRAW);

	checkerror("glBufferData");


	
	
	glGenBuffers(1, &buff);

	int baseOffset = 0;
	glBindVertexBuffer(0, buff, baseOffset, sizeof(glutpp::vertex));

	glVertexAttribFormat(uniform_position_.o_, 3, GL_FLOAT, GL_FALSE, offsetof(position, glutpp::vertex));
	glVertexAttribBinding(loc_position_, 0);
	glVertexAttribFormat(loc_normal_, 3, GL_FLOAT, GL_FALSE, offsetof(normal, glutpp::vertex));
	glVertexAttribBinding(1, 0);
	glVertexAttribFormat(loc_texcoor_, 4, GL_FLOAT, GL_FALSE, offsetof(texcoor, glutpp::vertex));
	glVertexAttribBinding(2, 0);
	
	glBufferData(
			GL_ARRAY_BUFFER,
			size,
			vertices,
			GL_STATIC_DRAW);


	//glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);


	printf("buffer positions: %i\n",buffer_position_);
	printf("buffer normals:   %i\n",buffer_normal_);
	printf("buffer texcoor:   %i\n",buffer_texcoor_);
	printf("buffer indices:   %i\n",buffer_indices_);
	printf("texture image:    %i\n",texture_image_);

}
void glutpp::object::draw()
{
	printf("draw\n");

	glEnableVertexAttribArray(location_position_);
	glEnableVertexAttribArray(location_normal_);
	glEnableVertexAttribArray(location_texcoor_);

	printf("draw\n");









	// position
	glBindBuffer(GL_ARRAY_BUFFER, buffer_position_);checkerror("glBindBuffer");
	glVertexAttribPointer(location_position_, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//checkerror();

	// normal
	glBindBuffer(GL_ARRAY_BUFFER, buffer_normal_);
	glVertexAttribPointer(location_normal_, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// texcoor
	glBindBuffer(GL_ARRAY_BUFFER, buffer_texcoor_);
	glVertexAttribPointer(location_texcoor_, 2, GL_FLOAT, GL_FALSE, 0, 0);


	// texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_image_);
	glUniform1i(location_image_, 0);

	// element
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

	glDisableVertexAttribArray(location_position_);
	glDisableVertexAttribArray(location_normal_);
	glDisableVertexAttribArray(location_texcoor_);

	printf("draw\n");
}
void	glutpp::object::render_reflection(){}



