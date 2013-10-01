#include <nebula/content/actor/admin/rigid_dynamic.hpp>


		ncaa::rigid_dynamic::rigid_dynamic()
{
}
		ncaa::rigid_dynamic::~rigid_dynamic()
{
}
void	ncaa::rigid_dynamic::init( const boost::shared_ptr<nc_sc_a::base>& parent )
{
	//PRINTSIG;
	ncaa::rigid_body::init( parent );
}
void	ncaa::rigid_dynamic::shutdown()
{
	//PRINTSIG;
}
void	ncaa::rigid_dynamic::update()
{
	ncaa::rigid_body::update();
}
void	ncaa::rigid_dynamic::render( const boost::shared_ptr<npr::base>& rnd )
{
	//PRINTSIG;
	
}
void	ncaa::rigid_dynamic::step( FLOAT dt )
{
	//PRINTSIG;
	
}
void	ncaa::rigid_dynamic::create_shapes()
{
	//PRINTSIG;
	
}

















