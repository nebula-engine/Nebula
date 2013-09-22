




#include <content/Actor/Physics/PhysX/CO_AC_PH_PX_Actor.h>


		Content::Actor::Physics::PhysX::Actor::Actor() {
}
		Content::Actor::Physics::PhysX::Actor::~Actor() {
}

void	Content::Actor::Physics::PhysX::Actor::VStep( Void* data ) {
	
}
void	Content::Actor::Physics::PhysX::Actor::SetActor( physx::PxActor* actor ) {
	m_pxActor = actor;
	
	m_pxActor->userData = this;
	
}







