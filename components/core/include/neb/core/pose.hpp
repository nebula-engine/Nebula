#ifndef NEBULA_CORE_POSE_HPP
#define NEBULA_CORE_POSE_HPP

#include <glm/gtc/matrix_transform.hpp>

#include <neb/core/math/Serialization/glm.hpp>

namespace neb { namespace core {
	/** @brief %pose
	*
	*/
	class pose {
		public:
			pose();
			pose(neb::core::pose const & rhs);
			pose(neb::core::pose&& rhs);
			pose(glm::vec3 p, glm::quat q);
			pose(glm::vec3 p);
			pose(glm::quat q);

			pose&		operator=(neb::core::pose const & rhs);
			pose		operator*(neb::core::pose const & rhs) const;

			template<typename Archive> void		serialize(Archive & ar, unsigned int const & version) {
<<<<<<< HEAD
				ar & pos_;
				ar & rot_;
=======
				ar & boost::serialization::make_nvp("pos", pos_);
				ar & boost::serialization::make_nvp("rot", rot_);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
			}
			
			glm::mat4		mat4_cast() const;

			glm::vec3		pos_;
			glm::quat		rot_;
	};


}}

#endif


