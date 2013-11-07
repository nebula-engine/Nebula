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

#include <nebula/content/shape/admin/box.hpp>
#include <nebula/content/shape/physics/box.hpp>
#include <nebula/content/shape/admin/plane.hpp>
#include <nebula/content/shape/physics/plane.hpp>


#include <nebula/content/base.hpp>

nebula::content::base::base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
nebula::content::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
/*void	nebula::content::base::init()
{
	NEB_LOG_FUNCSIG;
	
	/// \todo implement with ker
	//physics_.reset( new n36000::base( shared_from_this() ) );
	//physics_->init();
}*/
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
/*std::shared_ptr<n22000::base>	n30000::base::request_window()
{
	return ( parent_.lock()->request_window() );
}*/
/*std::shared_ptr<n34200::material>	n30000::base::request_physics_material()
{
	return ( physics_->request_physics_material() );
}*/
/*std::shared_ptr<n34100::rigid_dynamic_box>	n30000::base::create_rigid_dynamic_box(
		std::shared_ptr<ker::module::module> scene
		)
{
	NEB_LOG_FUNC;
	
	// create
	//std::shared_ptr<n34100::rigid_dynamic_box> actor( new n34100::rigid_dynamic_box( scene ) );
	
	// physics
	actor->physics_ = std::static_pointer_cast<n34200::base>( physics_->create_rigid_dynamic_box( scene, actor ) );
	
	// init
	actor->init();
	
	return actor;
}*/
/*std::shared_ptr<n34100::rigid_static_plane>	n30000::base::create_rigid_static_plane(
		std::shared_ptr<ker::module::module> scene
		)
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// create
	std::shared_ptr<n34100::rigid_static_plane> actor( new n34100::rigid_static_plane( scene ) );

	// physics
	actor->physics_ = std::static_pointer_cast<n34200::base>( physics_->create_rigid_dynamic_box( scene, actor ) );

	// init
	actor->init();

	return actor;
}*/
/*std::shared_ptr<n34100::controller::base>	n30000::base::create_controller(
		std::shared_ptr<ker::module::module> scene
		)
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	// create
	std::shared_ptr<n34100::controller::base> actor( new n34100::controller::base( scene ) );
	
	// physics
	actor->physics_ = std::static_pointer_cast<n34200::base>( physics_->create_controller( scene, actor ) );
	
	// init
	actor->init();
	
	return actor;
}*/
/**std::shared_ptr<n35100::box>			n30000::base::create_box( std::shared_ptr<n34100::rigid_actor> actor )
{
	// create
	std::shared_ptr<n35100::box> box( new n35100::box( actor ) );
	
	box->physics_ = physics_->create_box( box );
	
	box->init();
	
	return box;
}*/
/*std::shared_ptr<n35100::plane>			n30000::base::create_plane( std::shared_ptr<n34100::rigid_actor> actor )
{
	// create
	std::shared_ptr<n35100::plane> plane( new n35100::plane( actor ) );
	
	plane->physics_ = physics_->create_plane( plane );
	
	plane->init();
	
	return plane;
}*/





