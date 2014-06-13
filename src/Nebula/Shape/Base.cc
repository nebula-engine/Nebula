#include <glm/gtx/transform.hpp>

#include <Galaxy-Standard/map.hpp>
#include <Galaxy-Log/log.hpp>

#include <Nebula/debug.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Shape/Base.hh>

#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/glsl/attrib.hh>
#include <Nebula/Graphics/glsl/Uniform/scalar.hpp>
#include <Nebula/Math/geo/polygon.hpp>

neb::Shape::Base::Base() {
}
neb::Shape::Base::Base(sp::shared_ptr<neb::Shape::Util::Parent> parent):
	parent_(parent),
	s_(1,1,1)
{
	NEBULA_SHAPE_BASE_FUNC;
	assert(parent);
}
neb::Shape::Base::~Base() {}
mat4					neb::Shape::Base::getPoseGlobal() {
	NEBULA_SHAPE_BASE_FUNC;
	
	mat4 m;
	
	if(parent_) {
		m = parent_->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}
	
	return m;
}
mat4					neb::Shape::Base::getPose() {
	return pose_;
}
void					neb::Shape::Base::init() {
	NEBULA_SHAPE_BASE_FUNC
	
	auto me = sp::dynamic_pointer_cast<neb::Shape::Base>(shared_from_this());
	//auto scene = get_parent()->get_scene();
	
	// type

	// program
	if(image_.length() == 0) {
		program_ = neb::program_name::LIGHT;
	} else {
		/** @todo replace this with something better... */
		//flag_.set(neb::Shape::flag::e::IMAGE);

		program_ = neb::program_name::IMAGE;
	}


	neb::Shape::Util::Parent::init();
	neb::Light::Util::Parent::init();
	
	createMesh();
}
void					neb::Shape::Base::release() {
	NEBULA_SHAPE_BASE_FUNC;

	//neb::Util::parent<neb::Shape::Base>::release();
	neb::Shape::Util::Parent::release();
	neb::Light::Util::Parent::release();
}
void					neb::Shape::Base::step(neb::core::TimeStep const & ts) {

	neb::Shape::Util::Parent::step(ts);
	
	neb::Light::Util::Parent::step(ts);

	material_front_.step(ts);
}
void					neb::Shape::Base::load_lights(neb::core::light::util::count & light_count, mat4 space) {
	NEBULA_SHAPE_BASE_FUNC;

	space = space * pose_;

	typedef neb::Light::Util::Parent L;

	L::map_.for_each<0>([&] (L::map_type::iterator<0> it) {
		auto light = sp::dynamic_pointer_cast<neb::Light::Base>(it->ptr_);
		assert(light);
		//if(i == neb::Light::light_max) return L::map_type::BREAK;
		light->load(light_count, space);
		return L::map_type::CONTINUE;
	});

}
void					neb::Shape::Base::draw(sp::shared_ptr<neb::gfx::Context::Base> context, sp::shared_ptr<neb::glsl::program> p, mat4 space) {
	space = space * pose_;

	draw_elements(context, p, space);
}
void					neb::Shape::Base::model_load(mat4 space) {

	auto p = neb::App::Base::global()->current_program();

	space *= glm::scale(s_);

	p->get_uniform_scalar("model")->load(space);
}
void					neb::Shape::Base::init_buffer(sp::shared_ptr<neb::gfx::Context::Base> context, sp::shared_ptr<neb::glsl::program> p) {
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << __PRETTY_FUNCTION__;

	glEnable(GL_TEXTURE_2D);

	if(mesh_.indices_.empty()) {
		printf("not initialized\n");
		abort();
	}

	//checkerror("unknown");

	sp::shared_ptr<neb::Shape::buffer> bufs(new neb::Shape::buffer);
	context_[context.get()] = bufs;

	// image
	if(0)//if(flag_.all(neb::Shape::flag::e::IMAGE))
	{
		bufs->texture_.image_.reset(new neb::texture);

		//bufs->texture_.image_->load_png(raw_.image_);
	}

	// indices
	int size = mesh_.indices_.size() * sizeof(GLushort);
	
	glGenBuffers(1, &bufs->indices_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs->indices_);
	glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			size,
			&mesh_.indices_[0],
			GL_STATIC_DRAW);

	//checkerror("glBufferData");

	// vertices

	glGenBuffers(1, &bufs->vbo_);

	//int baseOffset = 0;
	glBindBuffer(GL_ARRAY_BUFFER, bufs->vbo_);
	//glBindVertexBuffer(0, vbo_, baseOffset, sizeof(neb::vertex));

	math::geo::vertex v;
	long off_position = (long)&(v.p[0])  - (long)&v;
	long off_normal =   (long)&(v.n[0])  - (long)&v;
	long off_texcoor =  (long)&(v.tc[0]) - (long)&v;
	
	glVertexAttribPointer(
			p->get_attrib(neb::attrib_name::e::POSITION)->o_,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(math::geo::vertex),
			(void*)off_position);
	//checkerror("glVertexAttribPointer");

	glVertexAttribPointer(
			p->get_attrib(neb::attrib_name::e::NORMAL)->o_,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(math::geo::vertex),
			(void*)off_normal);
	//checkerror("glVertexAttribPointer normal");

	if(0) {//if(flag_.all(neb::Shape::flag::e::IMAGE)) {
		glVertexAttribPointer(
				p->get_attrib(neb::attrib_name::e::TEXCOOR)->o_,
				2,
				GL_FLOAT,
				GL_FALSE,
				sizeof(math::geo::vertex),
				(void*)off_texcoor);
		//checkerror("glVertexAttribPointer texcoor");
	}

	size = mesh_.vertices_.size() * sizeof(math::geo::vertex);
	glBufferData(
			GL_ARRAY_BUFFER,
			size,
			&mesh_.vertices_[0],
			GL_STATIC_DRAW);
	
	//checkerror("glBufferData");

	//glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}
void		neb::Shape::Base::draw_elements(sp::shared_ptr<neb::gfx::Context::Base> context, sp::shared_ptr<neb::glsl::program> p, mat4 space) {
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << __PRETTY_FUNCTION__;

	//mesh_.print(debug);
	
	assert(context);
	
	/** @todo could switching programs here leave view and proj unset? */
	
	// initialize buffers if not already
	//	if(!context_[window.get()])
	{	
		init_buffer(context, p);
	}
	auto bufs = context_[context.get()];
	assert(bufs);
	//checkerror("unknown");

	// attribs
	p->get_attrib(neb::attrib_name::e::POSITION)->enable();
	p->get_attrib(neb::attrib_name::e::NORMAL)->enable();

	if(0) //if(flag_.all(neb::Shape::flag::e::IMAGE))
	{
		p->get_attrib(neb::attrib_name::e::TEXCOOR)->enable();
	}

	// material
	//printf("load material\n");
	material_front_.load();

	// texture
	if(0) //if(flag_.all(neb::Shape::flag::e::IMAGE))
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
			mesh_.indices_.size(),
			GL_UNSIGNED_SHORT,
			0);
	//checkerror("glDrawElements");

	glDrawElements(
			GL_LINES,
			mesh_.indices_.size(),
			GL_UNSIGNED_SHORT,
			0);
	//checkerror("glDrawElements");




	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//checkerror("glBindBuffer");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//checkerror("glBindBuffer");

	p->get_attrib(neb::attrib_name::e::POSITION)->disable();
	p->get_attrib(neb::attrib_name::e::NORMAL)->disable();

	if(0) //if(flag_.all(neb::Shape::flag::e::IMAGE))
	{
		p->get_attrib(neb::attrib_name::e::TEXCOOR)->disable();
	}
}


