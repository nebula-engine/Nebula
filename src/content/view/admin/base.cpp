#include <nebula/content/view/admin/base.hpp>


ncva::base::base()
{
	
}
ncva::base::~base()
{

}
void	ncva::base::init( const boost::shared_ptr<nc_sc_a::base>& parent )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	parent_ = parent;
}
void	ncva::base::shutdown() {
	//jess::clog << NEB_FUNCSIG << std::endl;
}
void	ncva::base::update() {
}

