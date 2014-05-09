#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__

#include <memory>

#include <boost/signals2.hpp>

#include <PxPhysicsAPI.h>

#include <Nebula/config.hpp> // Nebula/config.hpp.in
#include <Nebula/Actor/Types.hpp>
#include <Nebula/Actor/Util/desc.hpp>
#include <Nebula/Actor/Util/addr.hpp>
#include <Nebula/Actor/Util/raw.hpp>
#include <Nebula/Actor/Util/desc.hpp>
#include <Nebula/Actor/Util/parent.hpp>
#include <Nebula/Graphics/texture.hpp>
#include <Nebula/Graphics/material.hpp>
#include <Nebula/shape/shape.hpp>
#include <Nebula/Actor/Util/raw.hpp>
#include <Nebula/Util/weak_function.hpp>

namespace Neb {
	namespace Actor {
		/** @brief %Base */
		class Base: virtual public Neb::Actor::parent, virtual public Neb::Shape::parent, public gal::flag {
			public:
				struct flag {
					enum e {
						SHOULD_RELEASE	= 1 << 0,
						SHOULD_UPDATE	= 1 << 1,
						DESTRUCTIBLE    = 1 << 2,
					};
				};

				Base(Neb::Actor::parent_w);
				virtual ~Base();

				virtual void				init(Neb::weak_ptr<Neb::Actor::desc>);
				virtual void				release();
				virtual void				cleanup();


				void					i(int ni);
				int					i() const;

				unsigned int				f() const;
				void					f(unsigned int flag);

			private:
				Neb::Actor::Base_w			create_actor(Neb::weak_ptr<Neb::Actor::desc>);
			public:
				Neb::Actor::Base_w			create_actor_local(Neb::weak_ptr<Neb::Actor::desc>);

				Neb::Actor::Base_w			create_actor_remote(Neb::weak_ptr<Neb::Actor::addr>, Neb::weak_ptr<Neb::Actor::desc>);


				void							create_shapes(Neb::Actor::desc_w);
				void							create_children(Neb::Actor::desc_w);

				virtual void						create_physics() = 0;
				virtual void						init_physics() = 0;

				Neb::weak_ptr<Neb::app>					get_app();
				Neb::weak_ptr<Neb::Scene::scene>			get_scene();

				Neb::weak_ptr<Neb::Actor::Base>				get_actor(int);
				/** @brief get child actor
				 *
				 * casts gru actor to nebula actor
				 * @param addr address of actor
				 */
				Neb::weak_ptr<Neb::Actor::Base>			get_actor(Neb::weak_ptr<Neb::Actor::addr> addr);

				virtual Neb::weak_ptr<Neb::Actor::desc>		get_projectile();




				virtual void						hit();
				virtual void						damage(float);


				// signal
				void				connect(Neb::window::window_w);
				
				
				int				key_fun(int,int,int,int);
				virtual int			fire();
				
				/** @name Convertion @{ */
				Neb::weak_ptr<Neb::Actor::Base>					isBase();
				Neb::weak_ptr<Neb::Actor::RigidActor>				isRigidActor();
				Neb::weak_ptr<Neb::Actor::RigidBody::RigidBody>			isRigidBody();
				boost::shared_ptr<Neb::Actor::Base>				sharedBase();
				/** @} */
			public:
				Neb::Actor::mode_update::e	mode_update_;

				Neb::window::window_w	window_;
				
				struct {
					std::shared_ptr< Neb::weak_function<int,int,int,int,int> >	key_fun_;
				} conn_;

			public:


				

				
				/** @name Stepping @{ */
				virtual void					step(double time);
				virtual void					step_local(double);
				virtual void					step_remote(double);

				//virtual void					step_local(double);
				//virtual void					step_remote(double);

				/** @} */
				/** @name Render @{ */
				void						draw(Neb::window::window_s, physx::PxMat44);
				/** @} */
				
				/** @name Accessors @{ */
				Neb::weak_ptr<Neb::Actor::parent>		getParent();
				void						setPose(physx::PxTransform pose);
				/** @} */
				
				void						notify_foundation_change_pose();
				void						load_lights(int&, physx::PxMat44);
				



			public:
				int						i_;
				Neb::weak_ptr<Neb::Actor::parent>		parent_;
				Neb::Map<Neb::Shape::shape>			shapes_;
				Neb::Map<Neb::Actor::Base>			actors_;
				/** @brief Data */
				Neb::unique_ptr<Neb::Actor::raw>		raw_;
		};
	}
}

#endif








