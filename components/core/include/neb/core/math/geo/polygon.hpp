#ifndef __MATH_GEO_POLYGON_H__
#define __MATH_GEO_POLYGON_H__

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

<<<<<<< HEAD
using namespace std;

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
		struct tri {
			tri(std::shared_ptr<vertex>, std::shared_ptr<vertex>, std::shared_ptr<vertex>);

			shared_ptr<vertex>		v_[3];

			void	reset_normals();
		};
		struct polygon {
			int	triangle_count();


			vector< std::shared_ptr<tri> >		triangles_;

=======


namespace math {
	namespace geo {

		class vertex;

		struct triangle {
			triangle();
			triangle(vertex*, vertex*, vertex*);
			triangle&	operator=(triangle const &);
			vertex*		verts_[3];

			void	reset_normals();
		};
		class polygon {
			public:
				polygon();
				triangle*	getTriangles();
				unsigned int	getNbTriangles();
				void		setTriangles(triangle*, unsigned int);
			protected:
				triangle*	triangles_;
				unsigned int	nbTriangles_;
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
		};
	}
}

#endif


