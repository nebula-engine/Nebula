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



	/** @brief %Shape */	
	namespace Shape {
		struct flag {
			enum e {
				SHOULD_RELEASE = 1 << 0,
				IMAGE          = 1 << 1,
			};
		};

		class Raw;
		class desc;
		class base;
		class shape;
		class parent;

		typedef std::shared_ptr<base>		base_s;
		typedef std::weak_ptr<base>		base_w;


		typedef std::shared_ptr<desc>		desc_s;
		typedef std::weak_ptr<desc>		desc_w;
		typedef std::unique_ptr<desc>		desc_u;


		typedef std::shared_ptr<Raw>		Raw_s;
		typedef std::weak_ptr<Raw>		Raw_w;
		typedef std::unique_ptr<Raw>		Raw_u;


		typedef std::shared_ptr<shape>		shape_s;
		typedef std::weak_ptr<shape>		shape_w;
		typedef std::unique_ptr<shape>		shape_u;
		

		typedef std::shared_ptr<parent>		parent_s;
		typedef std::unique_ptr<parent>		parent_u;
		typedef std::weak_ptr<parent>		parent_w;

	}


}

#endif
