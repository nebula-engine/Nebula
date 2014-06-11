#ifndef NEBULA_ACTOR_BASE_HH
#define NEBULA_ACTOR_BASE_HH

#include <memory>

#include <boost/signals2.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <boost/serialization/map.hpp>

//#include <PxPhysicsAPI.h>

#include <Nebula/config.hh> // Nebula/config.hpp.in
//#include <Nebula/Actor/Util/desc.hh>

//#include <Nebula/Math/Serialization.hh>

#include <Nebula/Filter.hh>

#include <Nebula/Message/Actor/Update.hh>
#include <Nebula/Graphics/texture.hh>
#include <Nebula/Graphics/material.hh>

#include <Nebula/Shape/Base.hh>
#include <Nebula/Shape/Util/Parent.hh>
#include <Nebula/Actor/__base.hpp>
#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/Util/Flag.hh>
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
			virtual public neb::actor::__base,
			virtual public Neb::Actor::Util::Parent,
			virtual public Neb::Shape::Util::Parent
		{
			public:

				Base();
				Base(sp::shared_ptr<Neb::Actor::Util::Parent> parent);
				virtual ~Base();
			public:
				virtual void					init();
				virtual void					release();
				virtual void					step(Neb::Core::TimeStep const & ts);

			public:
				/** @name Render @{ */
				void						draw(sp::shared_ptr<Neb::Graphics::Context::Base>, mat4);
				/** @} */

				virtual mat4					getPose();
				virtual mat4					getPoseGlobal();

				/** @name Accessors @{ */
				Neb::Actor::Util::Parent_s			getParent();
				void						setPose(mat4 pose);
				/** @} */

				void						load_lights(int&, mat4);


				/** @todo move to derived class */
				// signal
				void						connect(Neb::Graphics::Window::Base_s);
				
				int						key_fun(sp::shared_ptr<Neb::Graphics::Window::Base> window,int,int,int,int);
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

					ar & boost::serialization::make_nvp("actors", /*gal::std::parent<Neb::Actor::Base>*/Neb::Actor::Util::Parent::map_);
					ar & boost::serialization::make_nvp("shapes", /*gal::std::parent<Neb::Shape::Base>*/Neb::Shape::Util::Parent::map_);
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





				Neb::Actor::mode_create::e		mode_create_;
				Neb::Actor::Util::Flag			flag_;
				std::string				name_;
				mat4					pose_;
				/** @brief Normal for planes. */
				vec3					n_;
				/** @brief Distance for planes. */
				float					d_;
				vec3					velocity_;
				float					density_;

				Neb::Filter::Data			simulation_;
				Neb::Filter::Data			scene_query_;

				double					health_;


			public:
				/** @brief Parent */
				Neb::Actor::Util::Parent_s			parent_;
		};
	}
}

#endif








