#include <jess/free.hpp>

#include <nebula/content/actor/physics/physx/rigid_static.hpp>

#include <nebula/ns.hpp>

void	ncapp::rigid_static::init( boost::shared_ptr<ncaa::base>& parent )
{
	
	ncapp::rigid_actor::init( parent );
	
	jess::assertion( px_actor_ ); 
	
	//_pxrigid_static = (physx::Pxrigid_static*)m_pxactor;
	
	//VCreateShape();
}






