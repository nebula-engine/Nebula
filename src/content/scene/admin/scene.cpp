#include <utilities/Types/Utilities.h>
#include <framework/FR_App.h>
#include <framework/FR_Mappable.h>

#include <content/Content.h>
#include <content/Physics/CO_PH_Physics.h>
#include <content/Scene/Physics/CO_SC_PH_Scene.h>
#include <content/Scene/Physics/PhysX/CO_SC_PH_PX_Scene.h>

#include <content/View/Admin/Human/CO_VI_AD_HU_View.h>

#include <content/Actor/Admin/CO_AC_AD_RigidDynamicBox.h>
#include <content/Actor/Admin/CO_AC_AD_Controller.h>














#include <content/Scene/Admin/CO_SC_AD_Scene.h>

		CO_SC_AD_Scene::Scene() {
	PRINTSIG;

	m_app = 0;
	m_co_sc_ph_scene = 0;
	m_accumulator = 0;
	m_stepSize = 1.0f / 60.0f;
	time(&m_last);

	
}
		CO_SC_AD_Scene::~Scene() {
}
void	CO_SC_AD_Scene::VInit( Void* data ) {
	PRINTSIG;

	m_app = DynCast<Void,AR_Init>( data )->app;
	

#ifdef __PHYSX
	m_physicsScene = new CO_SC_PH_PX_Scene();
#else
	m_co_sc_ph_scene = new CO_SC_PH_Scene();
#endif

	m_co_sc_ph_scene->VInit( data );


	m_app->GetContent()->GetPhysics()->RegisterScene( this );
}
void	CO_SC_AD_Scene::VShutDown() {
	PRINTSIG;
	m_actorBase.For( &CO_AC_AD_ActorBase::VShutdown, NULL );
	m_actorBase.Clear();

	m_view.For( &CO_VI_AD_View::VShutDown );
	m_view.Clear();
}
void	CO_SC_AD_Scene::CreateViewHuman( CO_VI_AD_HU_View*& viewHuman ) {
	PRINTSIG;

	m_view.Create(viewHuman);

	AR_Init i;
	i.app =		m_app;
	i.scene =	this;

	viewHuman->VInit( &i );
	
	
	
}
void	CO_SC_AD_Scene::VUpdate() {
	// time
	time_t now;
	time(&now);
	// for debugging, will simply add stepSize to accumulator on every update
	//m_accumulator += difftime( now, m_last );
	m_accumulator += m_stepSize;
	m_last = now;
	
	AR_Step s;
	s.dt = m_stepSize;

	// Step
	while ( m_accumulator > m_stepSize ) {
		m_accumulator -= m_stepSize;

		Step( &s );
	}

	m_actorBase.For( &CO_AC_AD_ActorBase::VUpdate, NULL );
	
	m_view.For( &CO_VI_AD_View::VUpdate );

}
void	CO_SC_AD_Scene::Step( Void* v ) {
	//PRINTSIG;
	
	m_actorBase.For( &CO_AC_AD_ActorBase::VStep, v );
}
void	CO_SC_AD_Scene::Render( Void* v ) {
	//PRINTSIG;

	m_actorBase.For( &CO_AC_AD_ActorBase::VRender, v );
}
void	CO_SC_AD_Scene::CreateRigidDynamicBox( CO_AC_AD_RigidDynamicBox*& co_ac_ad_rigidDynamicBox ) {
	PRINTSIG;
	
	m_actorBase.Create( co_ac_ad_rigidDynamicBox );

	if ( !co_ac_ad_rigidDynamicBox ) throw Except("co_ac_ad_rigidDynamicBox is null");

	RegisterRigidDynamic( co_ac_ad_rigidDynamicBox );
	
}
void	CO_SC_AD_Scene::RegisterRigidDynamic( CO_AC_AD_RigidDynamic* co_ac_ad_rigidDynamic ) {
	PRINTSIG;
	if ( !m_co_sc_ph_scene ) throw Except("m_co_sc_ph_scene is null");

	// get the CO_PH_Physics object
	CO_PH_Physics* co_ph_physics = m_app->GetContent()->GetPhysics();
	if (!co_ph_physics) throw Except("co_ph_physics is null");


	// register 
	co_ph_physics->RegisterRigidDynamic( co_ac_ad_rigidDynamic );
	

	
	// initialize the actor
	AR_Init i;
	i.app =		m_app;
	i.scene =	this;

	co_ac_ad_rigidDynamic->VInit(&i);


	// Add the actor to the CO_SC_PH_Scene object
	m_co_sc_ph_scene->AddActor( co_ac_ad_rigidDynamic );
}
void	CO_SC_AD_Scene::CreateController( CO_AC_AD_Controller*& controller ) {
	// create controller object
	m_actorBase.Create(controller);
	
	// register controller with global physics object
	m_app->GetContent()->GetPhysics()->RegisterController( controller, this );

	// init
	AR_Init i;
	i.app = m_app;

	controller->VInit(&i);
}


















