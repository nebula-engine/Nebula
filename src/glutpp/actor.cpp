#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <png.h>

#include <math/mat44.h>
#include <math/geo/polyhedron.h>

#include <glutpp/window.h>
#include <glutpp/actor.h>
#include <glutpp/scene.h>

glutpp::actor::actor():
	type_(NONE)
{
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	glutpp::actor::init(std::shared_ptr<scene> scene)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(scene);
	
	scene_ = scene;
	
	uniforms();
	
	material_front_.init();//scene);
}
std::shared_ptr<glutpp::scene>	glutpp::actor::get_scene()
{
	assert(!scene_.expired());
	
	return scene_.lock();
}
void	glutpp::actor::uniforms()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	std::shared_ptr<scene> scene = scene_.lock();

}
void	print_vector(GLfloat* v, unsigned int m, unsigned int n)
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
void	print_vectori(GLushort* v, unsigned int m, unsigned int n)
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
void	readbuffer(GLuint buffer)
{
	GLfloat data[24*4];

	glBindBuffer(GL_ARRAY_BUFFER, buffer);	
	//checkerror("glBindBuffer");

	glGetBufferSubData(GL_ARRAY_BUFFER, 0, 1*4*sizeof(GLfloat), data);
	//checkerror("glGetBufferSubData");
}
void	glutpp::actor::construct(math::geo::polyhedron* poly)
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
int	glutpp::actor::load(const char * name)
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

	//printf("vertices: %i elements\n",fh_.len_vertices_);
	//printf("indices:  %i elements\n",fh_.len_indices_);

	// allocate
	vertices_ = new glutpp::vertex[fh_.len_vertices_];
	indices_ = new GLushort[fh_.len_indices_];

	fread(vertices_, sizeof(glutpp::vertex), fh_.len_vertices_, fp);
	fread(indices_,  sizeof(GLushort),       fh_.len_indices_,  fp);

	fclose(fp);

	// print
	//for(int i = 0; i < fh_.len_vertices_; ++i) vertices_[i].print();

	return 0;
}
int	glutpp::actor::save(const char * filename)
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

	//printf("sizeof(vertex): %i\n",(int)sizeof(glutpp::vertex));
	//printf("indices:   %i elements\n",fh_.len_indices_);
	//printf("vertices:  %i elements\n",fh_.len_vertices_);

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
void	glutpp::actor::init_buffer(std::shared_ptr<glutpp::glsl::program> p)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	checkerror("unknown");
	
	// image
	//texture_image_.load_png("bigtux.png");
	
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
			p->get_attrib(glutpp::attrib_name::e::POSITION)->o_,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glutpp::vertex),
			(void*)off_position);
	checkerror("glVertexAttribPointer");

	glVertexAttribPointer(
			p->get_attrib(glutpp::attrib_name::e::NORMAL)->o_,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glutpp::vertex),
			(void*)off_normal);
	checkerror("glVertexAttribPointer normal");

/*	glVertexAttribPointer(
			p->get_attrib(glutpp::attrib_name::e::TEXCOOR)->o_,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glutpp::vertex),
			(void*)off_texcoor);
	checkerror("glVertexAttribPointer texcoor");
*/

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
void	glutpp::actor::model_load()
{
	auto p = glutpp::__master.get_program(glutpp::program_name::e::LIGHT);
	
	auto scene = get_scene();
	
	
	math::mat44 model(pose_);

	math::mat44 scale;
	scale.SetScale(s_);
	
	model = model * scale;
	
	if(scene->all(glutpp::scene::SHADER))
	{
		p->get_uniform(glutpp::uniform_name::e::MODEL)->load(model);
	}
	else
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glMultMatrixf(model);
	}
}
void	glutpp::actor::model_unload()
{
	std::shared_ptr<scene> scene = scene_.lock();

	if(scene->all(glutpp::scene::SHADER))
	{
	}
	else
	{
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
}
void	glutpp::actor::draw()
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	auto p = glutpp::__master.get_program(glutpp::program_name::e::LIGHT);
	
	checkerror("unknown");
	
	p->get_attrib(glutpp::attrib_name::e::POSITION)->enable();
	p->get_attrib(glutpp::attrib_name::e::NORMAL)->enable();
	//p->get_attrib(glutpp::attrib_name::e::TEXCOOR)->enable();


	// material
	printf("load material\n");
	material_front_.load_shader();
	
	// texture
/*	glActiveTexture(GL_TEXTURE0);checkerror("glActiveTexture");
	texture_image_.bind();
	p->get_uniform(glutpp::uniform_name::e::IMAGE)->load(0);
*/	//glUniform1i(texture_image_.o_, 0);checkerror("glUniform1i");
	
	printf("bind vbo\n");
	glBindBuffer(GL_ARRAY_BUFFER, vbo_); checkerror("glBindBuffer");
	printf("bind elements\n");// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_indices_); checkerror("glBindBuffer");
	
	printf("load model\n");
	model_load();
	
	printf("draw\n");
	glDrawElements(GL_TRIANGLES, fh_.len_indices_, GL_UNSIGNED_SHORT, 0);checkerror("glDrawElements");
	//glDrawElements(GL_LINES, fh_.len_indices_, GL_UNSIGNED_SHORT, 0);checkerror("glDrawElements");

	printf("unload material\n");
	model_unload();

	glBindBuffer(GL_ARRAY_BUFFER,0);checkerror("glBindBuffer");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);checkerror("glBindBuffer");

	p->get_attrib(glutpp::attrib_name::e::POSITION)->disable();
	p->get_attrib(glutpp::attrib_name::e::NORMAL)->disable();
	//p->get_attrib(glutpp::attrib_name::e::TEXCOOR)->disable();

}
void	glutpp::actor::render_reflection(){}

void	glutpp::vertex::print()
{
	printf("% 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f % 2.1f\n",
			position.x,position.y,position.z,
			normal.x,normal.y,normal.z,
			texcoor.x,texcoor.y);
	//position.print();
	//normal.print();
	//texcoor.print();
}


