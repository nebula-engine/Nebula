#ifndef NEBULA_ACTOR_TYPE
#define NEBULA_ACTOR_TYPE

#include <string>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/nvp.hpp>

#include <gru/Enum.hpp>

namespace glutpp {
	namespace actor {

		DEFINE_ENUM(Type,int,
				((NONE)(0))
				((ACTOR)(1))
				)

	}
}

#endif


