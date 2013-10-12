#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_ACTOR_HPP__

#include <nebula/content/actor/admin/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// rigid dynamic
				class actor:
					public n34100::base
				{
					protected:
						/// Copy Ctor
						actor(const actor&);
						/// assignment
						actor&									operator=(const actor&);
					public:
						// Ctor
						actor( jess::shared_ptr<n32100::base> );
						/// Dtor
						virtual ~actor();
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


