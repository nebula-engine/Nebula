#include <nebula/define.hpp>

#include <nebula/content/shape/renderer/base.hpp>

ncsr::base::base()
{
}
ncsr::base::~base()
{
}
void	ncsr::base::init( jess::shared_ptr<ncs::admin::base> parent )
{
	parent_ = parent;
}
void	ncsr::base::shutdown()
{
	
}
void	ncsr::base::render( jess::shared_ptr<nebula::platform::renderer::base> rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	
}











