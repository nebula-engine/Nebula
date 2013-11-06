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

#include <nebula/content/actor/admin/rigid_static_plane.hpp>
#include <nebula/content/actor/physics/rigid_static_plane.hpp>

#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/actor/physics/controller.hpp>

#include <nebula/content/actor/control/controller/base.hpp>

#include <nebula/content/scene/admin/base.hpp>

n32100::base::base()
{
	NEB_LOG_FUNC;

	accumulator_ = 0;
	step_size_ = 1.0f / 60.0f;
	time( &last_ );	
}
n32100::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
std::shared_ptr<n30000::base>	n32100::base::get_content()
{
	NEB_ASSERT( !parent_.expired() );	
	std::shared_ptr<n31100::base> uni = parent_.lock();

	NEB_ASSERT( !uni->parent_.expired() );
	std::shared_ptr<n30000::base> cont = uni->parent_.lock();
	
	
	NEB_ASSERT( cont );

	return cont;
}
void						n32100::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;
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
void						n32100::base::connect_controller_to_view( std::shared_ptr<n34100::controller::base> controller, std::shared_ptr<n33100::base> view )
{
	NEB_ASSERT( bool( controller ) );
	NEB_ASSERT( bool( controller->control_ ) );
	NEB_ASSERT( bool( view ) );
	NEB_ASSERT( bool( view->window_ ) );

	controller->control_->connect_to_window( view->window_ );
}

void						n32100::base::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	NEB_ASSERT( physics_ );
	
	actors_.foreach( std::bind( &n34100::base::step, std::placeholders::_1, dt ) );
	
	// physics
	physics_->step(dt);
}
void						n32100::base::render( std::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	actors_.foreach( std::bind( &n34100::base::render, std::placeholders::_1, rnd ) );
}
std::shared_ptr<n34100::rigid_dynamic_box>	n32100::base::create_rigid_dynamic_box()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	// create
	std::shared_ptr<n34100::rigid_dynamic_box> act = parent_.lock()->create_rigid_dynamic_box( shared_from_this() );
	
	// add
	physics_->add( act );
	
	// store
	actors_.push<n34100::rigid_dynamic_box>( act );

	return act;
}
std::shared_ptr<n34100::rigid_static_plane>	n32100::base::create_rigid_static_plane()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// create
	std::shared_ptr<n34100::rigid_static_plane> act = parent_.lock()->create_rigid_static_plane( shared_from_this() );

	// add
	physics_->add( act );

	// store
	actors_.push<n34100::rigid_static_plane>( act );

	return act;
}
std::shared_ptr<n34100::controller::base>	n32100::base::create_controller()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// create
	std::shared_ptr<n34100::controller::base> act = parent_.lock()->create_controller( shared_from_this() );

	// store
	actors_.push<n34100::controller::base>( act );
	
	return act;
}
std::shared_ptr<n22000::base>			n32100::base::request_window()
{
	return ( parent_.lock()->request_window() );
}
std::shared_ptr<n34200::material>		n32100::base::request_material_physics()
{
	return ( parent_.lock()->request_material_physics() );
}
std::shared_ptr<n35100::box>			n32100::base::create_box( std::shared_ptr<n34100::rigid_actor> actor )
{
	return parent_.lock()->create_box( actor );
}
std::shared_ptr<n35100::plane>			n32100::base::create_plane( std::shared_ptr<n34100::rigid_actor> actor )
{
	return parent_.lock()->create_plane( actor );
}



