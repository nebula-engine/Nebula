#include <Nebula/debug.hpp>
#include <Nebula/master.hpp>
#include <Nebula/shape/shape.hpp>
#include <Nebula/shape/desc.hpp>
#include <Nebula/Graphics/light/light.hpp>
#include <Nebula/Graphics/glsl/attrib.hpp>
#include <Nebula/Map.hpp>
#include <Nebula/Memory/smart_ptr.hpp>

Neb::Shape::shape::shape(Neb::Shape::parent_w parent): parent_(parent) {
	NEBULA_SHAPE_BASE_FUNC;
	assert(parent);
}
Neb::Shape::shape::~shape() {}
Neb::Shape::parent_w		Neb::Shape::shape::getParent() {
	if(!parent_.expired()) {
		return parent_.lock();
	} else {
		return boost::shared_ptr<Neb::Shape::parent>();
	}
}
gal::flag::flag_type		Neb::Shape::shape::f() {
	return raw_->flag_;
}
void Neb::Shape::shape::f(unsigned int flag) {
	raw_->flag_ = flag;
}
Neb::Math::Mat44	Neb::Shape::shape::getPoseGlobal() {
	NEBULA_SHAPE_BASE_FUNC;
	
	Neb::Math::Mat44 m;
	
	if(!parent_.expired()) {
		m = parent_.lock()->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}
	
	return m;
}
Neb::Math::Mat44 Neb::Shape::shape::getPose() {
	return raw_->pose_;
}
void		Neb::Shape::shape::init(Neb::Shape::desc_w desc) {
	NEBULA_SHAPE_BASE_FUNC
	
	auto me = boost::dynamic_pointer_cast<Neb::Shape::shape>(shared_from_this());
	//auto scene = get_parent()->get_scene();
	
	i_ = desc->i_;
	raw_.swap(desc->raw_wrapper_.ptr_);
	
	// type


	// program
	if(strlen(raw_->image_) == 0) {
		program_ = Neb::program_name::LIGHT;
	} else {
		set(Neb::Shape::flag::e::IMAGE);

		program_ = Neb::program_name::IMAGE;
	}


	// shape
	boost::shared_ptr<Neb::Shape::desc> sd;
	Neb::unique_ptr<Neb::Shape::shape> shape;
	for(auto it = desc->shapes_.begin(); it != desc->shapes_.end(); ++it) {
		shape.reset(desc->construct());
		shape->init(*it);
		
		//Neb::Map<Neb::Shape::shape>::value_type p;

		//shapes_.map_.insert(p);

		shapes_.push_back(shape);
	}

	// lights
	boost::shared_ptr<Neb::light::desc> ld;
	Neb::unique_ptr<Neb::light::light> light;
	for(auto it = desc->lights_.begin(); it != desc->lights_.end(); ++it) {
		light.reset(new Neb::light::light(me));

		light->init(*it);
		
		//Neb::Map<Neb::light::light>::value_type p;
		
		//lights_.map_.insert(p);
	
		lights_.push_back(light);
	}

	// material
	//assert(raw_.get_vec_mat()->vec_.size() > 0);
	
	material_front_.raw_ = raw_->material_;
	
	printf("diffuse = ");
	material_front_.raw_.diffuse_.print();
}
void Neb::Shape::shape::release() {
	NEBULA_SHAPE_BASE_FUNC

	for(auto it = lights_.begin(); it != lights_.end(); ++it)
	{
		it->second->release();
	}

	lights_.clear();
}
void Neb::Shape::shape::cleanup() {
	NEBULA_SHAPE_BASE_FUNC

	auto s = shapes_.begin();
	while(s != shapes_.end()) {
		//auto shape = s->second;
		assert(s->second);
		
		s->second->cleanup();
		
		if(s->second->any(Neb::Shape::flag::e::SHOULD_RELEASE)) {
			s->second->release();

			s = shapes_.erase(s);
		} else {
			++s;
		}
	}

	auto l = lights_.begin();
	while(l != lights_.end()) {
		assert(l->second);

		l->second->cleanup();

		if(l->second->any(Neb::Shape::flag::e::SHOULD_RELEASE)) {
			l->second->release();

			l = lights_.erase(l);
		} else {
			++l;
		}
	}

}
void Neb::Shape::shape::step(double time) {

	for(auto it = shapes_.map_.begin(); it != shapes_.map_.end(); ++it) {
		it->second->step(time);
	}
	/*shapes_.foreach<Neb::Shape::shape>(std::bind(
				&Neb::Shape::shape::step,
				std::placeholders::_1,
				time
				));
*/
	for(auto it = lights_.map_.begin(); it != lights_.map_.end(); ++it) {
		it->second->step(time);
	}
	
/*	lights_.foreach<Neb::light::light>(std::bind(
				&Neb::light::light::step,
				std::placeholders::_1,
				time
				));
*/
	material_front_.step(time);
}
void Neb::Shape::shape::notify_foundation_change_pose() {

	boost::shared_ptr<Neb::light::light> light;
	
	for(auto it = shapes_.end(); it != shapes_.end(); ++it)
	{
		it->second->notify_foundation_change_pose();
	}

	for(auto it = lights_.end(); it != lights_.end(); ++it)
	{
		it->second->notify_foundation_change_pose();
	}
}
void Neb::Shape::shape::load_lights(int& i, Neb::Math::Mat44 space) {
	NEBULA_SHAPE_BASE_FUNC;

	space = space * raw_->pose_;

	for(auto it = lights_.begin(); it != lights_.end(); ++it)
	{
		if(i == Neb::light::light_max) break;

		it->second->load(i++, space);
	}
}
void Neb::Shape::shape::draw(Neb::window::window_s window, Neb::Math::Mat44 space) {
	space = space * raw_->pose_;

	draw_elements(window, space);
}
void		Neb::Shape::shape::model_load(Neb::Math::Mat44 space) {
	auto p = Neb::master::global()->current_program();
	
	space.scale(physx::PxVec4(raw_->s_, 0));
	
	p->get_uniform_scalar("model")->load(space);
}
void		Neb::Shape::shape::init_buffer(Neb::window::window_s window, std::shared_ptr<Neb::glsl::program> p) {
	NEBULA_SHAPE_BASE_FUNC;

	glEnable(GL_TEXTURE_2D);

	if(mesh_.indices_ == NULL)
	{
		printf("not initialized\n");
		return;
	}

	//checkerror("unknown");

	std::shared_ptr<Neb::Shape::buffer> bufs(new Neb::Shape::buffer);
	context_[window.get()] = bufs;

	// image
	if(all(Neb::Shape::flag::e::IMAGE))
	{
		bufs->texture_.image_.reset(new Neb::texture);

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
	//glBindVertexBuffer(0, vbo_, baseOffset, sizeof(Neb::vertex));

	Neb::vertex v;
	long off_position = (long)&v.position - (long)&v;
	long off_normal = (long)&v.normal - (long)&v;
	long off_texcoor = (long)&v.texcoor - (long)&v;

	glVertexAttribPointer(
			p->get_attrib(Neb::attrib_name::e::POSITION)->o_,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Neb::vertex),
			(void*)off_position);
	//checkerror("glVertexAttribPointer");

	glVertexAttribPointer(
			p->get_attrib(Neb::attrib_name::e::NORMAL)->o_,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Neb::vertex),
			(void*)off_normal);
	//checkerror("glVertexAttribPointer normal");

	if(all(Neb::Shape::flag::e::IMAGE)) {
		glVertexAttribPointer(
				p->get_attrib(Neb::attrib_name::e::TEXCOOR)->o_,
				2,
				GL_FLOAT,
				GL_FALSE,
				sizeof(Neb::vertex),
				(void*)off_texcoor);
		//checkerror("glVertexAttribPointer texcoor");
	}

	size = mesh_.fh_.len_vertices_ * sizeof(Neb::vertex);
	glBufferData(
			GL_ARRAY_BUFFER,
			size,
			mesh_.vertices_,
			GL_STATIC_DRAW);

	//checkerror("glBufferData");

	//glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}
void		Neb::Shape::shape::draw_elements(Neb::window::window_s window, Neb::Math::Mat44 space) {
	NEBULA_SHAPE_BASE_FUNC;

	auto p = Neb::master::global()->use_program(program_);

	// initialize buffers if not already
//	if(!context_[window.get()])
	{	
		init_buffer(window, p);
	}
	auto bufs = context_[window.get()];

	//checkerror("unknown");

	// attribs
	p->get_attrib(Neb::attrib_name::e::POSITION)->enable();
	p->get_attrib(Neb::attrib_name::e::NORMAL)->enable();

	if(all(Neb::Shape::flag::e::IMAGE))
	{
		p->get_attrib(Neb::attrib_name::e::TEXCOOR)->enable();
	}

	// material
	//printf("load material\n");
	material_front_.load();

	// texture
	if(all(Neb::Shape::flag::e::IMAGE))
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

	p->get_attrib(Neb::attrib_name::e::POSITION)->disable();
	p->get_attrib(Neb::attrib_name::e::NORMAL)->disable();

	if(all(Neb::Shape::flag::e::IMAGE))
	{
		p->get_attrib(Neb::attrib_name::e::TEXCOOR)->disable();
	}
}
void Neb::Shape::Box::Box::createMesh() {
	mesh_.load("cube.obj");
}
void Neb::Shape::Sphere::Sphere::createMesh() {
	mesh_.load("sphere.obj");
}
void Neb::Shape::Empty::Empty::createMesh() {
	mesh_.load("sphere.obj");
}

void Neb::Shape::shape::i(int ni) {
	i_ = ni;
}
int Neb::Shape::shape::i() {
	return i_;
}


