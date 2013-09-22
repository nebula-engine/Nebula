#include <content/Content.h>
#include <content/Physics/CO_PH_Physics.h>

#include <content/Actor/Admin/CO_AC_AD_RigidActor.h>


#include <content/Shape/Admin/CO_SH_AD_Box.h>

#include <framework/FR_App.h>






#include <content/Actor/Renderer/CO_AC_RE_RigidActor.h>

		CO_AC_RE_RigidActor::RigidActor() {
}
		CO_AC_RE_RigidActor::~RigidActor() {
}

		
		
void	CO_AC_RE_RigidActor::VInit( Void* data ){
}
void	CO_AC_RE_RigidActor::VShutDown(){
}
void	CO_AC_RE_RigidActor::VUpdate(){
}
void	CO_AC_RE_RigidActor::VRender( Void* data ) {
	m_acAdRigidActor->MapPtr<CO_SH_AD_Shape>::For( &CO_SH_AD_Shape::VRender, data );
}
void	CO_AC_RE_RigidActor::VStep( Void* data ){
}


