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

#include <nebula/content/scene/admin/base.hpp>

n32100::base::base( jess::shared_ptr<n31100::base> parent ):
	parent_( parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	accumulator_ = 0;
	step_size_ = 1.0f / 60.0f;
	time( &last_ );	
}
n32100::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
jess::shared_ptr<n30000::base>	n32100::base::get_content()
{
	jess::assertion( !parent_.expired() );	
	jess::shared_ptr<n31100::base> uni = parent_.lock();

	jess::assertion( !uni->parent_.expired() );
	jess::shared_ptr<n30000::base> cont = uni->parent_.lock();


	jess::assertion( bool( cont ) );

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
	jess::shared_ptr<n34100::rigid_dynamic_box> act = parent_.lock()->create_rigid_dynamic_box( shared_from_this() );

	// store
	actors_.push<n34100::rigid_dynamic_box>( act );

	return act;
}
jess::shared_ptr<n34100::rigid_static_plane>	n32100::base::create_rigid_static_plane()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// create
	jess::shared_ptr<n34100::rigid_static_plane> act = parent_.lock()->create_rigid_static_plane( shared_from_this() );

	// store
	actors_.push<n34100::rigid_static_plane>( act );

	return act;
}
jess::shared_ptr<n34100::controller::base>	n32100::base::create_controller()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// create
	jess::shared_ptr<n34100::controller::base> act = parent_.lock()->create_controller( shared_from_this() );

	// store
	actors_.push<n34100::controller::base>( act );
	
	return act;
}
jess::shared_ptr<n22000::base>			n32100::base::request_window()
{
	return ( parent_.lock()->request_window() );
}
jess::shared_ptr<n34200::material>		n32100::base::request_physics_material()
{
	return ( parent_.lock()->request_physics_material() );
}
jess::shared_ptr<n35100::box>			n32100::base::create_box()
{
	return parent_.lock()->create_box();
}
jess::shared_ptr<n35100::plane>			n32100::base::create_plane()
{
	return parent_.lock()->create_plane();
}








