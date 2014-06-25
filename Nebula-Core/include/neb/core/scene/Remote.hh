#ifndef __GLUTPP_SCENE_REMOTE_H__
#define __GLUTPP_SCENE_REMOTE_H__

#include <vector>

//#include <neb/Flag.hh>
//#include <neb/util/Map.hh>
//#include <neb/util/Shared.hh>

#include <neb/util/decl.hpp>

#include <neb/core/scene/Base.hh>

//#include <neb/config.hh> // neb/config.hpp.in
//#include <neb/gfx/glsl/program.hh>


//#include <neb/core/actor/Base.hh>
#include <neb/core/actor/Util/Parent.hh>

//#include <neb/gfx/Camera/View/Base.hh>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace neb { namespace core {
	namespace scene {
		class remote:
			virtual public neb::core::scene::base
		{
			void				step(gal::std::timestep const & ts);

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
	}
}}

#endif





