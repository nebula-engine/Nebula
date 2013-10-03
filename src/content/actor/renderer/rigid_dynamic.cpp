#include <nebula/content/actor/renderer/rigid_dynamic.hpp>

/** \todo 
* Where approporiate, make member functions of base classes (especially in actor namespace) pure virtual.
* Also, remove derived class member functions where not used
**/

ncar::rigid_dynamic::rigid_dynamic()
{
}
ncar::rigid_dynamic::~rigid_dynamic()
{
}
ncar::rigid_dynamic::rigid_dynamic( const ncar::rigid_dynamic& act )
{
}
ncar::rigid_dynamic&	ncar::rigid_dynamic::operator=( const ncar::rigid_dynamic& act )
{
	return *this;
}




void	ncar::rigid_dynamic::init( const boost::shared_ptr<ncaa::base>& parent )
{
	ncar::rigid_body::init( parent );
}
void	ncar::rigid_dynamic::shutdown()
{
	
}
void	ncar::rigid_dynamic::update(){
	
}
void	ncar::rigid_dynamic::render( const boost::shared_ptr<npr::base>& rnd ) {
	
}
void	ncar::rigid_dynamic::step( FLOAT dt ){
	
}
void	ncar::rigid_dynamic::create_shapes()
{

}















