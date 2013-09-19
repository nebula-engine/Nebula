#include <content/Actor/Admin/CO_AC_AD_RigidActor.h>

#include <content/Shape/Admin/CO_SH_AD_Box.h>


#include <Platform/Renderer/PL_RE_Renderer.h>









#include <content/Shape/Renderer/CO_SH_RE_Box.h>

		CO_SH_RE_Box::Box() {
}
		CO_SH_RE_Box::~Box() {
}
void	CO_SH_RE_Box::VInit(Void* v) {
	AR_Init* i = DynCast<Void,AR_Init>(v);
	
	m_co_sh_ad_box = DynCast<CO_SH_AD_Shape,CO_SH_AD_Box>(i->co_sh_ad_shape);


}
void	CO_SH_RE_Box::VShutDown() {
	
}
void	CO_SH_RE_Box::VRender( Void* v ) {
	PL_RE_Renderer* renderer = DynCast<Void,AR_Render>( v )->renderer;
	
	if ( !renderer ) throw Except("renderer is null");

	if ( !m_co_sh_ad_box ) throw Except("m_co_sh_ad_box is null");
	if ( !m_co_sh_ad_box->Get_CO_AC_AD_RigidActor() ) throw Except("m_co_sh_ad_box->Get_CO_AC_AD_RigidActor() is null");
	
	// store transform
	Math::Transformf transform;

	// get transform from actor
	m_co_sh_ad_box->Get_CO_AC_AD_RigidActor()->GetTransform( transform );

	// construct matrix from transform

	Math::Mat44f matrix( transform );

	renderer->VPushMatrix();

	renderer->VMultMatrix( matrix );

	renderer->VScale( 
		m_co_sh_ad_box->Get_x(),
		m_co_sh_ad_box->Get_y(),
		m_co_sh_ad_box->Get_z() );

	renderer->VDrawCube();

	renderer->VPopMatrix();

}











