#include <gru/shape/shape.hpp>

glutpp::shape::shape::shape(glutpp::shape::parent_s parent):
	parent_(parent)
{
	printf("%s\n",__PRETTY_FUNCTION__);

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
	return raw_.get_raw_base()->flag_;
}
void glutpp::shape::shape::f(unsigned int flag) {
	raw_.get_raw_base()->flag_ = flag;
}
math::mat44<double>	glutpp::shape::shape::getPoseGlobal() {
	GLUTPP_DEBUG_1_FUNCTION;
	
	math::mat44<double> m;
	
	if(!parent_.expired()) {
		m = parent_.lock()->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}
	
	return m;
}
math::mat44<double> glutpp::shape::shape::getPose() {
	return raw_.get_raw_base()->pose_;
}
void glutpp::shape::shape::init(glutpp::shape::desc_s desc) {
	GLUTPP_DEBUG_0_FUNCTION;

	auto me = std::dynamic_pointer_cast<glutpp::shape::shape>(shared_from_this());
	//auto scene = get_parent()->get_scene();

	i_ = desc->get_id()->i_;
	raw_ = *desc->get_raw();

	// type
	switch(raw_.get_raw_base()->type_) {
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
	if(strlen(raw_.get_raw_base()->image_) == 0)
	{
		program_ = glutpp::program_name::LIGHT;
	}
	else
	{
		set(glutpp::shape::flag::e::IMAGE);

		program_ = glutpp::program_name::IMAGE;
	}


	// shape
	glutpp::shape::desc_s sd;
	glutpp::shape::shape_s shape;
	for(auto it = desc->get_shapes()->vec_.begin(); it != desc->get_shapes()->vec_.end(); ++it)
	{
		sd = std::get<0>(*it);

		shape.reset(new glutpp::shape::shape(me));

		shape->init(sd);

		shapes_.push_back(shape);
	}

	// lights
	glutpp::light::desc_s ld;
	glutpp::light::light_s light;
	for(auto it = desc->get_lights()->vec_.begin(); it != desc->get_lights()->vec_.end(); ++it)
	{
		ld = std::get<0>(*it);

		light.reset(new glutpp::light::light(me));

		light->init(/*scene,*/ ld);

		lights_.push_back(light);
	}

	// material
	//assert(raw_.get_vec_mat()->vec_.size() > 0);
	
	if(!raw_.get_vec_mat()->vec_.empty())
	{
		material_front_.raw_ = raw_.get_vec_mat()->vec_.at(0);
	}
	
	printf("diffuse = ");
	material_front_.raw_.diffuse_.print();
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
void glutpp::shape::shape::load_lights(int& i, math::mat44<double> space) {
	GLUTPP_DEBUG_1_FUNCTION;

	space = space * raw_.get_raw_base()->pose_;

	for(auto it = lights_.begin(); it != lights_.end(); ++it)
	{
		if(i == glutpp::light::light_max) break;

		it->second->load(i++, space);
	}
}
void glutpp::shape::shape::draw(glutpp::window::window_s window, math::mat44<double> space) {
	space = space * raw_.get_raw_base()->pose_;

	switch(raw_.get_raw_base()->type_)
	{
		case glutpp::shape::type::e::BOX:
		case glutpp::shape::type::e::SPHERE:
			draw_elements(window, space);
			break;
		case glutpp::shape::type::e::EMPTY:
			break;
	}
}
void		glutpp::shape::shape::model_load(math::mat44<double> space) {
	auto p = glutpp::master::Global()->current_program();

	math::vec3<double> s(raw_.get_raw_base()->s_);

	math::mat44<double> scale;
	scale.SetScale(s);

	p->get_uniform_scalar("model")->load(space * scale);
}
void		glutpp::shape::shape::init_buffer(glutpp::window::window_s window, std::shared_ptr<glutpp::glsl::program> p) {
	GLUTPP_DEBUG_0_FUNCTION;

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
void glutpp::shape::shape::draw_elements(glutpp::window::window_s window, math::mat44<double> space) {
	GLUTPP_DEBUG_1_FUNCTION;

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
void glutpp::shape::shape::i(int ni) {
	i_ = ni;
}
int glutpp::shape::shape::i() {
	return i_;
}


