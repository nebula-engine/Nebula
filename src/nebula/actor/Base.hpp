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
				Base(glutpp::actor::parent_s);
				virtual ~Base();

				virtual void			init(glutpp::actor::desc_s);
				virtual void			release();
				
			private:
				neb::Actor::Base_s		create_actor(glutpp::actor::desc_s);
			public:
				neb::Actor::Base_s		create_actor_local(glutpp::actor::desc_s);
				
				neb::Actor::Base_s		create_actor_remote(glutpp::actor::addr_s, glutpp::actor::desc_s);
				
				
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
				neb::Actor::Base_s		get_actor(glutpp::actor::addr_s addr);

				virtual glutpp::actor::desc_s	get_projectile();
				
				
				
				
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








