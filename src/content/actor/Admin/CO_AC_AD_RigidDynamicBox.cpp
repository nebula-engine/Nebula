

#include <content/Shape/Admin/CO_SH_AD_Box.h>

#include <content/Actor/Physics/CO_AC_PH_RigidDynamicBox.h>
#include <content/Actor/Physics/PhysX/CO_AC_PH_PX_RigidDynamicBox.h>
#include <content/Actor/Renderer/CO_AC_RE_RigidDynamicBox.h>








#include <content/Actor/Admin/CO_AC_AD_RigidDynamicBox.h>

		CO_AC_AD_RigidDynamicBox::RigidDynamicBox() {
	PRINTSIG;
	
	m_hx = 1;
	m_hy = 1;
	m_hz = 1;
}
		CO_AC_AD_RigidDynamicBox::~RigidDynamicBox() {
	PRINTSIG;
}
void	CO_AC_AD_RigidDynamicBox::VInit( Void* v )
{
	PRINTSIG;
	CO_AC_AD_RigidDynamic::VInit( v );

	// Physics
#ifdef __PHYSX
	CO_AC_PH_PX_RigidDynamicBox* acPhPxRigidDynamicBox = 0;

	acPhPxRigidDynamicBox = new CO_AC_PH_PX_RigidDynamicBox( m_app );

	acPhPxRigidDynamicBox->CO_AC_PH_PX_RigidDynamic::VInit( v );

	m_acPhRigidDynamicBox = acPhPxRigidDynamicBox;
#else
	Ptr<CO_AC_PH_RigidDynamicBox>::Set_Or_Error(new CO_AC_PH_RigidDynamicBox());
#endif
	
	Ptr<CO_AC_PH_RigidDynamicBox>::Get()->CO_AC_PH_RigidDynamicBox::VInit( v );
	
	Ptr<CO_AC_PH_ActorBase>::Set( Ptr<CO_AC_PH_RigidDynamicBox>::Get() );
	
	

	// Renderer
	

	L__CO_AC_RE_RigidDynamicBox::Set_Or_Error(new CO_AC_RE_RigidDynamicBox());
	
	L__CO_AC_RE_RigidDynamicBox::Get<CO_AC_RE_RigidDynamicBox>()->VInit( v );

	
}
void	CO_AC_AD_RigidDynamicBox::VShutdown(Void* v) {
	
}
void	CO_AC_AD_RigidDynamicBox::VUpdate(Void* v) {
	CO_AC_AD_RigidDynamic::VUpdate(v);
}
void	CO_AC_AD_RigidDynamicBox::VRender( Void* v ) {
	//PRINTSIG;

	CO_AC_AD_RigidActor::VRender( v );
}
void	CO_AC_AD_RigidDynamicBox::VStep( Void* v ) {
	//PRINTSIG;
	/*
	AR_Step* s = DynCast<Void,AR_Step>( v );
	
	if ( m_transform.p.y > 0.5 ) {
		m_transform.p.x += -2 * s->dt;
	} else {
		m_transform.p.x += 2 * s->dt;
	}

	if ( m_transform.p.x > 3 ) {
		m_transform.p.y = 1;
	} else if ( m_transform.p.x < -3 ) {
		m_transform.p.y = 0;
	}
	*/
}
void	CO_AC_AD_RigidDynamicBox::VCreateShape() {
	PRINTSIG;

	CreateBox( m_box );

}























