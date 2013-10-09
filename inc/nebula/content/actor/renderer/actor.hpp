#ifndef __NEBULA_CONTENT_ACTOR_RENDERER_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_RENDERER_ACTOR_HPP__



#include <nebula/content/actor/renderer/base.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace renderer
			{
				/// actor
				class actor:
					virtual public ncar::base
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					actor();
					/// Copy Ctor
					actor(const actor&);
					/// Dtor
					~actor();
					///@}

					///@name operator
					///@{
					/// assignment
					actor&									operator=(const actor&);
					///@}

				

					/// init
					virtual	void								init( jess::shared_ptr<ncaa::base> );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step( FLOAT );
					/// render
					virtual	void								render( jess::shared_ptr<npr::base> );
				
				
				
					
				};
			}
		}
	}
}

#endif








