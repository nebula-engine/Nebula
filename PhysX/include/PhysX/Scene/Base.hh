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
				void				init();
				void				release();
				glm::mat4			get_pose();
				/** @name Main Loop @{ */
				/** @brief render */
				void				render(
						double time,
						std::shared_ptr<Neb::Graphics::Camera::View::Base>,
						std::shared_ptr<Neb::Graphics::Camera::Projection::Base>,
						Neb::Graphics::Window::Base_s);
				void				draw(Neb::Graphics::Window::Base_s window);
				void				resize(int w, int h);
				void				draw();
				void				step(Neb::Core::TimeStep const & ts);
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
				//void						create_actors(Neb::Scene::desc_w);
			private:	
				//_wNeb::Actor::Base>		create_actor(boost::shared_ptr<Neb::Actor::desc>);
			public:
				//Neb::weak_ptr<Neb::Actor::Base>			create_actor_local(Neb::Actor::desc_w);
				//Neb::weak_ptr<Neb::Actor::Base>			create_actor_remote(Neb::Actor::addr_w, Neb::Actor::desc_w);
				void							add_deferred(Neb::Actor::Base_s);

				//void							send_actor_update();

				//int						recv(Neb::packet::packet);
				//void						read(Neb::active_transform::set*);
				//Neb::Scene::desc_s				desc_generate();

				virtual void						dumby() {}
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





