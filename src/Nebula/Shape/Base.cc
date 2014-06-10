#include <glm/gtx/transform.hpp>

#include <Nebula/debug.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Shape/Base.hh>

#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/glsl/attrib.hh>

#include <Galaxy-Standard/map.hpp>

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
mat4					Neb::Shape::Base::getPoseGlobal() {
	NEBULA_SHAPE_BASE_FUNC;
	
	mat4 m;
	
	if(!parent_.expired()) {
		m = parent_.lock()->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}
	
	return m;
}
mat4					Neb::Shape::Base::getPose() {
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


	Neb::Shape::Util::Parent::init();
	Neb::Light::Util::Parent::init();

}
void Neb::Shape::Base::release() {
	NEBULA_SHAPE_BASE_FUNC;

	//Neb::Util::parent<Neb::Shape::Base>::release();
	Neb::Shape::Util::Parent::release();
	Neb::Light::Util::Parent::release();
}
void		Neb::Shape::Base::step(Neb::Core::TimeStep const & ts) {

	Neb::Shape::Util::Parent::step(ts);
	
	Neb::Light::Util::Parent::step(ts);

	material_front_.step(ts);
}
void Neb::Shape::Base::load_lights(int& i, mat4 space) {
	NEBULA_SHAPE_BASE_FUNC;

	space = space * pose_;

	typedef Neb::Light::Util::Parent L;

	L::map_.for_each<0>([&] (L::map_type::iterator<0> it) {
		auto light = sp::dynamic_pointer_cast<Neb::Light::Base>(it->ptr_);
		assert(light);
		if(i == Neb::Light::light_max) return L::map_type::BREAK;
		light->load(i++, space);
		return L::map_type::CONTINUE;
	});

}
void		Neb::Shape::Base::draw(Neb::Graphics::Context::Base_s context, mat4 space) {
	space = space * pose_;

	draw_elements(context, space);
}
void		Neb::Shape::Base::model_load(mat4 space) {

	auto p = Neb::App::Base::globalBase()->current_program();

	space *= glm::scale(s_);

	p->get_uniform_scalar("model")->load(space);
}
void		Neb::Shape::Base::init_buffer(Neb::Graphics::Context::Base_s context, std::shared_ptr<Neb::glsl::program> p) {
	NEBULA_SHAPE_BASE_FUNC;

	glEnable(GL_TEXTURE_2D);

	if(mesh_.indices_ == NULL)
	{
		printf("not initialized\n");
		return;
	}

	//checkerror("unknown");

	std::shared_ptr<Neb::Shape::buffer> bufs(new Neb::Shape::buffer);
	context_[context.get()] = bufs;

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
void		Neb::Shape::Base::draw_elements(sp::shared_ptr<Neb::Graphics::Context::Base> context, mat4 space) {
	NEBULA_SHAPE_BASE_FUNC;

	auto p = Neb::App::Base::globalBase()->use_program(program_);

	// initialize buffers if not already
	//	if(!context_[window.get()])
	{	
		init_buffer(context, p);
	}
	auto bufs = context_[context.get()];

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


