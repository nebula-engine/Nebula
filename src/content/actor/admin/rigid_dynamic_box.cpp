

#include <content/Shape/Admin/CO_SH_AD_Box.h>

#include <content/actor/Physics/CO_AC_PH_RigidDynamicBox.h>
#include <content/actor/Physics/PhysX/CO_AC_PH_PX_RigidDynamicBox.h>
#include <content/actor/Renderer/CO_AC_RE_RigidDynamicBox.h>








#include <nebula/content/actor/admin/ncaa::RigidDynamicBox.h>

		ncaa::RigidDynamicBox::RigidDynamicBox() {
	PRINTSIG;
	
	m_hx = 1;
	m_hy = 1;
	m_hz = 1;
}
		ncaa::RigidDynamicBox::~RigidDynamicBox() {
	PRINTSIG;
}
void	ncaa::RigidDynamicBox::VInit( Void* v )
{
	PRINTSIG;
	ncaa::RigidDynamic::VInit( v );

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
	
	Ptr<CO_AC_PH_base>::Set( Ptr<CO_AC_PH_RigidDynamicBox>::Get() );
	
	

	// Renderer
	

	L__CO_AC_RE_RigidDynamicBox::Set_Or_Error(new CO_AC_RE_RigidDynamicBox());
	
	L__CO_AC_RE_RigidDynamicBox::Get<CO_AC_RE_RigidDynamicBox>()->VInit( v );

	
}
void	ncaa::RigidDynamicBox::VShutdown(Void* v) {
	
}
void	ncaa::RigidDynamicBox::VUpdate(Void* v) {
	ncaa::RigidDynamic::VUpdate(v);
}
void	ncaa::RigidDynamicBox::VRender( Void* v ) {
	//PRINTSIG;

	ncaa::rigid_actor::VRender( v );
}
void	ncaa::RigidDynamicBox::VStep( Void* v ) {
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
void	ncaa::RigidDynamicBox::VCreateShape() {
	PRINTSIG;

	CreateBox( m_box );

}























