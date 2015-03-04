#ifndef PHYSX_APP_BASE_HPP
#define PHYSX_APP_BASE_HPP

#include <memory>

#include <PxPhysicsAPI.h>

#include <neb/fnd/plug/phx/app/Base.hpp>
#include <neb/fnd/util/config.hpp> // neb/fnd/util/config.hpp.in
//#include <neb/fnd/core/scene/Base.hpp>
//#include <neb/phx/game/game/util/parent.hpp>

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
		physx::PxU32 constantBlockSize);

namespace neb { namespace phx { namespace app {
	class base:
		public gal::tmp::Verbosity<neb::phx::app::base>,
		virtual public neb::fnd::plug::phx::app::Base
		//virtual public neb::phx::game::game::util::parent
	{
		public:
			using gal::tmp::Verbosity<neb::phx::app::base>::printv;
			//static std::shared_ptr<phx::app::base>		global();
			base();
		protected:
			virtual void					init(parent_t * const & parent);
		public:
			void						release();
			virtual void					step(gal::etc::timestep const & ts);
			physx::PxConvexMeshGeometry*			frustrum_geometry(glm::mat4 proj);
			bool						query(
					physx::PxConvexMeshGeometry& g0,
					glm::mat4 v0,
					physx::PxConvexMeshGeometry& g1,
					glm::mat4 v1);
			physx::PxDefaultCpuDispatcher*			create_default_cpu_dispatcher();
			DefaultErrorCallback 				px_default_error_callback_;
			physx::PxDefaultAllocator 			px_default_allocator_callback_;
			physx::PxFoundation*				px_foundation_;
			physx::PxPhysics*				px_physics_;
			physx::PxProfileZoneManager*			px_profile_zone_manager_;
			physx::PxCooking*				px_cooking_;
			//physx::pxtask::CudaContextManager*		px_cuda_context_manager_;
			physx::PxControllerManager*			px_character_controller_manager_;
	};
}}}

#endif
