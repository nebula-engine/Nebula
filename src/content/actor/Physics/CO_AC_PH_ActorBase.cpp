#include <content/Actor/Physics/CO_AC_PH_ActorBase.h>



		Content::Actor::Physics::ActorBase::ActorBase() {
}
		Content::Actor::Physics::ActorBase::~ActorBase() {
}


void	Content::Actor::Physics::ActorBase::VInit( Void* data ) {
	AR_Init* di = DynCast<Void,AR_Init>( data );
	m_app = di->app;
}
void	Content::Actor::Physics::ActorBase::VShutDown() {
	
}
void	Content::Actor::Physics::ActorBase::VUpdate() {
	
}
void	Content::Actor::Physics::ActorBase::VStep( Void* data ) {
	
}









