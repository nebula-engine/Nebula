#ifndef __NEBULA_NS_HPP__
#define __NEBULA_NS_HPP__

#include <boost/numeric/ublas/matrix.hpp>

/// %nebula
namespace nebula
{
	/// asio
	/**
	 * asynchronous in/out using boost::asio
	 */
	namespace asio
	{
		class message;
		class mailbox;
		class destination;

		/// network
		namespace network
		{
			class base;
		}
	}

	/// framework
	/**
	 * Contains the application class.
	 */
	namespace framework
	{
		class app;
		class renderable;
	}

	namespace platform
	{
		class key;

		namespace platform
		{
			class base;

			namespace lin
			{
				class base;
			}
			namespace win
			{
				class base;
			}
		}
		namespace window
		{
			class base;

			namespace lin
			{
				class base;
			}
			namespace win
			{
				class base;
			}
		}
		namespace renderer
		{
			class base;

			namespace gl
			{
				class base;	

				namespace glx
				{
					class base;
				}
			}
		}
	}

	namespace content
	{
		class base;
		class camera;

		namespace physics
		{
			class base;

			namespace physx
			{
				class base;
			}
		}
		namespace universe
		{
			namespace admin
			{
				class base;
			}
		}
		namespace scene
		{
			namespace admin
			{
				class base;
			}
			namespace physics
			{
				class base;	

				namespace physx
				{
					class base;
				}
			}
			namespace renderer
			{
				class base;
			}
		}
		namespace view
		{
			namespace admin
			{
				class base;

				namespace human
				{
					class base;
				}
			}
		}
		namespace actor
		{
			namespace admin
			{
				class base;
				class actor;
				class rigid_actor;
				class rigid_body;
				class rigid_dynamic;
				class rigid_dynamic_box;
				class rigid_static;
				class rigid_static_plane;
				class controller;
				class vehicle;

				class material;
			}
			namespace physics
			{
				class base;
				class actor;
				class rigid_actor;
				class rigid_body;
				class rigid_dynamic;
				class rigid_dynamic_box;
				class rigid_static;
				class rigid_static_plane;
				class controller;
				class vehicle;


				class material;

				namespace physx
				{
					class base;
					class actor;
					class rigid_actor;
					class rigid_body;
					class rigid_dynamic;
					class rigid_dynamic_box;
					class rigid_static;
					class rigid_static_plane;
					class controller;
					class vehicle;

					class material;
				}
			}
			namespace renderer
			{
				class base;
				class actor;
				class rigid_actor;
				class rigid_body;
				class rigid_dynamic;
				class rigid_dynamic_box;
				class rigid_static;
				class rigid_static_plane;
				class controller;
				class vehicle;

				class material;
			}
		}
		namespace shape
		{
			namespace admin
			{
				class base;
				class box;
			}
			namespace physics
			{
				class base;
				class box;

				namespace physx
				{
					class base;
					class box;
				}
			}
			namespace renderer
			{
				class base;
				class box;
			}
		}
	}

	namespace ui
	{
		namespace layout
		{
			class base;
		}
		namespace object
		{
			class base;
			class button;
			class textview;
		}
	}
}




namespace n00000 = nebula;
namespace n10000 = nebula::framework;
namespace n20000 = nebula::platform;
namespace n23000 = nebula::platform::renderer;
namespace n30000 = nebula::content;
namespace n40000 = nebula::asio;
namespace n50000 = nebula::ui;
namespace n51000 = nebula::ui::layout;
namespace n52000 = nebula::ui::object;


namespace bnu		= boost::numeric::ublas;

// asio
namespace na		= nebula::asio;

// framework
namespace nf		= nebula::framework;

// platform
namespace np		= nebula::platform;
namespace npp		= nebula::platform::platform;
namespace nppl		= nebula::platform::platform::lin;
namespace npr		= nebula::platform::renderer;
namespace nprg		= nebula::platform::renderer::gl;
namespace nprgg		= nebula::platform::renderer::gl::glx;
namespace npw		= nebula::platform::window;
namespace npwl		= nebula::platform::window::lin;


// content
namespace nc		= nebula::content;
namespace ncp		= nebula::content::physics;
namespace ncpp		= nebula::content::physics::physx;

// universe
namespace ncua		= nebula::content::universe::admin;

// actor
namespace nca		= nebula::content::actor;
namespace ncaa		= nebula::content::actor::admin;
namespace ncap		= nca::physics;
namespace ncapp		= ncap::physx;
namespace ncar		= nebula::content::actor::renderer;

// scene
namespace nc_sc		= nebula::content::scene;
namespace nc_sc_a	= nc_sc::admin;
namespace nc_sc_p	= nc_sc::physics;
namespace nc_sc_pp	= nc_sc_p::physx;
namespace nc_sc_r	= nebula::content::scene::renderer;

// view
namespace ncva		= nebula::content::view::admin;
namespace ncvah		= nebula::content::view::admin::human;


// shape
namespace ncs		= nebula::content::shape;
namespace ncsa		= nebula::content::shape::admin;
namespace ncsp		= nebula::content::shape::physics;
namespace ncsr		= nebula::content::shape::renderer;

// ui
namespace nu		= nebula::ui;
namespace nul		= nebula::ui::layout;
namespace nuo		= nebula::ui::object;


#endif


