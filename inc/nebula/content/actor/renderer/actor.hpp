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
					virtual public n34300::base
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					actor( std::shared_ptr<n34100::base> );
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
					virtual	void								init();
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step( float );
					/// render
					virtual	void								render( jess::shared_ptr<n23000::base> );
				
				
				
					
				};
			}
		}
	}
}

#endif








