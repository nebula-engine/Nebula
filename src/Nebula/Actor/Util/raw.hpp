#ifndef __GLUTPP_ACTOR_RAW_H__
#define __GLUTPP_ACTOR_RAW_H__

//#include <math/transform.hpp>
//#include <math/raw/raw.hpp>

#include <boost/serialization/nvp.hpp>

#include <PxPhysicsAPI.h>

//#include <galaxy/network/serial.hpp>
//#include <galaxy/util.hpp>

#include <Nebula/config.hpp> // gru/config.hpp.in
#include <Nebula/shape/desc.hpp>
#include <Nebula/Actor/Types.hpp>
#include <Nebula/Actor/Util/Type.hpp>
#include <Nebula/Filter.hpp>
#include <Nebula/Typed.hpp>

//template void gal::reset<Neb::Actor::raw>(std::shared_ptr<glutpp::actor::raw>&);

namespace Neb {
	namespace Actor {
		class raw: public Neb::Typed {
			public:
				//friend class Neb::Actor::raw_factory;

				//template<typename T> friend void gal::reset(std::shared_ptr<T>&);

				enum
				{
					max_name_length = 31
				};
			protected:
				raw();
			public:
				virtual void			load(Neb::weak_ptr<Neb::Actor::Base>);

				raw&				operator=(raw const & r);

				//void				plane(tinyxml2::XMLElement*);
				//void				controller(tinyxml2::XMLElement*);

				unsigned int			parse_filter_word(tinyxml2::XMLElement*, unsigned int);
				void				parse_filter(tinyxml2::XMLElement*);
				void				parse_type(std::string);

				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {

					ar & boost::serialization::make_nvp("type",type_);
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

				Neb::Actor::Type			type_;
				Neb::Actor::mode_create::e		mode_create_;
				unsigned int				flag_;
				char					name_[32];

				physx::PxTransform			pose_;

				/** @brief Normal for planes. */
				physx::PxVec3				n_;
				/** @brief Distance for planes. */
				float					d_;

				//physx::PxVec3		velocity_;
				physx::PxVec3				velocity_;
				float					density_;

				gru::Filter::Data			simulation_;
				gru::Filter::Data			scene_query_;

				double					health_;

		};
	}
}
#endif








