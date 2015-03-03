#ifndef __PX_CONTENT_ACTOR_RIGIDDYNAMIC_BASE_HPP
#define __PX_CONTENT_ACTOR_RIGIDDYNAMIC_BASE_HPP

#include <PxPhysicsAPI.h>

#include <neb/fnd/util/macro.hpp>

#include <neb/fnd/core/actor/rigiddynamic/Base.hpp>
#include <neb/phx/core/actor/rigidbody/base.hpp>
#include <neb/phx/core/actor/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace rigiddynamic {
	class base:
		//virtual public neb::fnd::core::actor::rigiddynamic::base,
		virtual public neb::phx::core::actor::rigidbody::base
	{
		public:
			using CHILD::get_fnd_app;
			//base(std::shared_ptr<neb::phx::core::actor::util::parent>);
			NEB_INIT_FUNC;
			virtual void					release() = 0;
		public:
			virtual void					step(gal::etc::timestep const & ts) = 0;
			virtual void					create_physics();
			virtual void					init_physics();
			//virtual void					add_force(double) = 0;
			//virtual void					setPose(neb::fnd::pose const & pose);
/*
			gal::math::pose				getPoseGlobal() const;
			gal::math::pose				getPose() const;
			virtual void	load(ba::polymorphic_iarchive & ar, unsigned int const &) = 0;
			virtual void	save(ba::polymorphic_oarchive & ar, unsigned int const &) const = 0;
			BOOST_SERIALIZATION_SPLIT_MEMBER();
			*/
	};


}}}}}

#endif


