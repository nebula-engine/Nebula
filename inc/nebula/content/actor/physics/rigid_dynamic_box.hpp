#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_BOX_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_BOX_HPP__

#include <nebula/content/actor/physics/rigid_dynamic.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/** \brief rigid dynamic
				 */
				class rigid_dynamic_box:
					public nebula::content::actor::physics::rigid_dynamic
				{
					public:
						friend class n36000::base;
					protected:
						/** \brief copy ctor
						 */
						rigid_dynamic_box( rigid_dynamic_box const & );
						/** \brief assignment
						 */
						rigid_dynamic_box&				operator=( rigid_dynamic_box const & ) = default;
						/** \brief ctor
						 */
						rigid_dynamic_box( std::shared_ptr<n34100::base> );
					public:
						/** \brief dtor
						 */
						~rigid_dynamic_box();
						/** \brief init
						 */
						virtual	void					init();
						/** \brief shutdown
						 */
						virtual	void					shutdown();
						/** \brief update
						 */
						virtual	void					update();
						/** \brief step
						 */
						virtual	void					step( float );
						/** \brief render
						 */
						virtual	void					render( std::shared_ptr<n23000::base> );
						/** \brief create shapes
						 */
						virtual	void					create_shapes();
				};
			}
		}
	}
}

#endif








