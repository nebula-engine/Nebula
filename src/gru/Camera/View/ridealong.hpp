#ifndef __NEB_CAMERA_RIDEALONG_H__
#define __NEB_CAMERA_RIDEALONG_H__

#include <memory>
#include <map>

#include <gru/window/window.hpp>
#include <gru/Camera/View/Base.hpp>
#include <gru/config.hpp>

namespace glutpp {
	namespace Camera {
		namespace View {
			class ridealong: public glutpp::Camera::View::Base {
				public:
					ridealong(glutpp::actor::actor_s);
					virtual math::mat44<double>		view();
					virtual void				step(double time);


					glutpp::actor::actor_w		actor_;
			};
		}
	}
}

#endif


