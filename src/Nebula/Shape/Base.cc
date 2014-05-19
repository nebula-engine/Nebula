#include <Nebula/debug.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Shape/Base.hh>

#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/glsl/attrib.hh>

#include <Nebula/Util/Map.hh>

Neb::Shape::Base::Base() {
}
Neb::Shape::Base::Base(Neb::Shape::Util::Parent_s parent):
	parent_(parent)
{
	NEBULA_SHAPE_BASE_FUNC;
	assert(parent);
}
Neb::Shape::Base::~Base() {}
Neb::Shape::Util::Parent_s		Neb::Shape::Base::getParent() {
	return parent_.lock();
}
physx::PxTransform			Neb::Shape::Base::getPoseGlobal() {
	NEBULA_SHAPE_BASE_FUNC;
	
	physx::PxTransform m;
	
	if(!parent_.expired()) {
		m = parent_.lock()->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}
	
	return m;
}
physx::PxTransform			Neb::Shape::Base::getPose() {
	return pose_;
}
void		Neb::Shape::Base::init() {
	NEBULA_SHAPE_BASE_FUNC
	
	auto me = std::dynamic_pointer_cast<Neb::Shape::Base>(shared_from_this());
	//auto scene = get_parent()->get_scene();
	
	// type

	// program
	if(image_.length() == 0) {
		program_ = Neb::program_name::LIGHT;
	} else {
		flag_.set(Neb::Shape::flag::e::IMAGE);

		program_ = Neb::program_name::IMAGE;
	}


	// create shape
	
	typedef Neb::Util::Parent<Neb::Shape::Base> S;
	typedef Neb::Util::Parent<Neb::Light::Base> L;
	
	for(auto it = S::map_.map_.cbegin(); it != S::map_.map_.cend(); ++it) {
		it->second.ptr_->init();
	}

	for(auto it = L::map_.map_.cbegin(); it != L::map_.map_.cend(); ++it) {
		it->second.ptr_->init();
	}
}
void Neb::Shape::Base::release() {
	NEBULA_SHAPE_BASE_FUNC

	typedef Neb::Util::Parent<Neb::Shape::Base> S;
	typedef Neb::Util::Parent<Neb::Light::Base> L;
	
	for(auto it = S::map_.map_.cbegin(); it != S::map_.map_.cend(); ++it) {
		it->second.ptr_->release();
	}

	for(auto it = L::map_.map_.cbegin(); it != L::map_.map_.cend(); ++it) {
		it->second.ptr_->release();
	}

	S::map_.map_.clear();
	L::map_.map_.clear();
}
/*void Neb::Shape::Base::cleanup() {
	NEBULA_SHAPE_BASE_FUNC

	auto s = shapes_.begin();
	while(s != shapes_.end()) {
		auto shape = s->second.ptr_;
		
		assert(shape);
		
		shape->cleanup();
		
		if(shape->any(Neb::Shape::flag::e::SHOULD_RELEASE)) {
			shape->release();

			s = shapes_.erase(s);
		} else {
			++s;
		}
	}

	auto l = lights_.begin();
	while(l != lights_.end()) {
		auto light = l->second.ptr_;
		
		assert(light);
		
		light->cleanup();

		if(light->raw_.flag_.any(Neb::Shape::flag::e::SHOULD_RELEASE)) {
			light->release();

			l = lights_.erase(l);
		} else {
			++l;
		}
	}

}*/
void Neb::Shape::Base::step(double time) {
	
	typedef Neb::Util::Parent<Neb::Shape::Base> S;
	typedef Neb::Util::Parent<Neb::Light::Base> L;
	
	for(auto it = S::map_.map_.cbegin(); it != S::map_.map_.cend(); ++it) {
		it->second.ptr_->step(time);
	}

	for(auto it = L::map_.map_.cbegin(); it != L::map_.map_.cend(); ++it) {
		it->second.ptr_->step(time);
	}

	material_front_.step(time);
}
void Neb::Shape::Base::notify_foundation_change_pose() {

	typedef Neb::Util::Parent<Neb::Shape::Base> S;
	typedef Neb::Util::Parent<Neb::Light::Base> L;
	
	for(auto it = S::map_.map_.cbegin(); it != S::map_.map_.cend(); ++it) {
		it->second.ptr_->notify_foundation_change_pose();
	}

	for(auto it = L::map_.map_.cbegin(); it != L::map_.map_.cend(); ++it) {
		it->second.ptr_->notify_foundation_change_pose();
	}
}
void Neb::Shape::Base::load_lights(int& i, physx::PxMat44 space) {
	NEBULA_SHAPE_BASE_FUNC;

	space = space * pose_;
	
	typedef Neb::Util::Parent<Neb::Light::Base> L;
	
	for(auto it = L::map_.map_.cbegin(); it != L::map_.map_.cend(); ++it) {
		if(i == Neb::Light::light_max) break;
		it->second.ptr_->load(i++, space);
	}
}
void Neb::Shape::Base::draw(Neb::Graphics::Window::Base_s window, physx::PxMat44 space) {
	space = space * pose_;

	draw_elements(window, space);
}
void		Neb::Shape::Base::model_load(physx::PxMat44 space) {
	
	auto p = Neb::App::Base::globalBase()->current_program();
	
	space.scale(physx::PxVec4(s_, 0));
	
	p->get_uniform_scalar("model")->load(space);
}
void		Neb::Shape::Base::init_buffer(Neb::Graphics::Window::Base_s window, std::shared_ptr<Neb::glsl::program> p) {
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
	if(flag_.all(Neb::Shape::flag::e::IMAGE))
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

	if(flag_.all(Neb::Shape::flag::e::IMAGE)) {
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
void		Neb::Shape::Base::draw_elements(Neb::Graphics::Window::Base_s window, physx::PxMat44 space) {
	NEBULA_SHAPE_BASE_FUNC;

	auto p = Neb::App::Base::globalBase()->use_program(program_);

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

	if(flag_.all(Neb::Shape::flag::e::IMAGE))
	{
		p->get_attrib(Neb::attrib_name::e::TEXCOOR)->enable();
	}

	// material
	//printf("load material\n");
	material_front_.load();

	// texture
	if(flag_.all(Neb::Shape::flag::e::IMAGE))
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

	if(flag_.all(Neb::Shape::flag::e::IMAGE))
	{
		p->get_attrib(Neb::attrib_name::e::TEXCOOR)->disable();
	}
}


