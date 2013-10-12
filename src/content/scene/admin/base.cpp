#include <jess/free.hpp>

#include <nebula/define.hpp>

#include <nebula/framework/app.hpp>
#include <nebula/content/base.hpp>
#include <nebula/content/physics/base.hpp>
#include <nebula/content/universe/admin/base.hpp>
#include <nebula/content/scene/physics/base.hpp>
#include <nebula/content/scene/renderer/base.hpp>
#include <nebula/content/view/admin/human/base.hpp>
#include <nebula/content/actor/admin/rigid_dynamic_box.hpp>
#include <nebula/content/actor/physics/rigid_dynamic_box.hpp>
#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/actor/physics/controller.hpp>

#include <nebula/content/scene/admin/base.hpp>

n32100::base::base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	accumulator_ = 0;
	step_size_ = 1.0f / 60.0f;
	time( &last_ );	
}
n32100::base::~base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
jess::shared_ptr<nebula::content::base>	n32100::base::get_content()
{
	jess::assertion( !parent_.expired() );	
	jess::shared_ptr<n31100::base> uni = parent_.lock();
	
	jess::assertion( !uni->parent_.expired() );
	jess::shared_ptr<n30000::base> cont = uni->parent_.lock();
	
	
	jess::assertion( bool( cont ) );

	return cont;
}
void						n32100::base::init( jess::shared_ptr<n31100::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	parent_ = parent;



	// physics
	physics_.reset( new n32200::base );
	physics_->init( shared_from_this() );
	

	//get_content()->register_scene( shared_from_this() );
}
void						n32100::base::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	actors_.foreach( std::bind( &n34100::base::shutdown, std::placeholders::_1 ) );
	actors_.clear();

	views_.foreach( std::bind( &n33100::base::shutdown, std::placeholders::_1 ) );
	views_.clear();
}
void						n32100::base::update()
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

	actors_.foreach( std::bind( &n34100::base::update, std::placeholders::_1 ) );

	views_.foreach( std::bind( &n33100::base::update, std::placeholders::_1 ) );
}
void						n32100::base::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	actors_.foreach( std::bind( &n34100::base::step, std::placeholders::_1, dt ) );
}
void						n32100::base::render( jess::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	actors_.foreach( std::bind( &n34100::base::render, std::placeholders::_1, rnd ) );
}
jess::shared_ptr<n34100::rigid_dynamic_box>	n32100::base::create_rigid_dynamic_box()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// create
	jess::shared_ptr<n34100::rigid_dynamic_box> act = parent_.lock()->create_rigid_dynamic_box();

	/*( new n34100::rigid_dynamic_box() );
	
	act->physics_ = std::static_pointer_cast<n34200::base>( physics_->create_rigid_dynamic_box() );
	
	act->init( shared_from_this() );*/
	




	// store
	actors_.push<n34100::rigid_dynamic_box>( act );
	

	
	
	//jess::assertion( bool( act ) );	
	
	//register_rigid_dynamic( act );
	
	return act;
}
/*void						n32100::base::register_rigid_dynamic( jess::shared_ptr<n34100::rigid_dynamic> act )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// content physics
	jess::shared_ptr<n36000::base> cont_phys = get_content()->physics_.get();

	// register
	cont_phys->register_rigid_dynamic( act );



	// initialize the actor
	//co_ac_ad_rigidDynamic->init( shared_from_this() );


	// Add the actor to the CO_SC_PH_Scene object
	physics_->register_actor( act );
}*/
jess::shared_ptr<n34100::controller>		n32100::base::create_controller()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	jess::shared_ptr<n34100::controller> act = parent_.lock()->create_controller( shared_from_this() );

	// create
	/*jess::shared_ptr<n34100::controller> act( new n34100::controller );
	
	act->physics_ = std::static_pointer_cast<n34200::base>( physics_->create_controller() );
	
	act->init( shared_from_this() );*/

	// store
	actors_.push<n34100::controller>( act );
	
	return act;
}
/*jess::shared_ptr<n34200::rigid_dynamic_box>	n32100::base::create_physics_rigid_dynamic_box()
{
	
}
jess::shared_ptr<n34200::controller>		n32100::base::create_physics_controller()
{
	
}*/
jess::shared_ptr<n22000::base>	n32100::base::request_window()
{
	return ( parent_.lock()->request_window() );
}
jess::shared_ptr<n34200::material>	n32100::base::request_physics_material()
{
	return ( parent_.lock()->request_physics_material() );
}







