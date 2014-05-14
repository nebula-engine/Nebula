#ifndef NEBULA_TYPES_HH
#define NEBULA_TYPES_HH

#include <Nebula/Util/Map.hh>

/** @brief root namespace for @gru */
namespace Neb {

	class simulation_callback;

	namespace App {
		class Base;

		typedef std::shared_ptr<Base>		Base_s;
		typedef std::weak_ptr<Base>		Base_w;
		typedef std::unique_ptr<Base>		Base_u;
	}

	namespace Network {
		class Server;
		class Client;

		typedef std::shared_ptr<Server>		Server_s;
		typedef std::weak_ptr<Server>		Server_w;

		typedef std::shared_ptr<Client>		Client_s;
		typedef std::weak_ptr<Client>		Client_w;



	}
}

#endif
