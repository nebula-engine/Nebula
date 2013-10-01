#include <nebula/content/actor/admin/rigid_body.hpp>



		ncaa::rigid_body::rigid_body() {
}
		ncaa::rigid_body::~rigid_body() {
}


void	ncaa::rigid_body::init( const boost::shared_ptr<nc_sc_a::base>& parent )
{
	//PRINTSIG;
	ncaa::rigid_actor::init( parent );

	
}
void	ncaa::rigid_body::shutdown() {
	//PRINTSIG;
	
}
void	ncaa::rigid_body::update() {
	ncaa::rigid_actor::update();
}
void	ncaa::rigid_body::render(const boost::shared_ptr<npr::base>&) {
	//PRINTSIG;
	
}
void	ncaa::rigid_body::step(FLOAT) {
	//PRINTSIG;
	
}
void	ncaa::rigid_body::create_shapes()
{
}



