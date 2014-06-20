#ifndef PHYSX_CORE_SCENE_REMOTE_H__
#define PHYSX_CORE_SCENE_REMOTE_H__

#include <vector>


#include <Nebula/util/decl.hpp>

#include <Nebula/core/scene/Remote.hh>

#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/gfx/glsl/program.hh>


//#include <Nebula/core/actor/Base.hh>
#include <Nebula/core/actor/Util/Parent.hh>

#include <Nebula/gfx/Camera/View/Base.hh>

#include <PhysX/core/scene/base.hpp>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace phx { namespace core { namespace scene {

	class remote:
		virtual public neb::core::scene::remote,
		virtual public ::phx::core::scene::base
	{
		void				step(neb::core::TimeStep const & ts);
		
		virtual void			fire(sp::shared_ptr<neb::core::actor::base> actor);

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





