#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__

#include <nebula/content/actor/physics/rigid_body.hpp>

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
				class rigid_dynamic:
					public nebula::content::actor::physics::rigid_body
				{
					protected:
						/** \brief copy ctor
						*/
						rigid_dynamic(const rigid_dynamic&);
						/** \brief assignment
						*/
						rigid_dynamic&								operator=(const rigid_dynamic&);
						/** \brief ctor
						*/
						rigid_dynamic( jess::shared_ptr<n34100::base> );
					public:
						/** \brief dtor
						*/
						~rigid_dynamic();
						/** \brief init
						*/
						virtual	void								init();
						/** \brief shutdown
						*/
						virtual	void								shutdown();
						/** \brief update
						*/
						virtual	void								update();
						/** \brief step
						*/
						virtual	void								step(float);
						/** \brief render
						*/
						virtual	void								render( jess::shared_ptr<n23000::base> );
						/** \brief create shapes
						*/
						virtual	void								create_shape();
				};
			}
		}
	}
}

#endif








