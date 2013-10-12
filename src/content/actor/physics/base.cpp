#include <nebula/define.hpp>
#include <nebula/ns.hpp>

#include <nebula/content/actor/physics/base.hpp>

/// \todo completely separate "platform" from the rest of "nebula"

n34200::base::base( jess::shared_ptr<n34100::base> parent ):
	parent_( parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
n34200::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34200::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34200::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34200::base::update()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34200::base::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34200::base::render( jess::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34200::base::create_shapes()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}


