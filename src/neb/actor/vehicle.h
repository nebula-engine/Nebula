#ifndef __NEBULA_ACTOR_VEHICLE_H__
#define __NEBULA_ACTOR_VEHICLE_H__

namespace neb
{
	namespace actor
	{
		class vehicle: public neb::actor::Rigid_Dynamic
		{
			public:
			
				physx::PxVehicleDrive4W* px_vehicle_drive_;
			
		};
	}
}

#endif

