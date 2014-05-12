#ifndef __NEBULA_ACTOR_BASE_HPP
#define __NEBULA_ACTOR_BASE_HPP

#include <memory>

#include <boost/signals2.hpp>

#include <PxPhysicsAPI.h>

#include <Nebula/config.hpp> // Nebula/config.hpp.in
#include <Nebula/Actor/Types.hpp>
//#include <Nebula/Actor/Util/desc.hpp>
#include <Nebula/Actor/Util/Address.hpp>
#include <Nebula/Actor/Util/raw.hpp>

#include <Nebula/Actor/Util/parent.hpp>
#include <Nebula/Message/Actor/Update.hpp>
#include <Nebula/Graphics/texture.hpp>
#include <Nebula/Graphics/material.hpp>
#include <Nebula/shape/shape.hpp>
#include <Nebula/shape/parent.hpp>


#include <Nebula/Actor/Util/raw.hpp>
#include <Nebula/Actor/Util/parent.hpp>

#include <Nebula/Message/Actor/Update.hpp>

#include <Nebula/Graphics/texture.hpp>
#include <Nebula/Graphics/material.hpp>

#include <Nebula/shape/shape.hpp>
#include <Nebula/shape/parent.hpp>


namespace Neb {
	namespace Actor {
		/** @brief %Base */
		class Base:
				virtual public Neb::Actor::parent,
				virtual public Neb::Shape::parent,
				virtual public Neb::Util::Release,
				public gal::flag {
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

				//virtual void				init(Neb::weak_ptr<Neb::Actor::desc>);
				virtual void				releaseDerived();
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


				//void							create_shapes(Neb::Actor::desc_w);
				//void							create_children(Neb::Actor::desc_w);

				virtual void						create_physics() = 0;
				virtual void						init_physics() = 0;

				/** @name Accessors @{ */
				//Neb::app_s						get_app();
				Neb::Scene::Base_s					get_scene();
				Neb::weak_ptr<Neb::Actor::Base>				get_actor(int);
				/** @brief get child actor
				 *
				 * casts gru actor to nebula actor
				 * @param addr address of actor
				 */
				Neb::weak_ptr<Neb::Actor::Base>				get_actor(Neb::weak_ptr<Neb::Actor::addr> addr);
				//virtual Neb::Actor::Base_s				get_projectile();
				Neb::Actor::Util::Address				getAddress() const;


				virtual physx::PxTransform				getPose();
				virtual physx::PxTransform				getPoseGlobal();
				/** @} */


				virtual void						hit();
				virtual void						damage(float);


				// signal
				void				connect(Neb::window::window_w);


				int				key_fun(int,int,int,int);
				virtual int			fire();
			public:
				/** @todo what is this??? */
				Neb::Actor::mode_update::e		mode_update_;

				
				struct {
					boost::signals2::connection		key_fun_;
				} conn_;

			public:
				/** @brief %Serialize
				 * @param ar archive
				 * @param version version
				 */
				template<class Archive>
				void			serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i", i_);
					
					serializeData(ar, version);
					
					ar & boost::serialization::make_nvp("actors", actors_);				
					ar & boost::serialization::make_nvp("shapes", shapes_);
				}
				virtual void		serializeData(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("raw", raw_);
				}
				
				/** @brief %Serialize specialization */
				void			serialize(
						Neb::Message::Actor::OUpdate & ar,
						unsigned int const & version) {
					auto address = getAddress();
					ar << boost::serialization::make_nvp("address", address);
					ar << boost::serialization::make_nvp("raw", raw_);
				}
				/** @brief %Serialize specialization */
				void			serialize(
						Neb::Message::Actor::IUpdate & ar,
						unsigned int const & version) {
					ar >> boost::serialization::make_nvp("raw", raw_);
				}



				/** @name Stepping @{ */
				virtual void					step(double time);
				virtual void					step_local(double);
				virtual void					step_remote(double);

				//virtual void					step_local(double);
				//virtual void					step_remote(double);

				/** @} */
				/** @name Render @{ */
				void						draw(Neb::window::window_s, physx::PxTransform);
				/** @} */

				/** @name Accessors @{ */
				Neb::Actor::parent_s				getParent();
				void						setPose(physx::PxTransform pose);
				/** @} */

				void						notify_foundation_change_pose();
				void						load_lights(int&, physx::PxMat44);


			public:
				/** @brief ID */
				int						i_;
				
				/** @brief Data.
				 * @todo dissolve raw so. move certain members of raw up the hierarchy
				 * 
				 * Consider eliminating the raw class entirely (or at least make it
				 * a simple data container). If it is desired to serialize only the
				 * raw data (like in actor update), or a subset of it, implement this by
				 * overloading the serialize functions...
				 */
				Neb::Actor::Util::Raw				raw_;
				

				/** @brief Parent */
				Neb::Actor::Parent_w				parent_;
		};
	}
}

#endif








