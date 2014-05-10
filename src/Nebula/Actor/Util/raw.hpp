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
#include <Nebula/Util/Typed.hpp>

//template void gal::reset<Neb::Actor::raw>(std::shared_ptr<glutpp::actor::raw>&);

namespace Neb {
	namespace Actor {
		class raw: public Neb::Typed {
			public:
				Raw();
				Raw&				operator=(Neb::Actor::Base_w const &);

				Raw&				operator=(Raw const &);


				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
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

		};
	}
}
#endif








