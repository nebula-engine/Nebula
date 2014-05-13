#ifndef __NEBULA_ACTOR_BASE_HPP
#define __NEBULA_ACTOR_BASE_HPP

#include <memory>

#include <boost/signals2.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <PxPhysicsAPI.h>

#include <Nebula/config.hh> // Nebula/config.hpp.in
//#include <Nebula/Actor/Util/desc.hh>

#include <Nebula/Util/Release.hh>

#include <Nebula/Filter.hh>

#include <Nebula/Message/Actor/Update.hh>
#include <Nebula/Graphics/texture.hh>
#include <Nebula/Graphics/material.hh>

#include <Nebula/Shape/Base.hh>
#include <Nebula/Shape/Util/Parent.hh>


#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/Util/Address.hh>
#include <Nebula/Actor/Util/Parent.hh>

#include <Nebula/Message/Actor/Update.hh>

#include <Nebula/Graphics/texture.hh>
#include <Nebula/Graphics/material.hh>

#include <Nebula/Shape/Base.hh>
#include <Nebula/Shape/Util/Parent.hh>


namespace Neb {
	namespace Actor {
		/** @brief %Base */
		class Base:
				virtual public Neb::Actor::Util::Parent,
				virtual public Neb::Shape::Util::Parent,
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

				Base(Neb::Actor::Util::Parent_s);
				virtual ~Base();

				//virtual void				init(Neb::weak_ptr<Neb::Actor::desc>);
				virtual void				releaseDerived();
				virtual void				cleanup();

				void					i(int ni);
				int					i() const;

				unsigned int				f() const;
				void					f(unsigned int flag);

			private:
				/** %brief Insert Actor
				 * @param actor the actor to [copy and] insert
				 * @return the newly created and stored actor
				 * 
				 * @note this function replaces the old @c create_actor function
				 * 
				 * @warning the value of @c actor.i_ must be accurate
				 * 
				 * the new pattern is, an actor object is deserialized and passed as @c actor
				 * since the type of the actor MAY need to change (ex. between local and remote),
				 * a copy of @c actor is create with the correct type
				 */
				virtual Neb::Actor::Base_s		insertActor(Neb::Actor::Base_s actor);
			public:
				//Neb::Actor::Base_w			create_actor_local(Neb::weak_ptr<Neb::Actor::desc>);

				//Neb::Actor::Base_w			create_actor_remote(Neb::weak_ptr<Neb::Actor::addr>, Neb::weak_ptr<Neb::Actor::desc>);



				//void							create_shapes(Neb::Actor::desc_w);
				//void							create_children(Neb::Actor::desc_w);

				virtual void						create_physics() = 0;
				virtual void						init_physics() = 0;

				/** @name Accessors @{ */
				//virtual Neb::Actor::Base_s				get_projectile();
				Neb::Actor::Util::Address				getAddress() const;
				virtual physx::PxTransform				getPose();
				virtual physx::PxTransform				getPoseGlobal();
				/** @} */

				/** @todo move to derived class */
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
				virtual void		saveData(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("mode_create",mode_create_);
					ar & boost::serialization::make_nvp("flag",flag_);
					ar & boost::serialization::make_nvp("name",name_);
					ar & boost::serialization::make_nvp("pose",pose_);
					ar & boost::serialization::make_nvp("normal",n_);
					ar & boost::serialization::make_nvp("distance",d_);
					ar & boost::serialization::make_nvp("velocity",velocity_);
					ar & boost::serialization::make_nvp("density",density_);
					ar & boost::serialization::make_nvp("filter_data_simulation",simulation_);
					ar & boost::serialization::make_nvp("filter_data_scene_query",scene_query_);
				}
				virtual void		loadData(
						boost::archive::polymorphic_iarchive & ar,
						unsigned int const & version) {
					ar & boost::serialization::make_nvp("mode_create",mode_create_);
					ar & boost::serialization::make_nvp("flag",flag_);
					ar & boost::serialization::make_nvp("name",name_);
					ar & boost::serialization::make_nvp("pose",pose_);
					ar & boost::serialization::make_nvp("normal",n_);
					ar & boost::serialization::make_nvp("distance",d_);
					ar & boost::serialization::make_nvp("velocity",velocity_);
					ar & boost::serialization::make_nvp("density",density_);
					ar & boost::serialization::make_nvp("filter_data_simulation",simulation_);
					ar & boost::serialization::make_nvp("filter_data_scene_query",scene_query_);
				}

				/** @brief %Serialize specialization */
				void			saveUdate(
						boost::archive::polymorphic_oarchive & ar,
						unsigned int const & version) {
					auto address = getAddress();
					ar << boost::serialization::make_nvp("address", address);
					saveData(ar, version);
				}
				/** @brief %Serialize specialization */
				void			loadUpdate(
						boost::archive::polymorphic_iarchive & ar,
						unsigned int const & version) {
					loadData(ar, version);
				}

			

					
				Neb::Actor::mode_create::e		mode_create_;
				unsigned int				flag_;
				std::string				name_;

				physx::PxTransform			pose_;

				/** @brief Normal for planes. */
				physx::PxVec3				n_;
				/** @brief Distance for planes. */
				float					d_;

				//physx::PxVec3		velocity_;
				physx::PxVec3				velocity_;
				float					density_;

				Neb::Filter::Data			simulation_;
				Neb::Filter::Data			scene_query_;

				double					health_;



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
				Neb::Actor::Util::Parent_s			getParent();
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
				//Neb::Actor::Util::Raw				raw_;
				

				/** @brief Parent */
				Neb::Actor::Util::Parent_s			parent_;
		};
	}
}

#endif








