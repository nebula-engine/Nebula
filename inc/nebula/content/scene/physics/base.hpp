#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/scene/types.hpp>
#include <nebula/utilities/types/content/actor/types.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace scene
		{
			namespace physics
			{
				class base
				{
				public:
					base();
					virtual ~base();
					base(const base&);
					base&						operator=(const base&);
					virtual void					init(const jess::shared_ptr<nebula::content::scene::admin::base>&);
					virtual void					shutdown();
					virtual void					update();
					virtual void					step(FLOAT);
					virtual void					render(const jess::shared_ptr<nebula::platform::renderer::base>&);
					
					
					virtual void					register_actor( jess::shared_ptr<ncaa::actor> );
				};
			}
		}
	}
}

#endif
