#include <nebula/define.hpp>

#include <nebula/content/actor/renderer/base.hpp>


ncar::base::base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
ncar::base::~base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
ncar::base::base( const ncar::base& act )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
ncar::base&	ncar::base::operator=( const ncar::base& act )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	return *this;
}
void	ncar::base::init(const jess::shared_ptr<ncaa::base>& parent)
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	parent_ = parent;
}
void	ncar::base::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	ncar::base::update()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	ncar::base::render(const jess::shared_ptr<npr::base>& rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	ncar::base::step(FLOAT dt)
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	ncar::base::create_shapes()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}











