#ifndef __GLUTPP_SHAPE_RAW_H__
#define __GLUTPP_SHAPE_RAW_H__

#include <vector>

#include <boost/serialization/nvp.hpp>

//#include <tinyxml2.h>

//#include <math/vec3.hpp>
//#include <math/transform.hpp>

//#include <galaxy/network/serial.hpp>

#include <gru/Archive.hpp>

#include <gru/Types/Material.hpp>

#include <gru/Math/Typedef.hpp>

#include <gru/config.hpp>
#include <gru/material.hpp>

//#include <gru/shape/desc.hpp>

namespace glutpp {
	namespace shape {
		class Raw {
			public:
				enum
				{
					max_filename_length = 20
				};

				Raw();

				Raw&			operator=(Raw const &);

				//void			load(tinyxml2::XMLElement*);
				void			parse_type(char const *);

				void			box(Neb::Math::Vec3);
				void			box(tinyxml2::XMLElement*);

				void			sphere(float);
				void			sphere(tinyxml2::XMLElement*);
				
				template<class Archive>	void	serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("type",type_);
					ar & boost::serialization::make_nvp("flag",flag_);
					ar & boost::serialization::make_nvp("pose",pose_);
					ar & boost::serialization::make_nvp("s",s_);
					ar & boost::serialization::make_nvp("image",image_);
					ar & boost::serialization::make_nvp("normal",normal_);
					ar & boost::serialization::make_nvp("material",material_);
				}

			public:
				/** @brief Type.
				 * used to tell shape factory what to create */
				int				type_;
				unsigned int			flag_;
				
				/** @brief Pose. */
				physx::PxTransform		pose_;
				/** @brief Scale. */
				physx::PxVec4			s_;
				
				/** @brief Name of image file */
				char				image_[max_filename_length];
				/** @brief Name of normal map file */
				char				normal_[max_filename_length];
				/** @brief Material. */
				glutpp::material::raw		material_;
		};
		namespace Box {
			class Raw {
				
			};
		}
		namespace Sphere {
			class Raw {
			};
		}
		
		//typedef gal::network::vector<glutpp::material::raw> vec_mat;
		
		//typedef std::shared_ptr<vec_mat> vec_mat_s;
		/*	
		class raw { //: public gal::network::serial_ext<raw_base, vec_mat> {
			public:
				raw&		operator=(raw const &);
				
				void		load(tinyxml2::XMLElement*);
				
				//raw_base_s	get_raw_base() const;
				//vec_mat_s	get_vec_mat() const;
				
				glutpp::shape::raw_base_s		raw_base_;
				std::vector<glutpp::material::raw_s>	materials_;
		};*/
	}
}

#endif



