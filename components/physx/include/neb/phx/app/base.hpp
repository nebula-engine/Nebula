#ifndef PHYSX_APP_BASE_HPP
#define PHYSX_APP_BASE_HPP

#include <memory>

#include <PxPhysicsAPI.h>

#include <neb/core/util/config.hpp>
#include <neb/core/app/__core.hpp>
#include <neb/core/core/scene/base.hpp>

#include <neb/phx/core/scene/util/parent.hpp>
<<<<<<< HEAD
#include <neb/phx/game/game/util/parent.hpp>
=======
//#include <neb/phx/game/game/util/parent.hpp>
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

class DefaultErrorCallback:
	public physx::PxErrorCallback
{
	public:
		void reportError(
				physx::PxErrorCode::Enum code,
				char const * message,
				char const * file,
				int line);
};

physx::PxFilterFlags DefaultFilterShader(
		physx::PxFilterObjectAttributes attributes0,
		physx::PxFilterData filterData0,
		physx::PxFilterObjectAttributes attributes1,
		physx::PxFilterData filterData1,
		physx::PxPairFlags& pairFlags,
		const void* constantBlock,
		physx::PxU32 constantBlockSize );

namespace neb {
	namespace phx {
		namespace app {


			class base:
				virtual public neb::app::__core,
<<<<<<< HEAD
				virtual public neb::phx::core::scene::util::parent,
				virtual public neb::phx::game::game::util::parent
=======
				virtual public neb::phx::core::scene::util::parent
				//virtual public neb::phx::game::game::util::parent
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
			{
				public:
					static std::shared_ptr<phx::app::base>		global();
					base();
				protected:
					void						__init();
				public:
					void						release();
					virtual void					step(gal::etc::timestep const & ts);
					DefaultErrorCallback 				px_default_error_callback_;
					physx::PxDefaultAllocator 			px_default_allocator_callback_;
					physx::PxFoundation*				px_foundation_;
					physx::PxPhysics*				px_physics_;
					physx::PxProfileZoneManager*			px_profile_zone_manager_;
					physx::PxCooking*				px_cooking_;
					//physx::pxtask::CudaContextManager*		px_cuda_context_manager_;
					physx::PxControllerManager*			px_character_controller_manager_;
			};
		}
	}
}


#endif
