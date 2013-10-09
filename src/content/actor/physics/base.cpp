#include <nebula/define.hpp>
#include <nebula/content/actor/physics/base.hpp>

/// \todo completely separate "platform" from the rest of "nebula"


nca::physics::base::base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
nca::physics::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
nca::physics::base::base( const ncap::base& act )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
nca::physics::base&	ncap::base::operator=( const ncap::base& act )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	return *this;
}
void	nca::physics::base::init( jess::shared_ptr<nebula::content::actor::admin::base> parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	parent_ = parent;
}
void	nca::physics::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	nca::physics::base::update()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	nca::physics::base::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	ncap::base::render( jess::shared_ptr<npr::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	ncap::base::create_shapes()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}





