#include <framework/FR_App.h>

#include <content/Content.h>
#include <content/Physics/CO_PH_Physics.h>

#include <content/Actor/Physics/CO_AC_PH_RigidActor.h>

#include <content/Actor/Physics/PhysX/CO_AC_PH_PX_RigidActor.h>

#include <content/Shape/Admin/CO_SH_AD_Shape.h>
#include <content/Shape/Admin/CO_SH_AD_Box.h>









#include <content/Actor/Admin/CO_AC_AD_RigidActor.h>


		CO_AC_AD_RigidActor::RigidActor() {
}
		CO_AC_AD_RigidActor::~RigidActor() {
}
void	CO_AC_AD_RigidActor::VInit(Void* v) {
	PRINTSIG;
	CO_AC_AD_Actor::VInit( v );

	VCreateShape();
}
void	CO_AC_AD_RigidActor::VRender(Void* v) {
	//PRINTSIG;
	MapPtr<CO_SH_AD_Shape>::For( &CO_SH_AD_Shape::VRender, v );
}
void	CO_AC_AD_RigidActor::VCreateShape() {
	PRINTSIG;
	
}
void	CO_AC_AD_RigidActor::CreateBox( CO_SH_AD_Box*& box ) {
	MapPtr<CO_SH_AD_Shape>::Create(box);

	AR_Init i;
	i.co_ac_ad_rigidActor = this;

	box->VInit( &i );
}
void	CO_AC_AD_RigidActor::VShutdown(Void* v) {
	PRINTSIG;
	
}
void	CO_AC_AD_RigidActor::VUpdate(Void* v) {
	CO_AC_AD_Actor::VUpdate(v);
}
void	CO_AC_AD_RigidActor::VStep(Void* v) {
	PRINTSIG;
	
}


