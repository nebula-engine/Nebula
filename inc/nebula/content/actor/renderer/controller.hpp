#ifndef __NEBULA_CONTENT_ACTOR_RENDERER_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_RENDERER_CONTROLLER_HPP__



#include <nebula/content/actor/renderer/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace renderer
			{
				/// controller
				class controller:
					public n34300::base
				{
public:
friend class n34100::controller::base;
					protected:
						/** \brief copy ctor
						*/
						controller(const controller&);
						/** \brief assignment
						*/
						controller&								operator=( controller const & ) = default;
						/** \brief ctor
						*/
						controller( std::shared_ptr<n34100::base> );
					public:
						/** \brief dtor
						*/
						~controller();
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
						virtual	void								step( float );
						/** \brief render
						*/
						virtual	void								render( std::shared_ptr<n23000::base> );
						/** \brief create shapes
						*/
						virtual	void								create_shapes();
				};
			}
		}
	}
}

#endif








