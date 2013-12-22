#ifndef __NEBULA_PACKET_BASIC_H__
#define __NEBULA_PACKET_BASIC_H__

#include <math/vec3.h>
#include <math/transform.h>

namespace neb
{
	namespace packet
	{
		struct vec3
		{
			int		from_math(math::vec3 const &);
			math::vec3	to_math();

			float	x, y, z;
		};
		struct quat
		{
			
			int		from_math(math::quat const &);
			math::quat	to_math();

			float	x, y, z, w;
		};
		struct transform
		{
			math::transform		to_math();
			int			from_math(math::transform const &);
			
			vec3	p;
			quat	q;
		};
	}
}

#endif
