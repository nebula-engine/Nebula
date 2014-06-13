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
		class Base: virtual public neb::Actor::Util::Parent {
			public:
				Base(sp::shared_ptr<neb::Scene::Util::Parent>);
				virtual ~Base();
				void				init();
				void				release();
				glm::mat4			get_pose();
				/** @name Main Loop @{ */
				/** @brief render */
				void				render(
						double time,
						std::shared_ptr<neb::gfx::Camera::View::Base>,
						std::shared_ptr<neb::gfx::Camera::Projection::Base>,
						sp::shared_ptr<neb::gfx::Window::Base>);
				void				draw(sp::shared_ptr<neb::gfx::Window::Base> window);
				void				resize(int w, int h);
				void				draw();
				void				step(neb::core::TimeStep const & ts);
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
				void						create_physics();
				/** @name Accessors @{ */
				mat4						getPose();
				mat4						getPoseGlobal();
				/** @} */
				/** @name Children @{ */
				/** @} */
				//void						create_actors(neb::Scene::desc_w);
			private:	
				//_wneb::Actor::Base>		create_actor(boost::shared_ptr<neb::Actor::desc>);
			public:
				//neb::weak_ptr<neb::Actor::Base>			create_actor_local(neb::Actor::desc_w);
				//neb::weak_ptr<neb::Actor::Base>			create_actor_remote(neb::Actor::addr_w, neb::Actor::desc_w);
				void							add_deferred(sp::shared_ptr<neb::Actor::Base>);

				//void							send_actor_update();

				//int						recv(neb::packet::packet);
				//void						read(neb::active_transform::set*);
				//sp::shared_ptr<neb::Scene::desc>				desc_generate();

				virtual void						dumby() {}
			public:
				/** @brief parent
				 *
				 * @note WEAK
				 */
				sp::shared_ptr<neb::Scene::Util::Parent>		parent_;
				
			public:
				neb::Scene::Util::Flag					flag_;

				std::map<std::string, neb::Actor::Base_s>		actors_deferred_;
		};
	}
}

#endif





