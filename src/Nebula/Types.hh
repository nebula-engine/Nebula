#ifndef NEBULA_TYPES_HH
#define NEBULA_TYPES_HH

#include <memory>

//#include <Nebula/Util/Map.hh>

/** @brief root namespace for @gru */
namespace Neb {

	class simulation_callback;

	namespace App {
		class BaseFactory;

		typedef std::shared_ptr<BaseFactory>		BaseFactory_s;
		typedef std::weak_ptr<BaseFactory>		BaseFactory_w;

		
		class Base;

		typedef std::shared_ptr<Base>		Base_s;
		typedef std::weak_ptr<Base>		Base_w;
	}

	namespace Network {
		class Server;
		class Client;
		class Communicating;
		
		typedef std::shared_ptr<Server>		Server_s;
		typedef std::weak_ptr<Server>		Server_w;

		typedef std::shared_ptr<Client>		Client_s;
		typedef std::weak_ptr<Client>		Client_w;

		typedef std::shared_ptr<Communicating>		Communicating_s;
		typedef std::weak_ptr<Communicating>		Communicating_w;



	}
	
	namespace Util {
		typedef int	index_type;
	}
}

#endif
