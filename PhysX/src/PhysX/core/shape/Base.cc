#include <Nebula/debug.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Shape/Base.hh>

#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/glsl/attrib.hh>

#include <Nebula/Util/Map.hh>

neb::Shape::Base::Base() {
}
neb::Shape::Base::Base(sp::shared_ptr<neb::Shape::Util::Parent> parent):
	parent_(parent)
{
	NEBULA_SHAPE_BASE_FUNC;
	assert(parent);
}
neb::Shape::Base::~Base() {}
sp::shared_ptr<neb::Shape::Util::Parent>		neb::Shape::Base::getParent() {
	return parent_.lock();
}
physx::PxTransform			neb::Shape::Base::getPoseGlobal() {
	NEBULA_SHAPE_BASE_FUNC;
	
	physx::PxTransform m;
	
	if(!parent_.expired()) {
		m = parent_.lock()->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}
	
	return m;
}
physx::PxTransform			neb::Shape::Base::getPose() {
	return pose_;
}
void		neb::Shape::Base::init() {
	NEBULA_SHAPE_BASE_FUNC
	
	auto me = std::dynamic_pointer_cast<neb::Shape::Base>(shared_from_this());
	//auto scene = get_parent()->get_scene();
	
	// type

	// program
	if(image_.length() == 0) {
		program_ = neb::program_name::LIGHT;
	} else {
		flag_.set(neb::Shape::flag::e::IMAGE);

		program_ = neb::program_name::IMAGE;
	}


	// create shape
	
	typedef neb::Util::Parent<neb::Shape::Base> S;
	typedef neb::Util::Parent<neb::Light::Base> L;

	S::map_.for_each([] (S::map_type::const_iterator it) {
			it->second.ptr_->init();
			});

	L::map_.for_each([] (L::map_type::const_iterator it) {
			it->second.ptr_->init();
			});
}
void neb::Shape::Base::release() {
	NEBULA_SHAPE_BASE_FUNC;
	
	typedef neb::Util::Parent<neb::Shape::Base> S;
	typedef neb::Util::Parent<neb::Light::Base> L;

	S::map_.clear();
	L::map_.clear();
}
/*void neb::Shape::Base::cleanup() {
  NEBULA_SHAPE_BASE_FUNC

  auto s = shapes_.begin();
  while(s != shapes_.end()) {
  auto shape = s->second.ptr_;

  assert(shape);

  shape->cleanup();

  if(shape->any(neb::Shape::flag::e::SHOULD_RELEASE)) {
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

  if(light->raw_.flag_.any(neb::Shape::flag::e::SHOULD_RELEASE)) {
  light->release();

  l = lights_.erase(l);
  } else {
  ++l;
  }
  }

  }*/
void		neb::Shape::Base::step(double const & time, double const & dt) {

	typedef neb::Util::Parent<neb::Shape::Base> S;
	typedef neb::Util::Parent<neb::Light::Base> L;
	
	S::map_.for_each([&] (S::map_type::const_iterator it) {
		it->second.ptr_->step(time, dt);
	});

	L::map_.for_each([&] (L::map_type::const_iterator it) {
		it->second.ptr_->step(time, dt);
	});

	material_front_.step(time);
}
void neb::Shape::Base::notify_foundation_change_pose() {

	typedef neb::Util::Parent<neb::Shape::Base> S;
	typedef neb::Util::Parent<neb::Light::Base> L;

	S::map_.for_each([] (S::map_type::const_iterator it) {
		it->second.ptr_->notify_foundation_change_pose();
	});

	L::map_.for_each([] (L::map_type::const_iterator it) {
		it->second.ptr_->notify_foundation_change_pose();
	});
}
void neb::Shape::Base::load_lights(int& i, physx::PxMat44 space) {
	NEBULA_SHAPE_BASE_FUNC;

	space = space * pose_;

	typedef neb::Util::Parent<neb::Light::Base> L;

	L::map_.for_each([&] (L::map_type::const_iterator it) {
		if(i == neb::Light::light_max) return L::map_type::BREAK;
		it->second.ptr_->load(i++, space);
		return L::map_type::CONTINUE;
	});

}
void neb::Shape::Base::draw(sp::shared_ptr<neb::gfx::Window::Base> window, physx::PxMat44 space) {
	space = space * pose_;

	draw_elements(window, space);
}
void		neb::Shape::Base::model_load(physx::PxMat44 space) {

	auto p = neb::App::Base::globalBase()->current_program();

	space.scale(physx::PxVec4(s_, 0));

	p->get_uniform_scalar("model")->load(space);
}
void		neb::Shape::Base::init_buffer(sp::shared_ptr<neb::gfx::Window::Base> window, std::shared_ptr<neb::glsl::program> p) {
	NEBULA_SHAPE_BASE_FUNC;

	glEnable(GL_TEXTURE_2D);

	if(mesh_.indices_ == NULL)
	{
		printf("not initialized\n");
		return;
	}

	//checkerror("unknown");

	std::shared_ptr<neb::Shape::buffer> bufs(new neb::Shape::buffer);
	context_[window.get()] = bufs;

	// image
	if(flag_.all(neb::Shape::flag::e::IMAGE))
	{
		bufs->texture_.image_.reset(new neb::texture);

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
	//glBindVertexBuffer(0, vbo_, baseOffset, sizeof(neb::vertex));

	neb::vertex v;
	long off_position = (long)&v.position - (long)&v;
	long off_normal = (long)&v.normal - (long)&v;
	long off_texcoor = (long)&v.texcoor - (long)&v;

	glVertexAttribPointer(
			p->get_attrib(neb::attrib_name::e::POSITION)->o_,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(neb::vertex),
			(void*)off_position);
	//checkerror("glVertexAttribPointer");

	glVertexAttribPointer(
			p->get_attrib(neb::attrib_name::e::NORMAL)->o_,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(neb::vertex),
			(void*)off_normal);
	//checkerror("glVertexAttribPointer normal");

	if(flag_.all(neb::Shape::flag::e::IMAGE)) {
		glVertexAttribPointer(
				p->get_attrib(neb::attrib_name::e::TEXCOOR)->o_,
				2,
				GL_FLOAT,
				GL_FALSE,
				sizeof(neb::vertex),
				(void*)off_texcoor);
		//checkerror("glVertexAttribPointer texcoor");
	}

	size = mesh_.fh_.len_vertices_ * sizeof(neb::vertex);
	glBufferData(
			GL_ARRAY_BUFFER,
			size,
			mesh_.vertices_,
			GL_STATIC_DRAW);

	//checkerror("glBufferData");

	//glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}
void		neb::Shape::Base::draw_elements(sp::shared_ptr<neb::gfx::Window::Base> window, physx::PxMat44 space) {
	NEBULA_SHAPE_BASE_FUNC;

	auto p = neb::App::Base::globalBase()->use_program(program_);

	// initialize buffers if not already
	//	if(!context_[window.get()])
	{	
		init_buffer(window, p);
	}
	auto bufs = context_[window.get()];

	//checkerror("unknown");

	// attribs
	p->get_attrib(neb::attrib_name::e::POSITION)->enable();
	p->get_attrib(neb::attrib_name::e::NORMAL)->enable();

	if(flag_.all(neb::Shape::flag::e::IMAGE))
	{
		p->get_attrib(neb::attrib_name::e::TEXCOOR)->enable();
	}

	// material
	//printf("load material\n");
	material_front_.load();

	// texture
	if(flag_.all(neb::Shape::flag::e::IMAGE))
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

	p->get_attrib(neb::attrib_name::e::POSITION)->disable();
	p->get_attrib(neb::attrib_name::e::NORMAL)->disable();

	if(flag_.all(neb::Shape::flag::e::IMAGE))
	{
		p->get_attrib(neb::attrib_name::e::TEXCOOR)->disable();
	}
}


