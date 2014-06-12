#ifndef NEBULA_TYPES_HH
#define NEBULA_TYPES_HH

#include <memory>

//#include <Nebula/Util/Map.hh>

/** @todo since all classes used in factory derive from neb::Util::Shared, theres no need to have multiple
 * factory objects for different type. You can still have different factories for different uses (i.e. remote and local)
 * but all default factories can be merged into one!!! Also implies that Factory doesnt need to be template.
 */

/** @brief root namespace for @gru */
namespace neb {
	/** @brief %app */
	namespace app {
		class Base;
	}
	
	/** @brief %net */
	namespace net {
		class server;
		class client;
		class communicating;
	}
}

#endif
