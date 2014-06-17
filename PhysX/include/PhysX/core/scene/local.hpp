#ifndef PHYSX_SCENE_LOCAL_H__
#define PHYSX_SCENE_LOCAL_H__

#include <vector>



#include <Nebula/Types.hh>

#include <Nebula/Scene/Local.hh>
#include <Nebula/Scene/Util/Types.hh>

#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/Graphics/glsl/program.hh>


//#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Parent.hh>

#include <Nebula/Graphics/Camera/View/Base.hh>

//#include <glutpp/shader.h>

#include <PhysX/core/actor/base.hpp>
#include <PhysX/core/scene/base.hpp>

namespace phx { namespace core { namespace scene {


	class local:
		virtual public neb::scene::local,
		virtual public phx::core::scene::base
	{
		public:
			local(sp::shared_ptr<neb::scene::util::parent> parent);
			virtual void			init();
			virtual void			release();
			virtual void			step(::neb::core::TimeStep const & ts);

			virtual void			serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {}
			virtual void			serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {}


			virtual void			fire(sp::shared_ptr<phx::core::actor::base> actor);
	};



}}}

#endif



