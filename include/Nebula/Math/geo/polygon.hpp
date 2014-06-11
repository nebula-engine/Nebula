#ifndef __MATH_GEO_POLYGON_H__
#define __MATH_GEO_POLYGON_H__

#include <memory>
#include <vector>

#include <Nebula/Util/typedef.hpp>

namespace math {
	namespace geo {
		class vertex {
			public:
				vertex() {};
				vertex(vec3 np, vec3 nn): p(np), n(nn) {}
				vec3	p;
				vec3	n;
		};
		struct tri {
			tri(std::shared_ptr<vertex>, std::shared_ptr<vertex>, std::shared_ptr<vertex>);

			std::shared_ptr<vertex>		v_[3];

			void	reset_normals();
		};
		struct polygon {
			int	triangle_count();


			std::vector< std::shared_ptr<tri> >		triangles_;

		};
	}
}

#endif


