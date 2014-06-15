#include <Nebula/debug.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Shape/Base.hh>

#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/glsl/attrib.hh>

//#include <Nebula/Util/Map.hh>

#include <PhysX/app/base.hpp>
#include <PhysX/core/shape/base.hpp>
#include <PhysX/core/actor/rigidactor/base.hpp>


phx::core::shape::base::base(sp::shared_ptr<neb::core::shape::util::parent> parent):
	neb::core::shape::base(parent)
{
	NEBULA_SHAPE_BASE_FUNC;
	assert(parent);
}
phx::core::shape::base::~base() {}
//void			phx::core::shape::base::release() {
//}
void			phx::core::shape::base::step(neb::core::TimeStep const & ts) {
}
void			phx::core::shape::base::init() {
	//NEBULA_DEBUG_0_FUNCTION;

	neb::core::shape::base::init();

	create_physics();
}
void			phx::core::shape::base::create_physics() {

	//NEBULA_DEBUG_0_FUNCTION;


	auto actor = parent_->isPxActorBase();

	if(actor) {
		auto rigidactor = actor->isPxActorRigidActorBase();//std::dynamic_pointer_cast<neb::core::actor::Rigid_Actor>(parent_.lock());

		if(rigidactor) {
			physx::PxRigidActor* px_rigid_actor = static_cast<physx::PxRigidActor*>(rigidactor->px_actor_);

			physx::PxMaterial* px_mat = phx::app::base::global()->px_physics_->createMaterial(1,1,1);

			px_shape_ = px_rigid_actor->createShape( *(to_geo()), *px_mat );
		}
	}
}







