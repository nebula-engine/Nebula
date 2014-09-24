#include <gal/log/log.hpp>

#include <glm/gtx/transform.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/math/geo/polyhedron.hh>

#include <neb/gfx/mesh/instanced.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/gfx/core/shape/box.hpp>
#include <neb/gfx/util/log.hpp>


neb::gfx::core::shape::box::box()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
void neb::gfx::core::shape::box::box::createMesh() {
	//mesh_.load("cube.obj");
	
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	if(!hasScene()) return;

	/*
	math::geo::cuboid cube(1.0,1.0,1.0);
	
	mesh_.reset(new neb::gfx::mesh);
	mesh_->construct(&cube);
	*/
	
	auto scene = dynamic_cast<neb::phx::core::scene::base*>(getScene());
	
	if(!mesh_slot_)
	{
		LOG(lg, neb::gfx::sl, debug) << "mesh registered";


		auto model = getPoseGlobal().mat4_cast() * glm::scale(scale_);

		auto dif = neb::core::color::ucolor8888::rand();
		auto amb = neb::core::color::color::gray(0.2);
		auto spc = neb::core::color::color::white();
		auto emi = neb::core::color::color::black();
		
		LOG(lg, neb::gfx::sl, debug) << "diffuse   " << std::hex << dif;
		LOG(lg, neb::gfx::sl, debug) << "diffuse r " << std::hex << (unsigned int)dif.r;
		LOG(lg, neb::gfx::sl, debug) << "diffuse g " << std::hex << (unsigned int)dif.g;
		LOG(lg, neb::gfx::sl, debug) << "diffuse b " << std::hex << (unsigned int)dif.b;
		LOG(lg, neb::gfx::sl, debug) << "diffuse a " << std::hex << (unsigned int)dif.a;
		//dif.print();
		LOG(lg, neb::gfx::sl, debug) << "ambient";
		//amb.print();
		LOG(lg, neb::gfx::sl, debug) << "specular";
		//spc.print();
		LOG(lg, neb::gfx::sl, debug) << "emission";
		//emi.print();

		assert(scene->meshes_.cuboid_);

		mesh_slot_ = scene->meshes_.cuboid_->instances_->reg(
				model,
				glm::vec4(-1.0,-1.0,-1.0,-1.0),
				(unsigned int)dif,
				amb,
				spc,
				emi,
				100.0
				);
	}
	
	//mesh_->texture_.reset(new neb::gfx::texture);
	//mesh_->texture_->load_png("/nfs/stak/students/r/rymalc/Documents/Pictures/crab.png", bufs);

}


