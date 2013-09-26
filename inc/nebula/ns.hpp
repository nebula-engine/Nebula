#ifndef __NEBULA_NS_HPP__
#define __NEBULA_NS_HPP__

namespace nebula
{
	namespace content
	{
		namespace physics
		{
			namespace physx
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


namespace ncp		= nebula::content::physics;
namespace ncpp		= nebula::content::physics::physx;
namespace nca		= nebula::content::actor;
namespace ncaa		= nca::admin;
namespace ncap		= nca::physics;
namespace ncapp		= ncap::physx;
namespace nc_sc		= nebula::content::scene;
namespace nc_sc_a	= nc_sc::admin;
namespace nc_sc_p	= nc_sc::physics;
namespace nc_sc_pp	= nc_sc_p::physx;



#endif
