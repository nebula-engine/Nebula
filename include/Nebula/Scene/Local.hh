#ifndef __GLUTPP_SCENE_LOCAL_H__
#define __GLUTPP_SCENE_LOCAL_H__

#include <vector>

//#include <Nebula/Flag.hh>

//#include <Nebula/Util/Map.hh>
//#include <Nebula/Util/Typed.hh>



#include <Nebula/Types.hh>

#include <Nebula/Scene/Base.hh>

//#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/Graphics/glsl/program.hh>


//#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Parent.hh>

#include <Nebula/Graphics/Camera/View/Base.hh>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace neb { namespace core {
	namespace scene {
		class local: virtual public neb::core::scene::base {
			public:
				local(sp::shared_ptr<neb::core::scene::util::parent> parent);
				virtual void			step(neb::core::TimeStep const & ts);
				virtual void			send_actor_update();
		};
	}
}}

#endif



