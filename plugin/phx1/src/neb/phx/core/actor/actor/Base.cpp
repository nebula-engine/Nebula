#include <gal/log/log.hpp>

#include <neb/fnd/core/scene/Base.hpp>
#include <neb/fnd/core/shape/base.hpp>
#include <neb/fnd/util/debug.hpp>

#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/actor/base.hpp>
#include <neb/phx/core/scene/base.hpp>

neb::phx::core::actor::actor::base::base():
	px_actor_(NULL)
{
	printv_func(DEBUG);
}
/*neb::phx::core::actor::actor::base::base(std::shared_ptr<neb::phx::core::actor::util::parent> parent):
	neb::fnd::core::actor::base(parent),
	neb::phx::core::actor::base(parent),
	px_actor_(NULL)
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
}*/
neb::phx::core::actor::actor::base::~base() {
	printv_func(DEBUG);

	assert(px_actor_ == NULL);
}
void		neb::phx::core::actor::actor::base::release() {
	printv_func(DEBUG);

	if(px_actor_ != NULL) {	
		px_actor_->release();
		px_actor_ = NULL;
	}
}

