#ifndef NEBULA_TYPES_HH
#define NEBULA_TYPES_HH

#include <memory>


/** @brief root namespace for @gru */
namespace neb {
	/** @brief %app */
	namespace app {
		class base;
	}
	
	/** @brief %net */
	namespace net {
		class server;
		class client;
		class communicating;
	}

	/** @brief %util */
	namespace util {
		struct terminal;
		struct command;
		struct command_set;
	}
}

#endif







