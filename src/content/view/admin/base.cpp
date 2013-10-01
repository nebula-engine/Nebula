#include <nebula/content/view/admin/base.hpp>


ncva::base::base()
{
	
}
ncva::base::~base()
{

}
void	ncva::base::init( const boost::shared_ptr<nc_sc_a::base>& parent )
{
	//PRINTSIG;
	parent_ = parent;
}
void	ncva::base::shutdown() {
	//PRINTSIG;
}
void	ncva::base::update() {
}

