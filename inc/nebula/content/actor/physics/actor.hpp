#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>

#include <nebula/content/actor/physics/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/** \brief actor
				 */
				class actor:
					public n34200::base
				{
					protected:
						/** \brief copy ctor
						 */
						actor( actor const & ) = default;
						/** \brief assignment
						 */
						actor&							operator=( actor const & ) = default;
						/** \brief ctor
						 */
						actor( std::shared_ptr<n34100::base> );
					public:
						/** \brief dtor
						 */
						~actor();
						/** \brief init
						 */
						virtual	void						init();
						/** \brief shutdown
						 */
						virtual	void						shutdown();
						/** \brief update
						 */
						virtual	void						update();
						virtual void						refresh() = 0;
						/** \brief step
						 */
						virtual	void						step();
					public:
						/** \brief px actor
						 */
						physx::PxActor*						px_actor_;
				};
			}
		}
	}
}

#endif








