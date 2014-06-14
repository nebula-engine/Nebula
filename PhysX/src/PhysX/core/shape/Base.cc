#include <Nebula/debug.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Shape/Base.hh>

#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/glsl/attrib.hh>

//#include <Nebula/Util/Map.hh>

#include <PhysX/core/shape/base.hpp>

px::core::shape::base::base(sp::shared_ptr<neb::core::shape::util::parent> parent):
	neb::core::shape::base(parent)
{
	NEBULA_SHAPE_BASE_FUNC;
	assert(parent);
}
px::core::shape::base::~base() {}
//void			px::core::shape::base::release() {
//}
void			px::core::shape::base::step(double const & time, double const & dt) {
}
void			px::core::shape::base::init() {
	//NEBULA_DEBUG_0_FUNCTION;

	neb::core::shape::Physical::init();

	create_physics();
}
void			px::core::shape::base::create_physics() {

	//NEBULA_DEBUG_0_FUNCTION;

	assert(!parent_.expired());

	auto parent = getParent();
	assert(parent);

	auto actor = parent->isActorBase();

	if(actor) {
		auto rigidactor = actor->isActorRigidActor();//std::dynamic_pointer_cast<neb::core::actor::Rigid_Actor>(parent_.lock());

		if(rigidactor) {
			physx::PxRigidActor* px_rigid_actor = static_cast<physx::PxRigidActor*>(rigidactor->px_actor_);

			physx::PxMaterial* px_mat = neb::Physics::global()->px_physics_->createMaterial(1,1,1);

			px_shape_ = px_rigid_actor->createShape( *(to_geo()), *px_mat );
		}
	}
}







