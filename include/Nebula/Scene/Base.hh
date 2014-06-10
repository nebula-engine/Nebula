#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <Galaxy-Standard/flag.hpp>
#include <Galaxy-Standard/map.hpp>


#include <Nebula/Types.hh>
#include <Nebula/Util/typedef.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

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
		/** 
		 * @ingroup group_core
		 * @brief Base
		 */
		class Base: virtual public Neb::Actor::Util::Parent {
			public:
				Base(Neb::Scene::Util::Parent_s);
				virtual ~Base();
				virtual void				init();
				virtual void				release();
				/** @name Main Loop @{ */
				/** @brief render */

				void				draw(sp::shared_ptr<Neb::Graphics::Context::Base> context);
				void				resize(int w, int h);
				virtual void			step(Neb::Core::TimeStep const & ts);
				/** @} */

				virtual  void			serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("flag",flag_);
				}
				virtual void			serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("flag",flag_);
				}
			public:
				/** @name Accessors @{ */
				mat4						getPose();
				mat4						getPoseGlobal();
				/** @} */
			public:
				void							add_deferred(Neb::Actor::Base_s);
			public:
				/** @brief parent
				 *
				 * @note WEAK
				 */
				sp::shared_ptr<Neb::Scene::Util::Parent>		parent_;
				
			public:
				Neb::Scene::Util::Flag					flag_;

				std::map<std::string, Neb::Actor::Base_s>		actors_deferred_;
		};
	}
}

#endif





