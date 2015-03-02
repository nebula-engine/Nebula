#include <gal/log/log.hpp>

#include <neb/fnd/util/debug.hpp>

#include <neb/fnd/game/weapon/SimpleProjectile.hpp>

#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/base.hpp>
#include <neb/phx/core/scene/base.hpp>

neb::phx::core::actor::base::base()
{
	printv_func(DEBUG);
}
neb::phx::core::actor::base::~base()
{
	printv_func(DEBUG);
}
void			neb::phx::core::actor::base::init(parent_t * const & p)
{
	printv_func(DEBUG);
	
	create_physics();
	init_physics();
}
/*void			phx::core::actor::base::release() {
	
	neb::fnd::core::actor::base::release();
}*/
void			neb::phx::core::actor::base::step(gal::etc::timestep const & ts)
{
	neb::fnd::core::actor::base::step(ts);
}
/*std::shared_ptr<neb::phx::core::actor::util::parent>		neb::phx::core::actor::base::getPxParent() {
	auto parent(phx::core::actor::base::parent_.lock());
	assert(parent);
	return parent;
}*/
/*int			phx::core::actor::base::key_fun(std::shared_ptr<neb::gfx::window::base> window, int key, int scancode, int action, int mods) {
  switch(action) {
  case GLFW_PRESS:
  switch(key) {
  case GLFW_KEY_SPACE:
  fire();
  return 1;
  }
  }

  return 0;
  }*/





