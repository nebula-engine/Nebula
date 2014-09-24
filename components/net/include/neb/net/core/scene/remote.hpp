#ifndef PHYSX_CORE_SCENE_REMOTE_H__
#define PHYSX_CORE_SCENE_REMOTE_H__

#include <vector>


#include <neb/util/decl.hpp>

#include <neb/core/scene/Remote.hh>

#include <neb/config.hh> // Nebula/config.hpp.in
#include <neb/gfx/glsl/program.hpp>

//#include <neb/core/actor/base.hpp>
#include <neb/core/actor/Util/Parent.hh>

#include <neb/gfx/camera/view/Base.hh>

#include <PhysX/core/scene/base.hpp>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace phx { namespace core { namespace scene {

	class remote:
		virtual public neb::core::scene::remote,
		virtual public ::phx::core::scene::base
	{
		void				step(gal::etc::timestep const & ts);
		
		virtual void			fire(std::shared_ptr<neb::core::actor::base> actor);

		/** @name convenience functions
		 * @{
		 */
		/** @brief create rigidstatic
		 *
		 * @note typeof returned actor will be determined by final implementation of this
		 *
		 * @warning return actor is not initialized
		 */
		std::weak_ptr<neb::core::actor::rigidstatic::base>	createActorRigidStaticUninitialized();
		/** @} */	

	};




}}}

#endif





