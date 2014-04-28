
#include <gru/debug.hpp>
#include <gru/master.hpp>
#include <gru/shape/shape.hpp>
#include <gru/shape/desc.hpp>
//#include <

glutpp::shape::shape::shape(glutpp::shape::parent_s parent):
	parent_(parent)
{
	GRU_SHAPE_SHAPE_FUNC

	assert(parent);

	//desc->reset();
}
glutpp::shape::shape::~shape() {

}
glutpp::shape::parent_s	glutpp::shape::shape::getParent() {
	if(!parent_.expired()) {
		return parent_.lock();
	} else {
		return glutpp::shape::parent_s();
	}
}
unsigned int glutpp::shape::shape::f() {
	return raw_.flag_;
}
void glutpp::shape::shape::f(unsigned int flag) {
	raw_.flag_ = flag;
}
Neb::Math::Mat44	glutpp::shape::shape::getPoseGlobal() {
	GRU_SHAPE_SHAPE_FUNC;
	
	Neb::Math::Mat44 m;
	
	if(!parent_.expired()) {
		m = parent_.lock()->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}
	
	return m;
}
Neb::Math::Mat44 glutpp::shape::shape::getPose() {
	return raw_.pose_;
}
void glutpp::shape::shape::init(glutpp::shape::desc_s desc) {
	GRU_SHAPE_SHAPE_FUNC

	auto me = std::dynamic_pointer_cast<glutpp::shape::shape>(shared_from_this());
	//auto scene = get_parent()->get_scene();

	i_ = desc->i_;
	raw_ = desc->raw_;
	
	// type


	// program
	if(strlen(raw_.image_) == 0) {
		program_ = glutpp::program_name::LIGHT;
	} else {
		set(glutpp::shape::flag::e::IMAGE);

		program_ = glutpp::program_name::IMAGE;
	}


	// shape
	glutpp::shape::desc_s sd;
	glutpp::shape::shape_s shape;
	for(auto it = desc->shapes_.begin(); it != desc->shapes_.end(); ++it) {
		sd = *it;
		
		//glutpp::master::Global()->shape_raw_factory_->create(desc_->type_);
		
		shape.reset(desc->construct());
		
		shape->init(sd);

		shapes_.push_back(shape);
	}

	// lights
	glutpp::light::desc_s ld;
	glutpp::light::light_s light;
	for(auto it = desc->lights_.begin(); it != desc->lights_.end(); ++it)
	{
		ld = *it;

		light.reset(new glutpp::light::light(me));

		light->init(/*scene,*/ ld);

		lights_.push_back(light);
	}

	// material
	//assert(raw_.get_vec_mat()->vec_.size() > 0);
	
	material_front_.raw_ = raw_.material_;
	
	printf("diffuse = ");
	material_front_.raw_.diffuse_.print();
}
void glutpp::shape::shape::release() {
	GRU_SHAPE_SHAPE_FUNC

	for(auto it = lights_.begin(); it != lights_.end(); ++it)
	{
		it->second->release();
	}

	lights_.clear();
}
void glutpp::shape::shape::cleanup() {
	GRU_SHAPE_SHAPE_FUNC

	auto s = shapes_.begin();
	while(s != shapes_.end()) {
		auto shape = s->second;
		assert(shape);

		shape->cleanup();

		if(shape->any(glutpp::shape::flag::e::SHOULD_RELEASE))
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

		if(light->any(glutpp::shape::flag::e::SHOULD_RELEASE)) {
			light->release();

			l = lights_.erase(l);
		} else {
			++l;
		}
	}

}
void glutpp::shape::shape::step(double time) {

	shapes_.foreach<glutpp::shape::shape>(std::bind(
				&glutpp::shape::shape::step,
				std::placeholders::_1,
				time
				));

	lights_.foreach<glutpp::light::light>(std::bind(
				&glutpp::light::light::step,
				std::placeholders::_1,
				time
				));

	material_front_.step(time);
}
void glutpp::shape::shape::notify_foundation_change_pose() {

	glutpp::shape::shape_s shape;
	glutpp::light::light_s light;

	for(auto it = shapes_.end(); it != shapes_.end(); ++it)
	{
		shape = it->second;
		shape->notify_foundation_change_pose();
	}

	for(auto it = lights_.end(); it != lights_.end(); ++it)
	{
		light = it->second;
		light->notify_foundation_change_pose();
	}
}
void glutpp::shape::shape::load_lights(int& i, Neb::Math::Mat44 space) {
	GRU_SHAPE_SHAPE_FUNC;

	space = space * raw_.pose_;

	for(auto it = lights_.begin(); it != lights_.end(); ++it)
	{
		if(i == glutpp::light::light_max) break;

		it->second->load(i++, space);
	}
}
void glutpp::shape::shape::draw(glutpp::window::window_s window, Neb::Math::Mat44 space) {
	space = space * raw_.pose_;

	draw_elements(window, space);
}
void		glutpp::shape::shape::model_load(Neb::Math::Mat44 space) {
	auto p = glutpp::master::Global()->current_program();
	
	space.scale(raw_.s_);
	
	p->get_uniform_scalar("model")->load(space);
}
void		glutpp::shape::shape::init_buffer(glutpp::window::window_s window, std::shared_ptr<glutpp::glsl::program> p) {
	GRU_SHAPE_SHAPE_FUNC;

	glEnable(GL_TEXTURE_2D);

	if(mesh_.indices_ == NULL)
	{
		printf("not initialized\n");
		return;
	}

	//checkerror("unknown");

	std::shared_ptr<glutpp::shape::buffer> bufs(new glutpp::shape::buffer);
	context_[window.get()] = bufs;

	// image
	if(all(glutpp::shape::flag::e::IMAGE))
	{
		bufs->texture_.image_.reset(new glutpp::texture);

		//bufs->texture_.image_->load_png(raw_.image_);
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

	//checkerror("glBufferData");

	// vertices

	glGenBuffers(1, &bufs->vbo_);

	//int baseOffset = 0;
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
	//checkerror("glVertexAttribPointer");

	glVertexAttribPointer(
			p->get_attrib(glutpp::attrib_name::e::NORMAL)->o_,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glutpp::vertex),
			(void*)off_normal);
	//checkerror("glVertexAttribPointer normal");

	if(all(glutpp::shape::flag::e::IMAGE)) {
		glVertexAttribPointer(
				p->get_attrib(glutpp::attrib_name::e::TEXCOOR)->o_,
				2,
				GL_FLOAT,
				GL_FALSE,
				sizeof(glutpp::vertex),
				(void*)off_texcoor);
		//checkerror("glVertexAttribPointer texcoor");
	}

	size = mesh_.fh_.len_vertices_ * sizeof(glutpp::vertex);
	glBufferData(
			GL_ARRAY_BUFFER,
			size,
			mesh_.vertices_,
			GL_STATIC_DRAW);

	//checkerror("glBufferData");

	//glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}
void		glutpp::shape::shape::draw_elements(glutpp::window::window_s window, Neb::Math::Mat44 space) {
	GRU_SHAPE_SHAPE_FUNC;

	auto p = glutpp::master::Global()->use_program(program_);

	// initialize buffers if not already
//	if(!context_[window.get()])
	{	
		init_buffer(window, p);
	}
	auto bufs = context_[window.get()];

	//checkerror("unknown");

	// attribs
	p->get_attrib(glutpp::attrib_name::e::POSITION)->enable();
	p->get_attrib(glutpp::attrib_name::e::NORMAL)->enable();

	if(all(glutpp::shape::flag::e::IMAGE))
	{
		p->get_attrib(glutpp::attrib_name::e::TEXCOOR)->enable();
	}

	// material
	//printf("load material\n");
	material_front_.load();

	// texture
	if(all(glutpp::shape::flag::e::IMAGE))
	{
		glActiveTexture(GL_TEXTURE0);
		//checkerror("glActiveTexture");
		bufs->texture_.image_->bind();
		p->get_uniform_scalar("image")->load(0);
	}

	//printf("bind vbo\n");
	glBindBuffer(GL_ARRAY_BUFFER, bufs->vbo_);
	//checkerror("glBindBuffer");
	//printf("bind elements\n");// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs->indices_);
	//checkerror("glBindBuffer");

	//printf("load model\n");
	model_load(space);

	//printf("draw\n");
	glDrawElements(
			GL_TRIANGLES,
			mesh_.fh_.len_indices_,
			GL_UNSIGNED_SHORT,
			0);
	//checkerror("glDrawElements");

	glDrawElements(
			GL_LINES,
			mesh_.fh_.len_indices_,
			GL_UNSIGNED_SHORT,
			0);
	//checkerror("glDrawElements");




	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//checkerror("glBindBuffer");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//checkerror("glBindBuffer");

	p->get_attrib(glutpp::attrib_name::e::POSITION)->disable();
	p->get_attrib(glutpp::attrib_name::e::NORMAL)->disable();

	if(all(glutpp::shape::flag::e::IMAGE))
	{
		p->get_attrib(glutpp::attrib_name::e::TEXCOOR)->disable();
	}
}
void glutpp::shape::Box::Box::createMesh() {
	mesh_.load("cube.obj");
}
void glutpp::shape::Sphere::Sphere::createMesh() {
	mesh_.load("sphere.obj");
}
void glutpp::shape::Empty::Empty::createMesh() {
	mesh_.load("sphere.obj");
}

void glutpp::shape::shape::i(int ni) {
	i_ = ni;
}
int glutpp::shape::shape::i() {
	return i_;
}


