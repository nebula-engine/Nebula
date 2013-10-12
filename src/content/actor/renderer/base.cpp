#include <nebula/define.hpp>

#include <nebula/content/actor/renderer/base.hpp>


n34300::base::base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
n34300::base::~base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
n34300::base::base( const n34300::base& act )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
n34300::base&	n34300::base::operator=( const n34300::base& act )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	return *this;
}
void	n34300::base::init( jess::shared_ptr<n34100::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	parent_ = parent;
}
void	n34300::base::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n34300::base::update()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n34300::base::render( jess::shared_ptr<n23000::base> rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n34300::base::step(float dt)
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n34300::base::create_shapes()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}











