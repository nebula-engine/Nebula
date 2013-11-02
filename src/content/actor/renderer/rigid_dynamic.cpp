#include <nebula/content/actor/renderer/rigid_dynamic.hpp>

/** \todo 
* Where approporiate, make member fun30000tions of base classes (especially in actor namespace) pure virtual.
* Also, remove derived class member fun30000tions where not used
**/

n34300::rigid_dynamic::rigid_dynamic( std::shared_ptr<n34100::base> parent ):
n34300::base( parent ),
n34300::rigid_body( parent )
{

}
n34300::rigid_dynamic::~rigid_dynamic()
{

}
void	n34300::rigid_dynamic::init()
{
	n34300::rigid_body::init();
}
void	n34300::rigid_dynamic::shutdown()
{
	
}
void	n34300::rigid_dynamic::update()
{
	
}
void	n34300::rigid_dynamic::render( std::shared_ptr<n23000::base> rnd )
{
	
}
void	n34300::rigid_dynamic::step( float dt ){
	
}
void	n34300::rigid_dynamic::create_shapes()
{

}















