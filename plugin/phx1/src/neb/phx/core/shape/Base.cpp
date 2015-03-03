#include <neb/fnd/util/cast.hpp>
#include <neb/fnd/util/debug.hpp>
#include <neb/fnd/core/shape/base.hpp>
#include <neb/fnd/core/light/base.hpp>

//#include <neb/gfx/glsl/attrib.hh>

#include <neb/phx/app/base.hpp>
#include <neb/phx/core/shape/base.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>


neb::phx::core::shape::base::base():
	px_shape_(NULL)
{
}
neb::phx::core::shape::base::~base()
{
	printv_func(DEBUG);
	assert(px_shape_ == NULL);
}
void			neb::phx::core::shape::base::step(gal::etc::timestep const & ts) {
	printv_func(DEBUG);
}
void			neb::phx::core::shape::base::init(parent_t * const & p)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	printv_func(DEBUG);
	abort();
}
void			neb::phx::core::shape::base::release()
{
	printf("%s\n", __PRETTY_FUNCTION__);
	//NEBULA_DEBUG_0_FUNCTION;
	printv_func(DEBUG);

	//neb::fnd::core::shape::base::release();
	
	if(px_shape_) {
		auto p = getParent();
		assert(p);

		auto fnd_actor = p->getParent()->is_fnd_actor_base();
		assert(fnd_actor);

		auto ra = dynamic_cast<neb::phx::core::actor::rigidactor::base*>(fnd_actor->P::get_object().get());
		assert(ra);		

		assert(ra->px_actor_);
		auto pxra = ra->px_actor_->isRigidActor();
		assert(pxra);
		
		pxra->detachShape(*px_shape_);
		
		//px_shape_->release();
		px_shape_ = NULL;
	}
}
void			neb::phx::core::shape::base::create_physics()
{
	printf("%s\n", __PRETTY_FUNCTION__);
	printv_func(DEBUG);
	//NEBULA_DEBUG_0_FUNCTION;

	if(!hasParent()) {
		printf("%s\n", __PRETTY_FUNCTION__);
		return;
	}
	
	auto fnd_shape = neb::could_be<parent_t, neb::fnd::core::shape::base>(getParent());
	assert(fnd_shape);
	
	auto fnd_actor = fnd_shape->getParent()->is_fnd_actor_base();
	assert(fnd_actor);

	auto actor = std::dynamic_pointer_cast<neb::phx::core::actor::base>(fnd_actor->P::get_object());
	assert(actor);
	if(!actor) return;

	auto rigidactor = actor->isPxActorRigidActorBase();//std::dynamic_pointer_cast<neb::fnd::actor::Rigid_Actor>(parent_.lock());
	assert(rigidactor);
	if(!rigidactor) return;

	physx::PxActor* const & px_actor = rigidactor->px_actor_;

	assert(px_actor);
	if(!px_actor) return;

	auto px_rigidactor = rigidactor->px_actor_->isRigidActor();

	assert(px_rigidactor);

	auto app = dynamic_cast<neb::phx::app::base*>(get_fnd_app());

	assert(app);

	physx::PxMaterial* px_mat = app->px_physics_->createMaterial(1,1,1);

	px_shape_ = px_rigidactor->createShape( *(to_geo()), *px_mat );
}
/*shared_ptr<neb::phx::core::shape::util::parent>		neb::phx::core::shape::base::getPxParent() {

  auto parent = getParent();

  auto pxparent(dynamic_cast<neb::phx::core::shape::util::parent*>(parent));

  if(!pxparent) {
  abort();
  }

  return pxparent;
  }*/
physx::PxGeometry*	neb::phx::core::shape::base::to_geo()
{
	printv_func(DEBUG);
	return 0;
}







