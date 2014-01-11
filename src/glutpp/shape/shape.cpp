#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glutpp/config.h>
#include <glutpp/shape/shape.h>
#include <glutpp/window/window.h>
#include <glutpp/texture.h>


glutpp::shape::shape::shape(
		glutpp::actor::actor_s actor):
	actor_(actor)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(actor);

	//desc->reset();
}
glutpp::shape::shape::~shape() {

}
unsigned int glutpp::shape::shape::f() {
	return raw_.flag_;
}
void glutpp::shape::shape::f(unsigned int flag) {
	raw_.flag_ = flag;
}
glutpp::actor::actor_s glutpp::shape::shape::get_actor() {
	assert(!actor_.expired());
	
	return actor_.lock();
}
void glutpp::shape::shape::init(glutpp::shape::desc_s desc) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	auto me = std::dynamic_pointer_cast<glutpp::shape::shape>(shared_from_this());
	auto scene = get_actor()->get_scene();
	
	i_ = desc->get_id()->i_;
	raw_ = *desc->get_raw();
	
	// type
	switch(raw_.type_)
	{
		case glutpp::shape::type::BOX:
			mesh_.load("cube.obj");
			break;
		case glutpp::shape::type::SPHERE:
			mesh_.load("sphere.obj");
			break;
		case glutpp::shape::type::EMPTY:
			break;
		default:
			printf("invalid shape type\n");
			exit(0);
			break;
	}

	// program
	if(strlen(raw_.image_) == 0)
	{
		raw_.program_ = glutpp::program_name::LIGHT;
	}
	else
	{
		set(glutpp::shape::shape::flag::IMAGE);
		
		raw_.program_ = glutpp::program_name::IMAGE;
	}

	// lights
	glutpp::light::desc_s ld;
	glutpp::light::light_s light;
	for(auto it = desc->get_lights()->vec_.begin(); it != desc->get_lights()->vec_.end(); ++it)
	{
		ld = std::get<0>(*it);

		light.reset(new glutpp::light::light(me));
		
		light->init(scene, ld);
		
		lights_.push_back(light);
	}
	
	// material
	material_front_.load(raw_.front_);
	
}
void glutpp::shape::shape::release() {
	GLUTPP_DEBUG_0_FUNCTION;
	
	for(auto it = lights_.begin(); it != lights_.end(); ++it)
	{
		it->second->release();
	}
	
	lights_.clear();
}
void glutpp::shape::shape::cleanup() {
	GLUTPP_DEBUG_1_FUNCTION;

	auto s = shapes_.begin();
	while(s != shapes_.end()) {
		auto shape = s->second;
		assert(shape);
		
		shape->cleanup();
		
		if(shape->any(SHOULD_DELETE))
		{
			shape->release();
			
			s = shapes_.erase(s);
		}
		else
		{
			++s;
		}
	}
	
	auto l = lights_.begin();
	while(l != lights_.end()) {
		auto light = l->second;
		assert(light);

		light->cleanup();

		if(light->any(SHOULD_DELETE)) {
			light->release();

			l = lights_.erase(l);
		} else {
			++l;
		}
	}

}
math::mat44 glutpp::shape::shape::get_pose() {

	assert(!actor_.expired());

	math::mat44 m(raw_.pose_);

	m = actor_.lock()->get_pose() * m;

	return m;
}
void glutpp::shape::shape::load_lights(int& i) {

	//printf("%s\n",__PRETTY_FUNCTION__);

	for(auto it = lights_.begin(); it != lights_.end(); ++it)
	{
		if(i == glutpp::light::light_max) break;

		it->second->load(i++);
	}
}
void glutpp::shape::shape::init_buffer(
		glutpp::window::window_s window,
		std::shared_ptr<glutpp::glsl::program> p) {
	GLUTPP_DEBUG_0_FUNCTION;

	glEnable(GL_TEXTURE_2D);

	if(mesh_.indices_ == NULL)
	{
		printf("not initialized\n");
		return;
	}

	checkerror("unknown");

	std::shared_ptr<glutpp::shape::buffers> bufs(new glutpp::shape::buffers);
	context_[window.get()] = bufs;

	// image
	if(all(glutpp::shape::shape::flag::IMAGE))
	{
		bufs->texture_.image_.reset(new glutpp::texture);

		bufs->texture_.image_->load_png(raw_.image_);
	}

	// indices
	int size = mesh_.fh_.len_indices_ * sizeof(GLushort);

	glGenBuffers(1, &bufs->indices_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs->indices_);
	glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			size,
			mesh_.indices_,
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

	if(all(glutpp::shape::shape::flag::IMAGE)) {
		glVertexAttribPointer(
				p->get_attrib(glutpp::attrib_name::e::TEXCOOR)->o_,
				2,
				GL_FLOAT,
				GL_FALSE,
				sizeof(glutpp::vertex),
				(void*)off_texcoor);
		checkerror("glVertexAttribPointer texcoor");
	}
	
	size = mesh_.fh_.len_vertices_ * sizeof(glutpp::vertex);
	glBufferData(
			GL_ARRAY_BUFFER,
			size,
			mesh_.vertices_,
			GL_STATIC_DRAW);

	checkerror("glBufferData");

	//glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}
void glutpp::shape::shape::model_load(math::mat44 space) {

	auto p = glutpp::__master.current_program();

	//auto scene = get_scene();

	math::mat44 model(raw_.pose_);
	
	math::vec3 s(raw_.s_);

	math::mat44 scale;
	scale.SetScale(s);

	p->get_uniform(glutpp::uniform_name::e::MODEL)->load(space * model * scale);
}
void glutpp::shape::shape::draw(std::shared_ptr<glutpp::window::window> window, math::mat44 space) {

	switch(raw_.type_)
	{
		case BOX:
		case SPHERE:
			draw_elements(window, space);
			break;
		case EMPTY:
			break;
	}

}
void glutpp::shape::shape::draw_elements(std::shared_ptr<glutpp::window::window> window, math::mat44 space) {
	GLUTPP_DEBUG_1_FUNCTION;

	auto p = glutpp::__master.use_program(raw_.program_);

	// initialize buffers if not already
	if(!context_[window.get()])
	{	
		init_buffer(window, p);
	}
	auto bufs = context_[window.get()];

	checkerror("unknown");

	// attribs
	p->get_attrib(glutpp::attrib_name::e::POSITION)->enable();
	p->get_attrib(glutpp::attrib_name::e::NORMAL)->enable();

	if(all(glutpp::shape::shape::flag::IMAGE))
	{
		p->get_attrib(glutpp::attrib_name::e::TEXCOOR)->enable();
	}

	// material
	//printf("load material\n");
	material_front_.load();

	// texture
	if(all(glutpp::shape::shape::flag::IMAGE))
	{
		glActiveTexture(GL_TEXTURE0);
		checkerror("glActiveTexture");
		bufs->texture_.image_->bind();
		p->get_uniform(glutpp::uniform_name::e::IMAGE)->load(0);
	}

	//printf("bind vbo\n");
	glBindBuffer(GL_ARRAY_BUFFER, bufs->vbo_); checkerror("glBindBuffer");
	//printf("bind elements\n");// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs->indices_); checkerror("glBindBuffer");

	//printf("load model\n");
	model_load(space);

	//printf("draw\n");
	glDrawElements(
			GL_TRIANGLES,
			mesh_.fh_.len_indices_,
			GL_UNSIGNED_SHORT,
			0);
	checkerror("glDrawElements");

	glDrawElements(
			GL_LINES,
			mesh_.fh_.len_indices_,
			GL_UNSIGNED_SHORT,
			0);
	checkerror("glDrawElements");




	glBindBuffer(GL_ARRAY_BUFFER,0);checkerror("glBindBuffer");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);checkerror("glBindBuffer");

	p->get_attrib(glutpp::attrib_name::e::POSITION)->disable();
	p->get_attrib(glutpp::attrib_name::e::NORMAL)->disable();

	if(all(glutpp::shape::shape::flag::IMAGE))
	{
		p->get_attrib(glutpp::attrib_name::e::TEXCOOR)->disable();
	}
}
void glutpp::shape::shape::i(int ni) {
	i_ = ni;
}
int glutpp::shape::shape::i() {
	return i_;
}



