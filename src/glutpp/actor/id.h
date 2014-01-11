#ifndef __NEBULA_ACTOR_ID_H__
#define __NEBULA_ACTOR_ID_H__

#include <math/transform.h>
#include <math/raw/raw.h>

#include <gal/network/serial.h>

#include <glutpp/actor/id.h>
#include <glutpp/shape/desc.h>

namespace glutpp {
	namespace actor {

		struct id: gal::network::serial<id> {
			int i_;
		};
	}
}

#endif








