#ifndef __NEBULA_GEOMETRY_H__
#define __NEBULA_GEOMETRY_H__

namespace neb
{
	class geometry
	{
		public:
			enum type
			{
				BOX,
				SPHERE
			};

			type			type_;
			physx::PxGeometry*	geo_;
	};
	class box
	{
		public:
			math::vec3		s_;

	};
}

#endif

