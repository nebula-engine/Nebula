#ifndef __GLUTPP_SCENE_LOCAL_H__
#define __GLUTPP_SCENE_LOCAL_H__

#include <vector>

#include <Nebula/Flag.hh>
#include <Nebula/Util/Map.hh>
#include <Nebula/Util/Typed.hh>



#include <Nebula/Types.hh>

#include <Nebula/Scene/Util/Flag.hh>
#include <Nebula/Scene/Util/Types.hh>

#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/Graphics/glsl/program.hh>


//#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Parent.hh>

#include <Nebula/Graphics/Camera/View/Base.hh>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace Neb {
	namespace Scene {
		class Local: public Neb::Scene::Base {
			virtual void			step(double const & time, double const & dt);
			virtual void			fire(Neb::Actor::Base_s);
		};
	}
}

#endif



