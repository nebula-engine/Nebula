#ifndef NEB_FINAL_GFX_PHX_CORE_SCENE_BASE_HPP
#define NEB_FINAL_GFX_PHX_CORE_SCENE_BASE_HPP


#include <neb/phx/core/scene/base.hpp>

#include <neb/core/core/actor/util/decl.hpp>

#include <neb/fin/gfx_phx/core/actor/util/decl.hpp>

typedef weak_ptr<neb::core::core::actor::base> wbase;

namespace neb { namespace fin { namespace gfx_phx { namespace core { namespace scene {
	class base:
		virtual public phx::core::scene::base
	{
		public:
			base();

			virtual void			init(parent_t * const & p);
			virtual void			release();
			virtual void			step(gal::etc::timestep const & ts);

			virtual void			load(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
			virtual void			save(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) const;
			BOOST_SERIALIZATION_SPLIT_MEMBER();

			virtual wbase			createActorBase(neb::core::pose);
			virtual wbase			createActorRigidStaticUninitialized();

			virtual wbase			createActorRigidDynamic(neb::core::core::actor::rigiddynamic::desc const * const &);
			
			virtual wbase			createActorRigidDynamicUninitialized();
	};
}}}}}

#endif

