#include <nebula/define.hpp>

#include <nebula/content/shape/renderer/base.hpp>

n35300::base::base( jess::shared_ptr<n35100::base> parent ):
	parent_( parent )
{
}
n35300::base::~base()
{
}
void	n35300::base::init()
{
}
void	n35300::base::shutdown()
{
	
}
void	n35300::base::render( jess::shared_ptr<n23000::base> rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	
}











