#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <boost/shared_ptr.hpp>

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
					virtual void					init(const boost::shared_ptr<nebula::content::scene::admin::base>&);
					virtual void					shutdown();
					virtual void					update();
					virtual void					step(FLOAT);
					virtual void					render(const boost::shared_ptr<nebula::platform::renderer::base>&);


					virtual void					add_actor( const boost::shared_ptr<ncaa::actor>& );
				};
			}
		}
	}
}

#endif
