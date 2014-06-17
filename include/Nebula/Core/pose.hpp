#ifndef NEBULA_CORE_POSE_HPP
#define NEBULA_CORE_POSE_HPP

#include <glm/gtc/matrix_transform.hpp>

#include <Nebula/Math/Serialization/GLM.hpp>

namespace neb { namespace core {


	class pose {
		public:
			pose(): pos_(0,0,0,1) {};
			pose(quat q, vec4 p): pos_(p), rot_(q) {}
			pose		operator*(neb::core::pose const & rhs) const {
				pose ret;
				ret.pos_ = pos_ + rot_ * rhs.pos_;
				ret.rot_ = rot_ * rhs.rot_;
				return ret;
			}
			template<typename Archive> void		serialize(Archive & ar, unsigned int const & version) {
				ar & pos_;
				ar & rot_;
			}
			
			mat4		mat4_cast() const {
				mat4 ret(glm::mat4_cast(rot_));
				return glm::translate(ret, vec3(pos_));
			}

			vec4		pos_;
			quat		rot_;
	};


}}

#endif


