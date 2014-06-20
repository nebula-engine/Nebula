#ifndef NEBULA_ACTOR_TYPE
#define NEBULA_ACTOR_TYPE

#include <string>
#include <map>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/nvp.hpp>

#include <Nebula/Enum.hh>

namespace neb {
	namespace actor {

		DEFINE_TYPE(Type,
				((NONE)(0))
				((ACTOR)(1))
				((RIGID_ACTOR)(2))
				((RIGID_STATIC)(3))
				((RIGID_BODY)(4))
				((RIGID_DYNAMIC)(5))
				((PLANE)(6))
				((CONTROLLER)(7))
				((EMPTY)(8))
				)

	}
}

#endif


