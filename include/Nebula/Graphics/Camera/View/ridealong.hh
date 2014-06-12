#ifndef __NEB_CAMERA_RIDEALONG_H__
#define __NEB_CAMERA_RIDEALONG_H__

#include <memory>
#include <map>

#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Camera/View/Base.hh>
#include <Nebula/config.hh>

namespace neb {
	namespace Graphics {
		namespace Camera {
			namespace View {
				class Ridealong: public Neb::Graphics::Camera::View::Base {
					public:
						Ridealong(Neb::Graphics::Context::Base_s);

						virtual mat4				view();
						virtual void				step(Neb::Core::TimeStep const & ts);


						sp::shared_ptr<Neb::Actor::Base>	actor_;
				};
			}
		}
	}
}
#endif


