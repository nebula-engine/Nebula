#include <Nebula/debug.hh>
#include <Nebula/app/Base.hh>
#include <Nebula/core/shape/Base.hh>

#include <Nebula/core/light/Base.hh>
#include <Nebula/gfx/glsl/attrib.hh>

//#include <Nebula/util/Map.hh>

#include <PhysX/app/base.hpp>
#include <PhysX/core/shape/base.hpp>
#include <PhysX/core/actor/rigidactor/base.hpp>


phx::core::shape::base::base(sp::shared_ptr<phx::core::shape::util::parent> parent):
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
void			phx::core::shape::base::release() {
	//NEBULA_DEBUG_0_FUNCTION;

	neb::core::shape::base::release();
	
	if(px_shape_) {
		px_shape_->release();
		px_shape_ = NULL;
	}
}
void			phx::core::shape::base::create_physics() {

	//NEBULA_DEBUG_0_FUNCTION;

	auto actor = getPxParent()->isPxActorBase();

	if(actor) {
		auto rigidactor = actor->isPxActorRigidActorBase();//std::dynamic_pointer_cast<neb::core::actor::Rigid_Actor>(parent_.lock());

		if(rigidactor) {
			assert(rigidactor->px_actor_);
			
			auto px_rigidactor = rigidactor->px_actor_->isRigidActor();
			assert(px_rigidactor);

			physx::PxMaterial* px_mat = phx::app::base::global()->px_physics_->createMaterial(1,1,1);

			px_shape_ = px_rigidactor->createShape( *(to_geo()), *px_mat );
		}
	}
}
sp::shared_ptr<phx::core::shape::util::parent>		phx::core::shape::base::getPxParent() {
	
	auto parent = parent_.lock();
	assert(parent);
	
	auto pxparent(sp::dynamic_pointer_cast<phx::core::shape::util::parent>(parent));
	
	if(!pxparent) {
		std::cout << typeid(*parent).name() << std::endl;
		abort();
	}

	return pxparent;
}







