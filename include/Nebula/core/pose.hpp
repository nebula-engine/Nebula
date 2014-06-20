#ifndef NEBULA_CORE_POSE_HPP
#define NEBULA_CORE_POSE_HPP

#include <glm/gtc/matrix_transform.hpp>

#include <Nebula/math/Serialization/GLM.hpp>

namespace neb { namespace core {


	class pose {
		public:
			pose();
			pose(neb::core::pose const & rhs);
			pose(neb::core::pose&& rhs);
			pose(vec3 p, quat q);
			pose(vec3 p);
			pose(quat q);

			pose&		operator=(neb::core::pose const & rhs);
			pose		operator*(neb::core::pose const & rhs) const;

			template<typename Archive> void		serialize(Archive & ar, unsigned int const & version) {
				ar & pos_;
				ar & rot_;
			}
			
			mat4		mat4_cast() const;

			vec4		pos_;
			quat		rot_;
	};


}}

#endif


