#include <jess/free.hpp>

#include <nebula/define.hpp>

#include <nebula/framework/app.hpp>
#include <nebula/content/base.hpp>
#include <nebula/content/physics/base.hpp>
#include <nebula/content/universe/admin/base.hpp>
#include <nebula/content/scene/physics/base.hpp>
#include <nebula/content/scene/physics/physx/base.hpp>
#include <nebula/content/scene/renderer/base.hpp>
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
jess::shared_ptr<nebula::content::base>	nc_sc_a::base::get_content()
{
	jess::assertion( !parent_.expired() );	
	jess::shared_ptr<ncua::base> uni = parent_.lock();
	
	jess::assertion( !uni->parent_.expired() );
	jess::shared_ptr<nc::base> cont = uni->parent_.lock();
	
	
	jess::assertion( bool( cont ) );

	return cont;
}
void						nc_sc_a::base::init( jess::shared_ptr<ncua::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	parent_ = parent;


	jess::cout << NEB_FUNCSIG << " test 1" << std::endl;

	// physics
#ifdef __PHYSX
	physics_.reset( new nc_sc_pp::base );
#else
	physics_.reset( new nc_sc_p::base );
#endif
	physics_->init( shared_from_this() );



	jess::cout << NEB_FUNCSIG << " test 2" << std::endl;


	get_content()->register_scene( shared_from_this() );
}
void						nc_sc_a::base::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	actors_.foreach( std::bind( &ncaa::base::shutdown, std::placeholders::_1 ) );
	actors_.clear();

	views_.foreach( std::bind( &ncva::base::shutdown, std::placeholders::_1 ) );
	views_.clear();
}
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

	actors_.foreach( std::bind( &ncaa::base::update, std::placeholders::_1 ) );

	views_.foreach( std::bind( &ncva::base::update, std::placeholders::_1 ) );
}
void						nc_sc_a::base::step( FLOAT dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	actors_.foreach( std::bind( &ncaa::base::step, std::placeholders::_1, dt ) );
}
void						nc_sc_a::base::render( jess::shared_ptr<npr::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	actors_.foreach( std::bind( &ncaa::base::render, std::placeholders::_1, rnd ) );
}
jess::shared_ptr<ncaa::rigid_dynamic_box>	nc_sc_a::base::create_rigid_dynamic_box()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	// create
	jess::shared_ptr<ncaa::rigid_dynamic_box> act( new ncaa::rigid_dynamic_box );

	actors_.push<ncaa::rigid_dynamic_box>( act );

	act->init( shared_from_this() );

	//jess::assertion( bool( act ) );	

	register_rigid_dynamic( act );

	return act;
}
void						nc_sc_a::base::register_rigid_dynamic( jess::shared_ptr<ncaa::rigid_dynamic> act )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	// content physics
	jess::shared_ptr<ncp::base> cont_phys = get_content()->physics_.get();

	// register
	cont_phys->register_rigid_dynamic( act );



	// initialize the actor
	//co_ac_ad_rigidDynamic->init( shared_from_this() );


	// Add the actor to the CO_SC_PH_Scene object
	physics_->register_actor( act );
}
jess::shared_ptr<ncaa::controller>		nc_sc_a::base::create_controller()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	jess::shared_ptr<ncaa::controller> act( new ncaa::controller );

	//actors_.push<ncaa::controller>( act, std::bind( &ncaa::controller::init, std::placeholders::_1, shared_from_this() ) );

	actors_.push<ncaa::controller>( act );

	//act.reset( new ncaa::controller );

	//jess::cout << "act.use_count()=" << act.use_count() << std::endl;

	//jess::shared_ptr<ncaa::actor> test_act( new ncaa::actor );
	//test_act->init( shared_from_this() );

	//jess::shared_ptr<ncaa::controller> test_act2( new ncaa::controller );
	//test_act2->init( shared_from_this() );

	act->init( shared_from_this() );

	// register controller with global physics object
	jess::shared_ptr<nc::base> cont = get_content();

	jess::shared_ptr<ncp::base> cont_phys = cont->physics_;
	jess::assertion( bool( cont_phys ) );
	jess::assertion( !cont_phys->parent_.expired() );
	
	//ncp::base test = *cont_phys;
	//ncaa::controller text_act = *act;

	cont_phys->register_controller( act );

	return act;
}
jess::shared_ptr<npw::base>	nc_sc_a::base::request_window()
{
	return ( parent_.lock()->request_window() );
}







