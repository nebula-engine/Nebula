#ifndef _CONTENT_PHYSICS_PHYSICS_PHYSX_H
#define _CONTENT_PHYSICS_PHYSICS_PHYSX_H

#include <memory>

#include <PxPhysicsAPI.h>

//#include <content/Content.h>
#include <content/Physics/CO_PH_Physics.h>

using namespace std;

/// default error callback for %PhysX
class DefaultErrorCallback: public physx::PxErrorCallback {
public:
	/// Reports an error code
	void 	reportError( physx::PxErrorCode::Enum code, const char *message, const char *file, int line);
};



namespace Content {
	namespace Physics {
		namespace PhysX {
			/// %Physx Implementation
			class Physics: public CO_PH_Physics {
			public:
				/// Constructor
							Physics() {};
				/// Destructor
							~Physics() {};
				/// initialize
				void		VInit( Void* data );
				/// shutdown
				void		VShutDown();
			


				///@name Register Objects
				///@{
				/// %CO_SC_AD_Scene
				void		RegisterScene( CO_SC_AD_Scene* scene );
				/// %RigidDynamic
				void		RegisterRigidDynamic( ::CO_AC_AD_RigidDynamic* rigidDynamic );
				/// %Controller
				void		RegisterController( ::CO_AC_AD_Controller*& controller, CO_SC_AD_Scene* scene );
				///@}



				///@name fetch objects
				///@{
				/// physx physics
				physx::PxPhysics*					GetPxPhysics()				const { return m_physics; }
				/// physx controller manager
				physx::PxControllerManager*			GetPxControllerManager()	const { return m_characterControllerManager; }
				///@}


				static	physx::PxTransform			TransformToPxTransform( Math::Transformf& trans );
				static	Math::Transformf			PxTransformToTransform( physx::PxTransform& trans );
			protected:
				///@name PhysX Objects
				///@{
				/***/
				/// physx default error callback
				DefaultErrorCallback 				m_defaultErrorCallback;
				/// physx default allocator
				physx::PxDefaultAllocator 			m_defaultAllocatorCallback;
				/// physx foundation
				physx::PxFoundation*				m_foundation;
				/// physx physics
				physx::PxPhysics*					m_physics;
				/// physx profile zone manager
				physx::PxProfileZoneManager*		m_profileZoneManager;
				/// physx cooking
				physx::PxCooking*					m_cooking;
				/// physx cuda context manager
				physx::pxtask::CudaContextManager*	m_cudaContextManager;
				/// physx controller manager
				physx::PxControllerManager*			m_characterControllerManager;
				///@}
			};
		}
	}
}

#endif









