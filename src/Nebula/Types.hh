#ifndef NEBULA_TYPES_HH
#define NEBULA_TYPES_HH

#include <Nebula/Util/Map.hh>

/** @brief root namespace for @gru */
namespace Neb {

	class simulation_callback;


	class App;
	
	typedef std::shared_ptr<App>		App_s;
	typedef std::weak_ptr<App>		App_w;
	typedef std::unique_ptr<App>		App_u;








}

#endif
