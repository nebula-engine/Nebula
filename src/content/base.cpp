#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <nebula/define.hpp>
#include <nebula/framework/app.hpp>
#include <nebula/content/physics/base.hpp>
#include <nebula/content/universe/admin/base.hpp>

#include <nebula/content/actor/admin/rigid_dynamic_box.hpp>
#include <nebula/content/actor/physics/rigid_dynamic_box.hpp>

#include <nebula/content/actor/admin/rigid_static_plane.hpp>
#include <nebula/content/actor/physics/rigid_static_plane.hpp>

#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/actor/physics/controller.hpp>

#include <nebula/content/base.hpp>

nebula::content::base::base( jess::shared_ptr<nebula::framework::app> parent ):
	parent_(parent)
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
nebula::content::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	nebula::content::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	physics_.reset( new n36000::base( shared_from_this() ) );
	physics_->init();
}
void	nebula::content::base::update()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	universes_.foreach(std::bind(&n31100::base::update,std::placeholders::_1));
}
void	nebula::content::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	universes_.foreach( std::bind( &n31100::base::shutdown, std::placeholders::_1 ) );

	universes_.clear();
}
jess::shared_ptr<n22000::base>	n30000::base::request_window()
{
	return ( parent_.lock()->request_window() );
}

jess::shared_ptr<n34200::material>	n30000::base::request_physics_material()
{
	return ( physics_->request_physics_material() );
}
jess::shared_ptr<n34100::rigid_dynamic_box>	n30000::base::create_rigid_dynamic_box(
		jess::shared_ptr<n32100::base> scene
		)
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// create
	jess::shared_ptr<n34100::rigid_dynamic_box> actor( new n34100::rigid_dynamic_box( scene ) );

	// physics
	actor->physics_ = std::static_pointer_cast<n34200::base>( physics_->create_rigid_dynamic_box( scene, actor ) );

	return actor;
}
jess::shared_ptr<n34100::rigid_static_plane>	n30000::base::create_rigid_static_plane(
		jess::shared_ptr<n32100::base> scene
		)
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// create
	jess::shared_ptr<n34100::rigid_static_plane> actor( new n34100::rigid_static_plane( scene ) );

	// physics
	actor->physics_ = std::static_pointer_cast<n34200::base>( physics_->create_rigid_dynamic_box( scene, actor ) );

	return actor;
}
jess::shared_ptr<n34100::controller>		n30000::base::create_controller(
		jess::shared_ptr<n32100::base> scene
		)
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// create
	jess::shared_ptr<n34100::controller> actor( new n34100::controller( scene ) );

	// physics
	actor->physics_ = std::static_pointer_cast<n34200::base>( physics_->create_controller( scene, actor ) );

	return actor;
}



