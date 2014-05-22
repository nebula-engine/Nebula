#ifndef __NEBULA_ACTOR_BASE_HH
#define __NEBULA_ACTOR_BASE_HH

#include <memory>

#include <boost/signals2.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <PxPhysicsAPI.h>

#include <Nebula/config.hh> // Nebula/config.hpp.in
//#include <Nebula/Actor/Util/desc.hh>

#include <Nebula/Util/Release.hh>
#include <Nebula/Math/Serialization.hh>

#include <Nebula/Filter.hh>

#include <Nebula/Message/Actor/Update.hh>
#include <Nebula/Graphics/texture.hh>
#include <Nebula/Graphics/material.hh>

#include <Nebula/Shape/Base.hh>
#include <Nebula/Shape/Util/Parent.hh>

#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/Util/Flag.hh>
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
			virtual public Neb::Util::Typed
		{
			public:
			

				Base();
				Base(Neb::Actor::Util::Parent_s);
				virtual ~Base();

				template<class D, typename... Args> inline void		dispatch(Args... a) {
					D::visit(this, a...);
				}

				virtual void				init();
				virtual void				releaseDerived();
				virtual void				cleanup();
				virtual void				release();

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

				/** @name Stepping @{ */
				virtual void					step(double const & time, double const & dt);


				//virtual void					step_local(double);
				//virtual void					step_remote(double);

				/** @} */
				/** @name Render @{ */
				void						draw(Neb::Graphics::Window::Base_s, physx::PxTransform);
				/** @} */

				/** @name Accessors @{ */
				virtual Neb::Actor::Base_s				get_projectile();

				Neb::Actor::Util::Address				getAddress() const;
				virtual physx::PxTransform				getPose();
				virtual physx::PxTransform				getPoseGlobal();
				/** @} */

				/** @name Accessors @{ */
				Neb::Actor::Util::Parent_s			getParent();
				void						setPose(physx::PxTransform pose);
				/** @} */

				void						notify_foundation_change_pose();
				void						load_lights(int&, physx::PxMat44);


				/** @todo move to derived class */
				virtual void						hit();
				virtual void						damage(float);


				// signal
				void				connect(Neb::Graphics::Window::Base_s);


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
				template<class Archive> void			serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i", i_);

					serializeData(ar, version);

					ar & boost::serialization::make_nvp("actors", Neb::Util::Parent<Neb::Actor::Base>::map_);
					ar & boost::serialization::make_nvp("shapes", Neb::Util::Parent<Neb::Shape::Base>::map_);
				}
				virtual void		serializeData(
						boost::archive::polymorphic_oarchive & ar,
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
				virtual void		serializeData(
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
				void			saveUpdate(
						boost::archive::polymorphic_oarchive & ar,
						unsigned int const & version) {
					auto address = getAddress();
					ar << boost::serialization::make_nvp("address", address);
					serializeData(ar, version);
				}
				/** @brief %Serialize specialization */
				void			loadUpdate(
						boost::archive::polymorphic_iarchive & ar,
						unsigned int const & version) {
					serializeData(ar, version);
				}




				Neb::Actor::mode_create::e		mode_create_;
				Neb::Actor::Util::Flag			flag_;
				std::string				name_;
				physx::PxTransform			pose_;
				/** @brief Normal for planes. */
				physx::PxVec3				n_;
				/** @brief Distance for planes. */
				float					d_;
				physx::PxVec3				velocity_;
				float					density_;

				Neb::Filter::Data			simulation_;
				Neb::Filter::Data			scene_query_;

				double					health_;





			public:
				/** @brief ID */
				int						i_;
				/** @brief Parent */
				Neb::Actor::Util::Parent_s			parent_;
		};
	}
}

#endif








