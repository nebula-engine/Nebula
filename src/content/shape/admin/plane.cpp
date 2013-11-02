#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/actor/admin/rigid_actor.hpp>
#include <nebula/content/shape/renderer/plane.hpp>
#include <nebula/content/shape/physics/plane.hpp>

#include <nebula/content/shape/admin/plane.hpp>

n35100::plane::plane( std::shared_ptr<n34100::rigid_actor> parent ):
	n35100::base( parent )
{
	
}
void	n35100::plane::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// init parent
	n35100::base::init();

	NEB_ASSERT( physics_ );
		
	// create physics
	//physics_.reset( new n35200::box );
	//physics_->init( shared_from_this() );
	
	// create renderer
	renderer_.reset( new n35300::plane( shared_from_this() ) );
	renderer_->init();
}
void	n35100::plane::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n35100::plane::render( std::shared_ptr<n23000::base> rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	n35100::base::render( rnd );
}



