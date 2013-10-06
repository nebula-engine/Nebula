#include <nebula/content/actor/renderer/rigid_body.hpp>



ncar::rigid_body::rigid_body() {
}
ncar::rigid_body::~rigid_body() {
}



void	ncar::rigid_body::init( const jess::shared_ptr<ncaa::base>& parent )
{
	ncar::rigid_actor::init( parent );
}
void	ncar::rigid_body::shutdown(){
}
void	ncar::rigid_body::update(){
}
void	ncar::rigid_body::render( const jess::shared_ptr<npr::base>& rnd ) {
}
void	ncar::rigid_body::step( FLOAT dt ){
}










