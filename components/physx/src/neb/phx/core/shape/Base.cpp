#include <neb/core/util/debug.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/light/base.hpp>

#include <neb/gfx/glsl/attrib.hh>


#include <neb/phx/app/base.hpp>
#include <neb/phx/core/shape/base.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>


neb::phx::core::shape::base::base(std::shared_ptr<phx::core::shape::util::parent> parent):
	neb::core::core::shape::base(parent)
{
	//NEBULA_SHAPE_BASE_FUNC;
	assert(parent);
}
neb::phx::core::shape::base::~base() {}
//void			neb::phx::core::shape::base::release() {
//}
void			neb::phx::core::shape::base::step(gal::etc::timestep const & ts) {
}
void			neb::phx::core::shape::base::init() {
	//NEBULA_DEBUG_0_FUNCTION;

	neb::core::core::shape::base::init();

	create_physics();
}
void			neb::phx::core::shape::base::release() {
	//NEBULA_DEBUG_0_FUNCTION;

	neb::core::core::shape::base::release();
	
	if(px_shape_) {
		
		auto ra = ::std::dynamic_pointer_cast<neb::phx::core::actor::rigidactor::base>(parent_.lock());
		assert(ra);		

		auto pxra = ra->px_actor_->isRigidActor();
		assert(pxra);
		
		pxra->detachShape(*px_shape_);
		
		//px_shape_->release();
		px_shape_ = NULL;
	}
}
void			neb::phx::core::shape::base::create_physics() {

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
shared_ptr<neb::phx::core::shape::util::parent>		neb::phx::core::shape::base::getPxParent() {
	
	auto parent = parent_.lock();
	assert(parent);
	
	auto pxparent(::std::dynamic_pointer_cast<neb::phx::core::shape::util::parent>(parent));
	
	if(!pxparent) {
		::std::cout << typeid(*parent).name() << ::std::endl;
		abort();
	}

	return pxparent;
}
physx::PxGeometry*	neb::phx::core::shape::base::to_geo() {
	return 0;
}







