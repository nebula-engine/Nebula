#ifndef __NEBULA_NS_HPP__
#define __NEBULA_NS_HPP__

namespace nebula
{
	namespace platform
	{
		namespace renderer
		{}
	}

	namespace content
	{
		namespace physics
		{
			namespace physx
			{}
		}
		namespace universe
		{
			namespace admin
			{}
		}
		namespace scene
		{
			namespace admin
			{}
			namespace physics
			{
				namespace physx
				{}
			}
			namespace renderer
			{}
		}
		namespace actor
		{
			namespace admin
			{
			}
			namespace physics
			{
				namespace physx
				{


				}
			}
			namespace renderer
			{

			}
		}
	}
}

namespace npr		= nebula::platform::renderer;

namespace ncp		= nebula::content::physics;
namespace ncpp		= nebula::content::physics::physx;

namespace ncua		= nebula::content::universe::admin;

namespace nca		= nebula::content::actor;
namespace ncaa		= nebula::content::actor::admin;
namespace ncap		= nca::physics;
namespace ncapp		= ncap::physx;
namespace ncar		= nebula::content::actor::renderer;

namespace nc_sc		= nebula::content::scene;
namespace nc_sc_a	= nc_sc::admin;
namespace nc_sc_p	= nc_sc::physics;
namespace nc_sc_pp	= nc_sc_p::physx;
namespace nc_sc_r	= nebula::content::scene::renderer;


#endif
