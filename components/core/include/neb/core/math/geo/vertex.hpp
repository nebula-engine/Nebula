#ifndef __MATH_GEO_VERTEX
#define __MATH_GEO_VERTEX

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>


namespace math {
	namespace geo {
		class vertex {
			public:
				vertex() {};
				vertex(glm::vec3 np, glm::vec3 nn, glm::vec2 ntc, glm::vec3 ntangent, glm::vec3 nbinormal): p(np), n(nn), tc(ntc), tangent(ntangent), binormal(nbinormal) {}
				void		serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
				void		serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version);
				void		print(int sl);
				/** @brief position */
				glm::vec3		p;
				/** @brief normal */
				glm::vec3		n;
				/** @brief texture coordinate */
				glm::vec2		tc;
				/** @brief normal mapping */
				glm::vec3		tangent;
				glm::vec3		binormal;
		};
	}
}

#endif




