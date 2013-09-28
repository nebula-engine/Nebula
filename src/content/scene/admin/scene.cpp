#include <boost/bind.hpp>

#include <nebula/framework/app.hpp>

#include <nebula/content/base.hpp>
#include <nebula/content/physics/base.hpp>

#include <nebula/content/universe/admin/base.hpp>

#include <nebula/content/scene/physics/base.hpp>
#include <nebula/content/scene/physics/physx/base.hpp>

#include <nebula/content/view/admin/human/base.hpp>

#include <nebula/content/actor/admin/rigid_dynamic_box.hpp>
#include <nebula/content/actor/admin/controller.hpp>





#include <nebula/content/scene/admin/base.hpp>

nc_sc_a::base::base()
{

	accumulator_ = 0;
	step_size_ = 1.0f / 60.0f;
	time( &last_ );

	
}
nc_sc_a::base::~base()
{
}
boost::shared_ptr<nebula::content::base>	nc_sc_a::base::get_content()
{
	return parent_.lock()->parent_.lock();
}
void						nc_sc_a::base::init( const boost::shared_ptr<ncua::base>& parent )
{
	parent_ = parent;

	// physics
#ifdef __PHYSX
	physics_.create<nc_sc_pp::base>( &nc_sc_pp::base::init, _1, shared_from_this() );
#else
	physics_.create<nc_sc_p::base>( boost::bind( &nc_sc_p::base::init, _1, shared_from_this() ) );
#endif
	
	
	get_content()->RegisterScene( this );
}
void	nc_sc_a::base::shutdown()
{
	PRINTSIG;
	m_actorBase.For( &CO_AC_AD_ActorBase::VShutdown, NULL );
	m_actorBase.Clear();

	m_view.For( &CO_VI_AD_View::VShutDown );
	m_view.Clear();
}
void	nc_sc_a::base::CreateViewHuman( CO_VI_AD_HU_View*& viewHuman )
{
	PRINTSIG;

	m_view.Create(viewHuman);

	AR_Init i;
	i.app =		m_app;
	i.scene =	this;

	viewHuman->VInit( &i );
	
	
	
}
void	nc_sc_a::base::update()
{
	// time
	std::time_t now;
	time( &now );
	// for debugging, will simply add stepSize to accumulator on every update
	//m_accumulator += difftime( now, m_last );
	accumulator_ += step_size_;
	last_ = now_;
	
	
	dt = step_size_;

	// Step
	while ( accumulator_ > step_size_ )
	{
		accumulator_ -= step_size_;

		step( dt );
	}

	m_actorBase.For( &CO_AC_AD_ActorBase::update, NULL );
	
	m_view.For( &CO_VI_AD_View::update );

}
void	nc_sc_a::base::step(FLOAT dt)i
{
	//PRINTSIG;
	
	m_actorBase.For( &CO_AC_AD_ActorBase::VStep, v );
}
void	nc_sc_a::base::Render( Void* v )
{
	//PRINTSIG;

	m_actorBase.For( &CO_AC_AD_ActorBase::VRender, v );
}
void	nc_sc_a::base::CreateRigidDynamicBox( CO_AC_AD_RigidDynamicBox*& co_ac_ad_rigidDynamicBox )
{
	PRINTSIG;
	
	m_actorBase.Create( co_ac_ad_rigidDynamicBox );

	if ( !co_ac_ad_rigidDynamicBox ) throw Except("co_ac_ad_rigidDynamicBox is null");

	RegisterRigidDynamic( co_ac_ad_rigidDynamicBox );
	
}
void	nc_sc_a::base::RegisterRigidDynamic( const boost::shared_ptr<ncaa::rigid_dynamic>& act )
{
	jess::assertion( m_co_sc_ph_scene );
	
	// content physics
	boost::shared_ptr<ncp::base> cont_phys = get_content()->physics_.pointer_;
	
	// register
	cont_phys->RegisterRigidDynamic( co_ac_ad_rigidDynamic );
	
	
	
	// initialize the actor
	co_ac_ad_rigidDynamic->init( shared_from_this() );
	
	
	// Add the actor to the CO_SC_PH_Scene object
	m_co_sc_ph_scene->AddActor( co_ac_ad_rigidDynamic );
}
void	nc_sc_a::base::CreateController( CO_AC_AD_Controller*& controller )
{
	// create controller object
	m_actorBase.Create(controller);
	
	// register controller with global physics object
	m_app->GetContent()->GetPhysics()->RegisterController( controller, this );

	// init
	AR_Init i;
	i.app = m_app;

	controller->VInit(&i);
}


















