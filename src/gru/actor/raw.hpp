#ifndef __GLUTPP_ACTOR_RAW_H__
#define __GLUTPP_ACTOR_RAW_H__

//#include <math/transform.hpp>
//#include <math/raw/raw.hpp>

#include <boost/serialization/nvp.hpp>

#include <PxPhysicsAPI.h>

//#include <galaxy/network/serial.hpp>
//#include <galaxy/util.hpp>

#include <gru/config.hpp>
#include <gru/shape/desc.hpp>

//template void gal::reset<glutpp::actor::raw>(std::shared_ptr<glutpp::actor::raw>&);

namespace glutpp {
	namespace actor {
		class filter_data {
			public:

			template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("word0",word0);
				ar & boost::serialization::make_nvp("word1",word1);
				ar & boost::serialization::make_nvp("word2",word2);
				ar & boost::serialization::make_nvp("word3",word3);
				
			}

			unsigned int word0;
			unsigned int word1;
			unsigned int word2;
			unsigned int word3;
		};
		class raw {
			public:
				friend class glutpp::actor::raw_factory;
				
				//friend void gal::reset<glutpp::actor::raw>(glutpp::actor::raw_s&);
				//template<typename T> friend void gal::reset(std::shared_ptr<T>&);
				
				enum
				{
					max_name_length = 31
				};

			protected:
				raw();
			public:
				virtual void			load(tinyxml2::XMLElement*);
				virtual void			load(glutpp::actor::actor_s);
				
				void				plane(tinyxml2::XMLElement*);
				void				controller(tinyxml2::XMLElement*);

				unsigned int			parse_filter(tinyxml2::XMLElement*, unsigned int);
				void				parse_filtering(tinyxml2::XMLElement*);
				
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
					ar & boost::serialization::make_nvp("filter_data_simulation",filter_data_.simulation_);
					ar & boost::serialization::make_nvp("filter_data_scene_query",filter_data_.scene_query_);
					
				}
				
				glutpp::actor::type::e		type_;
				glutpp::actor::mode_create::e	mode_create_;
				unsigned int			flag_;
				char				name_[32];

				physx::PxTransform		pose_;

				/** @brief Normal for planes. */
				physx::PxVec3		n_;
				/** @brief Distance for planes. */
				float				d_;

				//physx::PxVec3		velocity_;
				physx::PxVec3			velocity_;
				float				density_;

				struct {
					filter_data		simulation_;
					filter_data		scene_query_;
				} filter_data_;
		};
	}
}

#endif








