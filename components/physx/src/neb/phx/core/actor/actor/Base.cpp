#include <gal/log/log.hpp>

#include <neb/core/core/scene/base.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/util/debug.hpp>
#include <neb/core/util/typedef.hpp>

#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/actor/base.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/util/log.hpp>

neb::phx::core::actor::actor::base::base():
	px_actor_(NULL)
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
}
/*neb::phx::core::actor::actor::base::base(std::shared_ptr<neb::phx::core::actor::util::parent> parent):
	neb::core::core::actor::base(parent),
	neb::phx::core::actor::base(parent),
	px_actor_(NULL)
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
}*/
neb::phx::core::actor::actor::base::~base() {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;

	assert(px_actor_ == NULL);
}
void		neb::phx::core::actor::actor::base::release() {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;

	if(px_actor_ != NULL) {	
		px_actor_->release();
		px_actor_ = NULL;
	}
}

