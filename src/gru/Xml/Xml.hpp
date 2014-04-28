#ifndef GRU_XML_XML_HPP
#define GRU_XML_XML_HPP

#include <PxPhysicsAPI.h>

namespace gru {
	namespace Xml {

		physx::PxVec3	parseVec3(tinyxml2::XMLElement* element) {
			physx::PxVec3 ret(0,0,0);

			if(!element) return ret;

			char const * buf = element->GetText();

			int c = sscanf(buf, "%f,%f,%f", &ret.x, &ret.y, &ret.z);
			assert(c == 3);

			return ret;
		}
	}
}

#endif


