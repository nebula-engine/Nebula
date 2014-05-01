#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__

#include <memory>


//#include <tinyxml/tinyxml.h>

#include <PxPhysicsAPI.h>

//#include <math/transform.hpp>

#include <gru/actor/actor.hpp>
#include <gru/actor/desc.hpp>

#include <nebula/actor/raw.hpp>
#include <nebula/config.hpp>

namespace neb {
	namespace Actor {
		/** @brief %Base */
		class Base:
			public glutpp::actor::actor
		{
			public:
				Base(boost::shared_ptr<glutpp::actor::parent>);
				virtual ~Base();

				virtual void			init(boost::shared_ptr<glutpp::actor::desc>);
				virtual void			release();
				
			private:
				boost::shared_ptr<neb::Actor::Base>		create_actor(boost::shared_ptr<glutpp::actor::desc>);
			public:
				boost::shared_ptr<neb::Actor::Base>		create_actor_local(boost::shared_ptr<glutpp::actor::desc>);
				
				boost::shared_ptr<neb::Actor::Base>		create_actor_remote(boost::shared_ptr<glutpp::actor::addr>, boost::shared_ptr<glutpp::actor::desc>);
				
				
				void				create_shapes(glutpp::actor::desc_s);
				void				create_children(glutpp::actor::desc_s);
				
				virtual void			create_physics() = 0;
				virtual void			init_physics() = 0;

				neb::app_s			get_app();
				neb::scene::scene_s		get_scene();
				
				neb::Actor::Base_s		get_actor(int);
				/** @brief get child actor
				 *
				 * casts gru actor to nebula actor
				 * @param addr address of actor
				 */
				boost::shared_ptr<neb::Actor::Base>			get_actor(boost::shared_ptr<glutpp::actor::addr> addr);
				
				virtual boost::shared_ptr<glutpp::actor::desc>		get_projectile();
				
				
				
				
				virtual void			hit();
				virtual void			damage(float);
				
				
				virtual void			step_local(double);
				virtual void			step_remote(double);
				
				neb::Actor::raw_s		get_raw_base();
				
				// signal
				void				connect(glutpp::window::window_s);
				
				
				int				key_fun(int,int,int,int);
				virtual int			fire();
				
				
				/** @name Convertion
				 * @{
				 */
				Base_s				isBase();
				RigidActor_s			isRigidActor();
				RigidBody::RigidBody_s		isRigidBody();
				/** @} */
			public:
				glutpp::actor::mode_update::e	mode_update_;
				
				glutpp::window::window_w	window_;
				
				struct
				{
					boost::signals2::connection		key_fun_;
				} conn_;

		};
	}
}


#endif








