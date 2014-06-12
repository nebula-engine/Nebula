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

	class simulation_callback;
	
	
	
	class Physics;
	
	typedef std::shared_ptr<Physics>			Physics_s;
	
	
	namespace App {
		class BaseFactory;

		typedef std::shared_ptr<BaseFactory>		BaseFactory_s;
		typedef std::weak_ptr<BaseFactory>		BaseFactory_w;

		
		class Base;

		typedef std::shared_ptr<Base>			Base_s;
		typedef std::weak_ptr<Base>			Base_w;
	}

	namespace Network {
		class Server;
		class Client;
		class Communicating;
		
		typedef std::shared_ptr<Server>			Server_s;
		typedef std::weak_ptr<Server>			Server_w;

		typedef std::shared_ptr<Client>			Client_s;
		typedef std::weak_ptr<Client>			Client_w;

		typedef std::shared_ptr<Communicating>		Communicating_s;
		typedef std::weak_ptr<Communicating>		Communicating_w;



	}
	
	namespace Util {
				
		typedef int			index_type;
	
		class Shared;

		typedef std::shared_ptr<Shared>		Shared_s;
	}
}

#endif
