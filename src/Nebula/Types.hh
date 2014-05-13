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




	namespace window {
		
		class raw;
		class desc;
		class window;

		typedef std::shared_ptr<window>		window_s;
		typedef std::weak_ptr<window>		window_w;

		typedef std::shared_ptr<desc>		desc_s;

	}



}

#endif
