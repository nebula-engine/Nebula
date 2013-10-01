#ifndef __NEBULA_NS_HPP__
#define __NEBULA_NS_HPP__

#include <boost/numeric/ublas/matrix.hpp>

namespace nebula
{
	namespace platform
	{
		namespace platform {}
		namespace window
		{
			namespace lin {}
			namespace win {}
		}
		namespace renderer
		{
			namespace gl
			{
				namespace glx {}
			}
		}
	}

	namespace content
	{
		namespace physics
		{
			namespace physx	{}
		}
		namespace universe
		{
			namespace admin	{}
		}
		namespace scene
		{
			namespace admin	{}
			namespace physics
			{
				namespace physx	{}
			}
			namespace renderer {}
		}
		namespace view
		{
			namespace admin
			{
				namespace human {}
			}
		}
		namespace actor
		{
			namespace admin {}
			namespace physics
			{
				namespace physx	{}
			}
			namespace renderer {}
		}
		namespace shape
		{
			namespace admin {}
			namespace physics {}
			namespace renderer {}
		}
	}

namespace ui
{
namespace object {}
}
}


namespace bnu		= boost::numeric::ublas;

// platform
namespace npp		= nebula::platform::platform;
namespace npr		= nebula::platform::renderer;
namespace npw		= nebula::platform::window;
namespace npwl		= nebula::platform::window::lin;


// content
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
namespace ncsa		= nebula::content::shape::admin;
namespace ncsp		= nebula::content::shape::physics;
namespace ncsr		= nebula::content::shape::renderer;

// ui
namespace nu		= nebula::ui;
namespace nuo		= nebula::ui::object;

#endif


