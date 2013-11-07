#ifndef __NEBULA_CONTENT_CAMERA_HPP__
#define __NEBULA_CONTENT_CAMERA_HPP__

#include <ker/module/module.hpp>

namespace nebula
{
	namespace content
	{
		/// camera
		class camera:
			public ker::module::module
		{
			public:
				/// ctor
				camera();
				/// render
				void									render( std::shared_ptr<n23000::base> );

				/// controller
				std::shared_ptr<n34100::controller::base>		controller_;
		};
	}
}



#endif

