#ifndef __NEB_CAMERA_H__
#define __NEB_CAMERA_H__

#include <memory>
#include <map>

#include <glutpp/window/window.h>
#include <glutpp/camera_control.h>

#include <neb/config.h>

namespace neb {
	namespace camera {
		class ridealong: public glutpp::camera_control
		{
			public:
				camera_ridealong(neb::actor::Base_s);
				virtual math::mat44		supply();


				neb::actor::Base_w		actor_;
		};
	}
}

#endif


