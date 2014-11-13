#include <stdio.h>
#include <assert.h>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/util/decl.hpp>
#include <neb/core/util/log.hpp>
#include <neb/core/core/scene/base.hpp>
#include <neb/core/core/shape/base.hpp>

#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/core/light/base.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/camera/proj/base.hpp>
#include <neb/gfx/camera/view/Base.hh>
#include <neb/gfx/environ/shadow/directional.hpp>

#include <neb/phx/core/scene/base.hpp>

typedef neb::gfx::core::light::base THIS;

neb::gfx::core::light::base::base():
	ambient_(0.2,0.2,0.2,1.0),
	diffuse_(neb::core::color::color::white()),
	specular_(neb::core::color::color::white()),
	atten_const_(1.0),
	atten_linear_(0.0),
	atten_quad_(0.0),
	spot_direction_(vec3(0.0, 0.0, -1.0)),
	spot_cutoff_(1.0),
	spot_exponent_(1.0),
	spot_light_cos_cutoff_(1.0)
{
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;

	shadow_sampler_[0] = glm::vec3(-1);
	shadow_sampler_[1] = glm::vec3(-1);

}
neb::gfx::core::light::base::~base() {}
void			neb::gfx::core::light::base::init(neb::core::core::light::util::parent * const & p)
{
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__ << " " << this;

	setParent(p);

	// check if detached
	if(!hasScene())
	{
		std::cout << "skip initialization" << std::endl;
		return;
	}

	auto scene = dynamic_cast<neb::phx::core::scene::base*>(getScene());


	auto pose = getPoseGlobal();

	// register in light_array
	light_array_ = 0;

	if(!light_array_slot_)
	{
		if(!scene->light_array_[light_array_]) scene->init_light();

		assert(scene->light_array_[light_array_]);
		assert(scene->light_array_[light_array_]->size_array() != 0);

		light_array_slot_ = scene->light_array_[light_array_]->reg(
				pose.pos_,
				ambient_,
				diffuse_,
				specular_,
				atten_const_,
				atten_linear_,
				atten_quad_,
				pose.rot_ * spot_direction_,
				spot_cutoff_,
				spot_exponent_,
				glm::mat4(),
				glm::mat4(),
				glm::mat4(),
				glm::mat4(),
				glm::mat4(),
				glm::mat4(),
				glm::vec3(-1.0),
				glm::vec3(-1.0),
				(int)getType()
				);

	}

}
void			neb::gfx::core::light::base::setPose(neb::core::pose const & npose) {
	pose_ = npose;

	auto pose = getPoseGlobal();

	light_array_slot_->set<0>(pose.pos_);
	light_array_slot_->set<7>(pose.rot_ * spot_direction_);
}
void			neb::gfx::core::light::base::release() {
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
}
void			neb::gfx::core::light::base::cleanup() {
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
}
void			neb::gfx::core::light::base::dim() {
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
	/*	
	//printf("diffuse\n");
	//diffuse_.print();

	glLightfv(o_, GL_POSITION, camera_.eye_);
	glLightfv(o_, GL_AMBIENT, ambient_);
	glLightfv(o_, GL_DIFFUSE, diffuse_ * 0.2f);
	glLightfv(o_, GL_SPECULAR, math::black);checkerror(__PRETTY_FUNCTION__);
	*/
	printf("UNSUPPORTED\n");
	exit(0);
}

void		neb::gfx::core::light::base::step(gal::etc::timestep const & ts) {
	/*
	   if(shadow_environ_) {

	   auto e = std::dynamic_pointer_cast<>

	   }
	   */
}
void	neb::gfx::core::light::base::draw() {	
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
}
neb::core::pose		neb::gfx::core::light::base::getPose()
{
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;

	auto p = getParent()->getPoseGlobal();

	return p;
}
void			neb::gfx::core::light::base::load(int o, neb::core::pose const & pose) {
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;

	/** @todo way to ditinguish lights in shader */
	/*	
		auto p = neb::gfx::app::__gfx_glsl::global().lock()->current_program();

		vec3 pos = pos_;

		pos += vec3(pose.pos_);


		p->get_uniform_vector(light_type_string_ + ".position")->load(o, pos);


		p->get_uniform_vector(light_type_string_ + ".ambient")->load(o, (glm::vec4)ambient_);
		p->get_uniform_vector(light_type_string_ + ".diffuse")->load(o, (glm::vec4)diffuse_);
		p->get_uniform_vector(light_type_string_ + ".specular")->load(o, (glm::vec4)specular_);
		*/

}
void	neb::gfx::core::light::base::load_shadow() {
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
	/*	auto p = neb::master::Global()->current_program();

		math::mat44 biasMatrix(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f);

		math::mat44 textureMatrix = biasMatrix * camera_.proj() * camera_.view();

		uniform_matrix_shadow_.load_matrix4fv(textureMatrix);

	// texture
	glActiveTexture(GL_TEXTURE1);
	texture_shadow_map_.bind();
	uniform_tex_shadow_.load_1i(1);
	*/
}
void	neb::gfx::core::light::base::RenderLightPOV()
{
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
	/*
	   std::shared_ptr<scene> scene = scene_.lock();

	//First pass - from light's point of view
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);

	camera_.load_shader();
	*/	/*
		   glMatrixMode(GL_PROJECTION);
		   glLoadMatrixf(camera_.proj());

		   glMatrixMode(GL_MODELVIEW);
		   glLoadMatrixf(camera_.view());

		   glViewport(0, 0, texture_shadow_map_.w_, texture_shadow_map_.h_);
		   */

	//window_->lights_updateGL();

	// Use viewport the same size as the shadow map

	// Draw back faces into the shadow map
	/*	glCullFace(GL_FRONT);

	// Disable color writes, and use flat shading for speed
	glShadeModel(GL_FLAT);
	glColorMask(0, 0, 0, 0);

	//Draw the scene
	scene->draw_shader();

	//Read the depth buffer into the shadow map texture
	texture_shadow_map_.bind();

	glCopyTexSubImage2D(
	GL_TEXTURE_2D,
	0, 0, 0, 0, 0,
	texture_shadow_map_.w_, texture_shadow_map_.h_);

	//restore states
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glColorMask(1, 1, 1, 1);
	*/
	checkerror("unknown");
}
void	neb::gfx::core::light::base::RenderShadowPost()
{
	//Disable textures and texgen
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);

	glDisable(GL_ALPHA_TEST);
	checkerror(__PRETTY_FUNCTION__);
}
void	THIS::load(ba::polymorphic_iarchive & ar, unsigned int const & v)
{
	__serialize(ar,v);
}
void	THIS::save(ba::polymorphic_oarchive & ar, unsigned int const & v) const
{
	const_cast<THIS*>(this)->__serialize(ar,v);
}







