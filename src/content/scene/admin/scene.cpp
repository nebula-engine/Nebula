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
	
	
	get_content()->register_scene( shared_from_this() );
}
void						nc_sc_a::base::shutdown()
{
	actors_.foreach( boost::bind( &ncaa::base::shutdown, _1 ) );
	actors_.clear();
	
	views_.foreach( boost::bind( &ncva::base::shutdown, _1 ) );
	views_.clear();
}
void						nc_sc_a::base::create_view_human( boost::shared_ptr<ncvah::base>& v )
{
	views_.push<ncvah::base>( v, boost::bind( &ncvah::base::init, _1, shared_from_this() ) );
}
void						nc_sc_a::base::update()
{
	// time
	std::time_t now_;
	time( &now_ );
	// for debugging, will simply add stepSize to accumulator on every update
	//m_accumulator += difftime( now, m_last );
	accumulator_ += step_size_;
	last_ = now_;
	
	
	// Step
	while ( accumulator_ > step_size_ )
	{
		accumulator_ -= step_size_;
		
		step( step_size_ );
	}
	
	actors_.foreach( boost::bind( &ncaa::base::update, _1 ) );
	
	views_.foreach( boost::bind( &ncva::base::update, _1 ) );
}
void						nc_sc_a::base::step( FLOAT dt )
{
	//PRINTSIG;
	
	actors_.foreach( boost::bind( &ncaa::base::step, _1, dt ) );
}
void						nc_sc_a::base::render( const boost::shared_ptr<npr::base>& rnd )
{
	//PRINTSIG;
	
	actors_.foreach( boost::bind( &ncaa::base::render, _1, rnd ) );
}
void						nc_sc_a::base::create_rigid_dynamic_box( boost::shared_ptr<ncaa::rigid_dynamic_box>& act )
{
	//PRINTSIG;
	
	actors_.push<ncaa::rigid_dynamic_box>( act, boost::bind( &ncaa::rigid_dynamic_box::init, _1, shared_from_this() ) );
	
	//if ( !co_ac_ad_rigidDynamicBox ) throw Except("co_ac_ad_rigidDynamicBox is null");
	
	register_rigid_dynamic( act );
	
}
void						nc_sc_a::base::register_rigid_dynamic( boost::shared_ptr<ncaa::rigid_dynamic> act )
{
	//jess::assertion( m_co_sc_ph_scene );
	
	// content physics
	boost::shared_ptr<ncp::base> cont_phys = get_content()->physics_.pointer_;
	
	// register
	cont_phys->register_rigid_dynamic( act );
	
	
	
	// initialize the actor
	//co_ac_ad_rigidDynamic->init( shared_from_this() );
	
	
	// Add the actor to the CO_SC_PH_Scene object
	physics_.pointer_->add_actor( act );
}
void						nc_sc_a::base::create_controller( boost::shared_ptr<ncaa::controller>& act )
{
	// create controller object
	actors_.push<ncaa::controller>( act, boost::bind( &ncaa::controller::init, _1, shared_from_this() ) );
	
	// register controller with global physics object
	get_content()->physics_.pointer_->register_controller( act );
}








