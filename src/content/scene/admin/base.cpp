#include <boost/bind.hpp>

#include <jess/free.hpp>

#include <nebula/define.hpp>

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
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	accumulator_ = 0;
	step_size_ = 1.0f / 60.0f;
	time( &last_ );	
}
nc_sc_a::base::~base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
boost::shared_ptr<nebula::content::base>	nc_sc_a::base::get_content()
{
	boost::shared_ptr<nc::base> cont = parent_.lock()->parent_.lock();
	
	jess::assertion( bool( cont ) );
	
	return cont;
}
void						nc_sc_a::base::init( boost::shared_ptr<ncua::base>& parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	parent_ = parent;


	jess::cout << NEB_FUNCSIG << " test 1" << std::endl;

	// physics
#ifdef __PHYSX
	physics_.create<nc_sc_pp::base>( &nc_sc_pp::base::init, _1, shared_from_this() );
#else
	physics_.create<nc_sc_p::base>( boost::bind( &nc_sc_p::base::init, _1, shared_from_this() ) );
#endif
	jess::cout << NEB_FUNCSIG << " test 2" << std::endl;
	

	get_content()->register_scene( shared_from_this() );
}
void						nc_sc_a::base::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	actors_.foreach( boost::bind( &ncaa::base::shutdown, _1 ) );
	actors_.clear();
	
	views_.foreach( boost::bind( &ncva::base::shutdown, _1 ) );
	views_.clear();
}
/*void						nc_sc_a::base::create_view( boost::shared_ptr<ncva::base>& v )
{
	/// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	views_.push<ncva::base>( v, boost::bind( &ncva::base::init, _1, shared_from_this() ) );
}*/
void						nc_sc_a::base::update()
{
	jess::clog << NEB_FUNCSIG << std::endl;

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
	jess::clog << NEB_FUNCSIG << std::endl;
	
	actors_.foreach( boost::bind( &ncaa::base::step, _1, dt ) );
}
void						nc_sc_a::base::render( const boost::shared_ptr<npr::base>& rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	actors_.foreach( boost::bind( &ncaa::base::render, _1, rnd ) );
}
void						nc_sc_a::base::create_rigid_dynamic_box( boost::shared_ptr<ncaa::rigid_dynamic_box>& act )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	actors_.push<ncaa::rigid_dynamic_box>( act, boost::bind( &ncaa::rigid_dynamic_box::init, _1, shared_from_this() ) );
	
	jess::assertion( bool( act ) );	

	register_rigid_dynamic( act );
}
void						nc_sc_a::base::register_rigid_dynamic( boost::shared_ptr<ncaa::rigid_dynamic> act )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	// content physics
	boost::shared_ptr<ncp::base> cont_phys = get_content()->physics_.get();
		
	// register
	cont_phys->register_rigid_dynamic( act );
	
	
	
	// initialize the actor
	//co_ac_ad_rigidDynamic->init( shared_from_this() );
	
	
	// Add the actor to the CO_SC_PH_Scene object
	physics_->register_actor( act );
}
void						nc_sc_a::base::create_controller( boost::shared_ptr<ncaa::controller>& act )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	

	actors_.push<ncaa::controller>( act, boost::bind( &ncaa::controller::init, _1, shared_from_this() ) );
	
	// register controller with global physics object
	get_content()->physics_->register_controller( act );
}
void	nc_sc_a::base::request_window( jess::shared_ptr<npw::base>& wnd )
{
	parent_.lock()->request_window( wnd );
}







