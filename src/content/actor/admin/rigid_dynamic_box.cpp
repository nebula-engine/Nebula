

#include <content/Shape/Admin/CO_SH_AD_Box.h>

#include <content/actor/Physics/CO_AC_PH_rigid_dynamicBox.h>
#include <content/actor/Physics/PhysX/CO_AC_PH_PX_rigid_dynamicBox.h>
#include <content/actor/Renderer/CO_AC_RE_rigid_dynamicBox.h>








#include <nebula/content/actor/admin/ncaa::rigid_dynamicBox.h>

		ncaa::rigid_dynamicBox::rigid_dynamicBox() {
	PRINTSIG;
	
	m_hx = 1;
	m_hy = 1;
	m_hz = 1;
}
		ncaa::rigid_dynamicBox::~rigid_dynamicBox() {
	PRINTSIG;
}
void	ncaa::rigid_dynamicBox::VInit( Void* v )
{
	PRINTSIG;
	ncaa::rigid_dynamic::VInit( v );

	// Physics
#ifdef __PHYSX
	CO_AC_PH_PX_rigid_dynamicBox* acPhPxrigid_dynamicBox = 0;

	acPhPxrigid_dynamicBox = new CO_AC_PH_PX_rigid_dynamicBox( m_app );

	acPhPxrigid_dynamicBox->CO_AC_PH_PX_rigid_dynamic::VInit( v );

	m_acPhrigid_dynamicBox = acPhPxrigid_dynamicBox;
#else
	Ptr<CO_AC_PH_rigid_dynamicBox>::Set_Or_Error(new CO_AC_PH_rigid_dynamicBox());
#endif
	
	Ptr<CO_AC_PH_rigid_dynamicBox>::Get()->CO_AC_PH_rigid_dynamicBox::VInit( v );
	
	Ptr<CO_AC_PH_base>::Set( Ptr<CO_AC_PH_rigid_dynamicBox>::Get() );
	
	

	// Renderer
	

	L__CO_AC_RE_rigid_dynamicBox::Set_Or_Error(new CO_AC_RE_rigid_dynamicBox());
	
	L__CO_AC_RE_rigid_dynamicBox::Get<CO_AC_RE_rigid_dynamicBox>()->VInit( v );

	
}
void	ncaa::rigid_dynamicBox::VShutdown(Void* v) {
	
}
void	ncaa::rigid_dynamicBox::VUpdate(Void* v) {
	ncaa::rigid_dynamic::VUpdate(v);
}
void	ncaa::rigid_dynamicBox::VRender( Void* v ) {
	//PRINTSIG;

	ncaa::rigid_actor::VRender( v );
}
void	ncaa::rigid_dynamicBox::VStep( Void* v ) {
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
void	ncaa::rigid_dynamicBox::VCreateShape() {
	PRINTSIG;

	CreateBox( m_box );

}























