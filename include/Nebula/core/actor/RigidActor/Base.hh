#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <Nebula/core/shape/Util/Types.hh>
#include <Nebula/core/actor/Actor/Base.hh>

namespace neb { namespace core { namespace actor {
namespace rigidactor {


			class base:
				virtual public neb::core::actor::actor::base
			{
				public:
					//base();
					base(sp::shared_ptr<neb::core::actor::util::parent> parent);

					virtual void					init();
					virtual void					release() = 0;
					virtual void					step(gal::std::timestep const & ts);

					/** @name convenience functions
					 * @{
					 */
					virtual sp::weak_ptr<neb::core::shape::box>		createShapeBoxUninitialized();
					/** @brief create shape cube
					 */
					sp::weak_ptr<neb::core::shape::box>			createShapeCube(real size);
					/** @} */
			};
		}


}}}

#endif








