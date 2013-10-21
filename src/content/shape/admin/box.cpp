#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/actor/admin/rigid_actor.hpp>
#include <nebula/content/shape/renderer/box.hpp>
#include <nebula/content/shape/physics/box.hpp>

#include <nebula/content/shape/admin/box.hpp>

void	n35100::box::box( jess::shared_ptr<n34100::rigid_actor> parent ):
	n35100::base( parent )
{
	
}
void	n35100::box::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// call base
	n35100::base::init();
	
	NEB_ASSERT( bool( physics_ ) )
	
	// create physics
	//physics_.reset( new n35200::box );
	//physics_->init( shared_from_this() );
	
	// create renderer
	renderer_.reset( new n35300::box( shared_from_this() ) );
	renderer_->init();
	
}
void	n35100::box::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n35100::box::render( jess::shared_ptr<n23000::base> rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	n35100::base::render( rnd );
}



