#include <nebula/content/actor/renderer/base.hpp>


ncar::base::base()
{
	
}
ncar::base::~base()
{

}
ncar::base::base( const ncar::base& act )
{
	
}
ncar::base&	ncar::base::operator=( const ncar::base& act )
{
	return *this;
}
void	ncar::base::init(const jess::shared_ptr<ncaa::base>& parent)
{
	parent_ = parent;
}
void	ncar::base::shutdown()
{
	
}
void	ncar::base::update()
{
	
}
void	ncar::base::render(const jess::shared_ptr<npr::base>& rnd )
{
	
}
void	ncar::base::step(FLOAT dt)
{
	
}
void	ncar::base::create_shapes()
{
	
}











