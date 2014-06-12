#ifndef __GLUTPP_SCENE_LOCAL_H__
#define __GLUTPP_SCENE_LOCAL_H__

#include <vector>

//#include <Nebula/Flag.hh>

//#include <Nebula/Util/Map.hh>
//#include <Nebula/Util/Typed.hh>



#include <Nebula/Types.hh>

#include <Nebula/Scene/Base.hh>

#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/Graphics/glsl/program.hh>


//#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Parent.hh>

#include <Nebula/Graphics/Camera/View/Base.hh>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace neb {
	namespace Scene {
		class Local: public Neb::Scene::Base {
			public:
				Local(sp::shared_ptr<Neb::Scene::Util::Parent> parent);
				virtual void			step(Neb::Core::TimeStep const & ts);
				virtual void			send_actor_update();
		};
	}
}

#endif



