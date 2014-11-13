#include <string.h>
#include <stdio.h>

#include <GL/glew.h>

#include <neb/core/color/Color.hh>

#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/texture.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <png.h>

typedef neb::gfx::texture tex;

std::shared_ptr<tex>		neb::gfx::texture::makePNG(std::string filename)
{
	std::shared_ptr<tex> t(new tex());
	
	t->load_png(filename);
	
	t->init_buffer(0);

	return t;
}
neb::gfx::texture::texture():
	w_(0), h_(0), png_image_data_(0)
{}
neb::gfx::texture::~texture()
{
}
void			neb::gfx::texture::init_shadow(int w,int h, std::shared_ptr<neb::gfx::context::base>)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	
	w_ = w;
	h_ = h;
	
	target_ = GL_TEXTURE_2D_ARRAY;
	
	glGenTextures(1, &o_);
	checkerror("glGenTextures");

	glBindTexture(target_, o_);
	checkerror("glBindTexture");
	
/*	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_DEPTH_COMPONENT,
			w_,
			h_,
			0,
			GL_DEPTH_COMPONENT,
			GL_UNSIGNED_BYTE,
			NULL);
*/	
	
	GLsizei depth = 32;
	
	layer_slots_.reset(new gal::etc::slots(depth));
	
	glTexImage3D(
			target_,
			0,
			GL_DEPTH_COMPONENT,
			w_,
		       	h_,
			depth,
			0,
			GL_DEPTH_COMPONENT,
			GL_UNSIGNED_BYTE,
			NULL);

	glTexParameteri(target_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(target_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(target_, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(target_, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(target_, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(target_, GL_TEXTURE_COMPARE_FUNC, GL_GREATER);
	
	checkerror("glTexParameteri");

	glBindTexture(target_, 0);
	checkerror("glBindTexture");

}
GLuint		neb::gfx::texture::genAndBind(std::shared_ptr<neb::gfx::context::base> context)
{
	GLuint o;
	
	glGenTextures(1, &o);
	checkerror("glGenTextures");

	glBindTexture(target_, o);
	checkerror("glBindTexture");

	return o;
}
void		neb::gfx::texture::bind(neb::gfx::glsl::program::base const * const & p)
{
	/*GLuint o;
	
	// this is the function called during drawing
	// this is where we check if the buffer is ready and create it if not
	auto it = buffers_.find(context.get());
	if(it == buffers_.end()) {
		o = init_buffer(context);
	} else {
		o = it->second;
	}*/
	
	glBindTexture(target_, o_);
	checkerror("glBindTexture");
}
int		neb::gfx::texture::load_png(std::string filename)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	auto app(neb::core::app::__base::global());
	
	filename = app->share_dir_ + "media/texture/" + filename;
	
	png_byte header[8];

	FILE *fp = fopen(filename.c_str(), "rb");
	if (fp == 0)
	{
		perror(filename.c_str());
		exit(0);
	}

	// read the header
	fread(header, 1, 8, fp);

	if (png_sig_cmp(header, 0, 8))
	{
		fprintf(stderr, "error: %s is not a PNG.\n", filename.c_str());
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

	// get info about png
	png_get_IHDR(
			png_ptr,
			info_ptr,
			&w_,
			&h_,
			&bit_depth,
			&color_type,
			NULL,
			NULL,
			NULL);
	
	std::cout << "png info" << std::endl;
	std::cout << "bit depth  " << bit_depth << std::endl;
	std::cout << "color type " << color_type << std::endl;
	std::cout << "w h        " << w_ << " " << h_<< std::endl;
	
	
	// Update the png info struct.
	png_read_update_info(png_ptr, info_ptr);

	// Row size in bytes.
	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

	// glTexImage2d requires rows to be 4-byte aligned
	rowbytes += 3 - ((rowbytes-1) % 4);

	// Allocate the image_data as a big block, to be given to opengl

	png_image_data_ = (png_byte*)malloc(rowbytes * h_ * sizeof(png_byte)+15);
	if (png_image_data_ == NULL)
	{
		fprintf(stderr, "error: could not allocate memory for PNG image data\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		abort();
	}

	// row_pointers is for pointing to image_data for reading the png with libpng
	png_bytep * row_pointers = (png_bytep*)malloc(h_ * sizeof(png_bytep));
	if (row_pointers == NULL)
	{
		fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		free(png_image_data_);
		fclose(fp);
		abort();
	}

	// set the individual row_pointers to point at the correct offsets of image_data
	for (unsigned int i = 0; i < h_; i++)
	{
		row_pointers[h_ - 1 - i] = png_image_data_ + i * rowbytes;
	}

	// read the png into image_data through row_pointers
	png_read_image(png_ptr, row_pointers);

	// Generate the OpenGL texture object

	//printf("image '%s' loaded into texture object %i\n", filename, buf->texture_);

	// clean up
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	//free(image_data);
	free(row_pointers);
	fclose(fp);
	return 0;
}
GLuint			neb::gfx::texture::init_buffer(std::shared_ptr<neb::gfx::context::base> context) {

	// initialize 2D with png data

	target_ = GL_TEXTURE_2D;

	o_ = genAndBind(context);

	//buffers_[context.get()] = o;
	
	std::cout << "w " << w_ << " h " << h_ << " data " << (long int)png_image_data_ << std::endl;


	glTexImage2D(
			target_,
			0,
			GL_RGB,
			w_, h_,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			png_image_data_);

	checkerror("glTexImage2D");

	glTexParameterf(target_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(target_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	checkerror("glTexParameterf");
	
	glBindTexture(target_, 0);

	return o_;
}




void			neb::gfx::texture::draw(neb::gfx::RenderDesc const & desc)
{
	checkerror("unknown");

	auto app = neb::gfx::app::__gfx_glsl::global().lock();
	auto p = app->program_tex_;
	p->use();

	// texture
	//GLuint tex;
	//glGenTextures(1, &tex);
	//glBindTexture(GL_TEXTURE_2D, tex);

	GLenum texture_target = GL_TEXTURE_2D_ARRAY;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(texture_target, o_);
	glUniform1i(p->uniform_table_[neb::gfx::glsl::uniforms::TEX], 0);

	glTexParameteri(texture_target, GL_TEXTURE_COMPARE_MODE, GL_NONE );
	glTexParameteri(texture_target, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE );

	/*	
	 *	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	 */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	auto attrib_coord = p->attrib_table_[neb::gfx::glsl::attribs::COOR];

	// vbo
	GLuint vbo;
	glGenBuffers(1, &vbo);

	glEnableVertexAttribArray(attrib_coord);
	checkerror("glEnableVertexAttribArray %i\n", attrib_coord);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// this line fucks everything up -- not anymore! needed to bind attrib location using layout in shader
	glVertexAttribPointer(attrib_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
	checkerror("glVertexAttribPointer");


	// prep environment
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);

	// draw

	GLfloat box[4][4] = 
	{
		{-1, -1, 0, 0},
		{ 1, -1, 1, 0},
		{-1,  1, 0, 1},
		{ 1,  1, 1, 1},
	};

	checkerror("unknown");


	glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
	checkerror("glBufferData");
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	checkerror("glDrawArrays");



	checkerror("unknown");


	glDisableVertexAttribArray(attrib_coord);
	
	

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(texture_target, 0);

	checkerror("unknown");


}




