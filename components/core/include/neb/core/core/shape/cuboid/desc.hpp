#ifndef NEB_CORE_CORE_SHAPE_CUBOID_DESC_HPP
#define NEB_CORE_CORE_SHAPE_CUBOID_DESC_HPP

namespace neb { namespace core { namespace core { namespace shape { namespace cuboid {

	struct desc {
		
		desc(neb::core::pose pose, glm::vec3 scale):
			pose_(pose),
			scale_(scale),
			density_(1.0)
		{}
		desc(glm::vec3 scale):
			scale_(scale),
			density_(1.0)
		{}

		neb::core::pose		pose_;
		glm::vec3		scale_;
		float			density_;
	};

}}}}}

#endif

