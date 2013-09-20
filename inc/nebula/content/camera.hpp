#ifndef __NEBULA_CONTENT_CAMERA_HPP__
#define __NEBULA_CONTENT_CAMERA_HPP__

#include <boost/shared_ptr.hpp>

#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/actor/types.hpp>

namespace nebula
{
	namespace content
	{
		/// camera
		class camera
		{
		public:
			/// ctor
			camera();
			/// render
			void									render(const boost::shared_ptr<nebula::platform::renderer::base>&);

			/// controller
			boost::shared_ptr<nebula::content::actor::admin::controller>		controller_;
		};
	}
}



#endif

