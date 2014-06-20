#ifndef PHYSX_SCENE_LOCAL_H__
#define PHYSX_SCENE_LOCAL_H__

#include <vector>



#include <Nebula/util/decl.hpp>

#include <Nebula/core/scene/Local.hh>
#include <Nebula/core/scene/Util/Types.hh>

#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/gfx/glsl/program.hh>


//#include <Nebula/core/actor/Base.hh>
#include <Nebula/core/actor/Util/Parent.hh>

#include <Nebula/gfx/Camera/View/Base.hh>

//#include <glutpp/shader.h>

#include <PhysX/core/actor/base.hpp>
#include <PhysX/core/scene/base.hpp>

namespace phx { namespace core { namespace scene {


	class local:
		virtual public neb::core::scene::local,
		virtual public phx::core::scene::base
	{
		public:
			local(sp::shared_ptr<neb::core::scene::util::parent> parent);
			virtual void			init();
			virtual void			release();
			virtual void			step(::neb::core::TimeStep const & ts);

			virtual void			serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {}
			virtual void			serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {}

			/** @name convenience functions
			 * @{
			 */
			/** @brief create rigidstatic
			 *
			 * @note typeof returned actor will be determined by final implementation of this
			 *
			 * @warning return actor is not initialized
			 */
			sp::weak_ptr<neb::core::actor::rigidstatic::base>	createActorRigidStaticUninitialized();
			/** @} */	
	
	};



}}}

#endif



