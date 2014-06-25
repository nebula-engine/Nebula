#include <glm/gtx/transform.hpp>

#include <Galaxy-Standard/map.hpp>
#include <Galaxy-Log/log.hpp>

#include <neb/debug.hh>
//#include <neb/app/Base.hh>
#include <neb/core/shape/Base.hh>

#include <neb/core/light/Base.hh>
//#include <neb/gfx/glsl/attrib.hh>
//#include <neb/gfx/glsl/Uniform/scalar.hpp>
#include <neb/math/geo/polygon.hpp>

neb::gfx::core::shape::base::base(sp::shared_ptr<neb::core::shape::util::parent> parent):
	neb::core::shape::base(parent)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core shape", debug) << __PRETTY_FUNCTION__;
	assert(parent);
}
neb::gfx::core::shape::base::~base() {}
void					neb::core::shape::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core shape", debug) << __PRETTY_FUNCTION__;

	createMesh();
}
void					neb::gfx::core::shape::base::step(gal::std::timestep const & ts) {

	material_front_.step(ts);
}
void					neb::gfx::core::shape::base::load_lights(neb::core::light::util::count & light_count, neb::core::pose const & pose) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core shape", debug) << __PRETTY_FUNCTION__;

	auto npose = pose * pose_;

	typedef neb::Light::util::parent L;

	auto lambda_light = [&] (L::map_type::iterator<0> it) {
		auto light = sp::dynamic_pointer_cast<neb::Light::base>(it->ptr_);
		assert(light);
		//if(i == neb::Light::light_max) return L::map_type::BREAK;
		
		if(light->light_gfx_) {
			light->light_gfx_->load(light_count, npose);
		}
		return L::map_type::CONTINUE;
	};

	L::map_.for_each<0>(lambda_light);

}
void					neb::gfx::core::shape::base::draw(
		sp::shared_ptr<neb::gfx::context::base> context,
		sp::shared_ptr<neb::glsl::program> p,
		neb::core::pose const & pose) {

	auto npose = pose * pose_;

	draw_elements(context, p, npose);
}
void					neb::gfx::core::shape::base::model_load(neb::core::pose const & pose) {

	auto p = neb::app::base::global()->current_program();

	mat4 space = pose.mat4_cast() * glm::scale(s_);

	p->get_uniform_scalar("model")->load(space);
}
void					neb::gfx::core::shape::base::init_buffer(sp::shared_ptr<neb::gfx::context::base> context, sp::shared_ptr<neb::glsl::program> p) {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << __PRETTY_FUNCTION__;

	glEnable(GL_TEXTURE_2D);

	if(mesh_.indices_.empty()) {
		printf("not initialized\n");
		abort();
	}

	//checkerror("unknown");

	sp::shared_ptr<neb::core::shape::buffer> bufs(new neb::core::shape::buffer);
	context_[context.get()] = bufs;

	// image
	if(0)//if(flag_.all(neb::core::shape::flag::e::IMAGE))
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

	if(0) {//if(flag_.all(neb::core::shape::flag::e::IMAGE)) {
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
	void		neb::gfx::core::shape::base::draw_elements(
			sp::shared_ptr<neb::gfx::context::base> context,
			sp::shared_ptr<neb::glsl::program> p,
			neb::core::pose const & pose) {
		if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << __PRETTY_FUNCTION__;

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

		if(0) //if(flag_.all(neb::core::shape::flag::e::IMAGE))
		{
			p->get_attrib(neb::attrib_name::e::TEXCOOR)->enable();
		}

		// material
		//printf("load material\n");
		material_front_.load();

		// texture
		if(0) //if(flag_.all(neb::core::shape::flag::e::IMAGE))
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
		model_load(pose);

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

		if(0) //if(flag_.all(neb::core::shape::flag::e::IMAGE))
		{
			p->get_attrib(neb::attrib_name::e::TEXCOOR)->disable();
		}
	}


