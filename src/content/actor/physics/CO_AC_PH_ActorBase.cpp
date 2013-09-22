#include <nebula/content/actor/physics/base.hpp>

namespace nca = nebula::content::actor;



nca::physics::base::ActorBase()
{
}
nca::physics::base::~ActorBase()
{
}
void	nca::physics::base::init(const boost::shared_ptr<nebula::content::actor::admin::base>& parent)
{
	parent_ = parent;
}
void	nca::physics::base::shutdown()
{
	
}
void	nca::physics::base::update()
{
	
}
void	nca::physics::base::step()
{
	
}









