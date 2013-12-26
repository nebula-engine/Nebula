#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <glutpp/config.h>
#include <glutpp/shape.h>
#include <glutpp/window.h>

glutpp::shape::shape(): vertices_(NULL), indices_(NULL) {

}
int	glutpp::shape::load() {
	
	scale_ = desc_.s_.to_math();
	
	switch(desc_.type_)
	{
		case glutpp::shape_type::BOX:
			load("cube.obj");
			break;
		case glutpp::shape_type::SPHERE:
			load("sphere.obj");
			break;
		default:
			printf("invalid shape type\n");
			exit(0);
			break;
	}
	
	material_front_.load(desc_.front_);
}
void	glutpp::shape::construct(math::geo::polyhedron* poly) {
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
int	glutpp::shape::load(const char * name){
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
	for(int i = 0; i < fh_.len_vertices_; ++i) vertices_[i].print();

	return 0;
}
int	glutpp::shape::save(const char * filename){
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
void glutpp::shape::init_buffer(glutpp::window_t window, std::shared_ptr<glutpp::glsl::program> p) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	if(indices_ == NULL)
	{
		load();
	}
	
	checkerror("unknown");

	std::shared_ptr<glutpp::buffers> bufs(new glutpp::buffers);
	context_[window.get()] = bufs;

	// image
	//texture_image_.load_png("bigtux.png");

	// indices
	int size = fh_.len_indices_ * sizeof(GLushort);

	glGenBuffers(1, &bufs->indices_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs->indices_);
	glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			size,
			indices_,
			GL_STATIC_DRAW);

	checkerror("glBufferData");

	// vertices

	glGenBuffers(1, &bufs->vbo_);

	int baseOffset = 0;
	glBindBuffer(GL_ARRAY_BUFFER, bufs->vbo_);
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
void	glutpp::shape::model_load(math::mat44 space) {
	
	auto p = glutpp::__master.current_program();
	
	//auto scene = get_scene();
	
	math::mat44 model(pose_);
	
	math::mat44 scale;
	scale.SetScale(scale_);
	
	p->get_uniform(glutpp::uniform_name::e::MODEL)->load(space * model * scale);
}
int	glutpp::shape::draw(std::shared_ptr<glutpp::window> window, math::mat44 space) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	auto p = glutpp::__master.current_program();

	// initialize buffers if not already
	if(!context_[window.get()])
	{	
		init_buffer(window, p);
	}
	auto bufs = context_[window.get()];
	
	checkerror("unknown");

	p->get_attrib(glutpp::attrib_name::e::POSITION)->enable();
	p->get_attrib(glutpp::attrib_name::e::NORMAL)->enable();
	//p->get_attrib(glutpp::attrib_name::e::TEXCOOR)->enable();


	// material
	printf("load material\n");
	material_front_.load();

	// texture
	/*	glActiveTexture(GL_TEXTURE0);checkerror("glActiveTexture");
		texture_image_.bind();
		p->get_uniform(glutpp::uniform_name::e::IMAGE)->load(0);
	 */	//glUniform1i(texture_image_.o_, 0);checkerror("glUniform1i");


	printf("bind vbo\n");
	glBindBuffer(GL_ARRAY_BUFFER, bufs->vbo_); checkerror("glBindBuffer");
	printf("bind elements\n");// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs->indices_); checkerror("glBindBuffer");

	printf("load model\n");
	model_load(space);

	printf("draw\n");
	glDrawElements(GL_TRIANGLES, fh_.len_indices_, GL_UNSIGNED_SHORT, 0);checkerror("glDrawElements");
	glDrawElements(GL_LINES, fh_.len_indices_, GL_UNSIGNED_SHORT, 0);checkerror("glDrawElements");




	glBindBuffer(GL_ARRAY_BUFFER,0);checkerror("glBindBuffer");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);checkerror("glBindBuffer");

	p->get_attrib(glutpp::attrib_name::e::POSITION)->disable();
	p->get_attrib(glutpp::attrib_name::e::NORMAL)->disable();
	//p->get_attrib(glutpp::attrib_name::e::TEXCOOR)->disable();

}






