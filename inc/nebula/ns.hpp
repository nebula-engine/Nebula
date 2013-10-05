#ifndef __NEBULA_NS_HPP__
#define __NEBULA_NS_HPP__

#include <boost/numeric/ublas/matrix.hpp>

namespace nebula
{
	namespace asio
	{
		namespace network {}
	}

	namespace framework {}

	namespace platform
	{
		namespace platform
		{
			namespace lin {}
			namespace win {}
		}
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




namespace n0x00000 = nebula;
namespace n0x10000 = nebula::framework;
namespace n0x20000 = nebula::platform;
namespace n0x30000 = nebula::content;


/*namespace n0x007 = nebula
namespace n0x008 = nebula
namespace n0x009 = nebula
namespace n0x010 = nebula
namespace n0x011 = nebula
namespace n0x012 = nebula
namespace n0x013 = nebula
namespace n0x014 = nebula
namespace n0x015 = nebula
namespace n0x016 = nebula
namespace n0x017 = nebula
namespace n0x018 = nebula
namespace n0x019 = nebula
namespace n0x020 = nebula
namespace n0x021 = nebula
namespace n0x022 = nebula
namespace n0x023 = nebula
namespace n0x023 = nebula
namespace n0x024 = nebula
namespace n0x025 = nebula
namespace n0x026 = nebula
namespace n0x027 = nebula
namespace n0x028 = nebula
namespace n0x029 = nebula
namespace n0x030 = nebula
namespace n0x031 = nebula
namespace n0x032 = nebula
namespace n0x033 = nebula
namespace n0x034 = nebula
namespace n0x035 = nebula
namespace n0x036 = nebula
namespace n0x037 = nebula
namespace n0x038 = nebula
namespace n0x039 = nebula
namespace n0x040 = nebula
namespace n0x041 = nebula
namespace n0x042 = nebula
namespace n0x043 = nebula
namespace n0x044 = nebula
namespace n0x045 = nebula
namespace n0x046 = nebula
namespace n0x047 = nebula
namespace n0x048 = nebula
namespace n0x049 = nebula



namespace n0x100 = nebula
namespace n0x101 = nebula
namespace n0x102 = nebula
namespace n0x103 = nebula
namespace n0x104 = nebula
namespace n0x105 = nebula
namespace n0x106 = nebula
namespace n0x107 = nebula
namespace n0x108 = nebula
namespace n0x109 = nebula
namespace n0x110 = nebula
namespace n0x111 = nebula
namespace n0x112 = nebula
namespace n0x113 = nebula
namespace n0x114 = nebula
namespace n0x115 = nebula
namespace n0x116 = nebula
namespace n0x117 = nebula
namespace n0x118 = nebula
namespace n0x119 = nebula
namespace n0x120 = nebula
namespace n0x121 = nebula
namespace n0x122 = nebula
namespace n0x123 = nebula
namespace n0x123 = nebula
namespace n0x124 = nebula
namespace n0x125 = nebula
namespace n0x126 = nebula
namespace n0x127 = nebula
*/




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
namespace ncsa		= nebula::content::shape::admin;
namespace ncsp		= nebula::content::shape::physics;
namespace ncsr		= nebula::content::shape::renderer;

// ui
namespace nu		= nebula::ui;
namespace nuo		= nebula::ui::object;

#endif


