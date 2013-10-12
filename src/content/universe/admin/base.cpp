#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <nebula/define.hpp>

#include <nebula/content/base.hpp>
#include <nebula/content/scene/admin/base.hpp>

#include <nebula/content/universe/admin/base.hpp>

nebula::content::universe::admin::base::base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
nebula::content::universe::admin::base::~base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	nebula::content::universe::admin::base::init( jess::shared_ptr<nebula::content::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	parent_ = parent;
}
void	nebula::content::universe::admin::base::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	scenes_.foreach( std::bind( &nebula::content::scene::admin::base::shutdown, std::placeholders::_1 ) );
}
void	nebula::content::universe::admin::base::update()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	scenes_.foreach( std::bind( &nebula::content::scene::admin::base::update, std::placeholders::_1 ) );
}
jess::shared_ptr<n22000::base>	n31100::base::request_window()
{
	return ( parent_.lock()->request_window() );
}
jess::shared_ptr<n34200::material>	n31100::base::request_physics_material()
{
	return ( parent_.lock()->request_physics_material() );
}
jess::shared_ptr<n34100::rigid_dynamic_box>	n31100::base::create_rigid_dynamic_box( jess::shared_ptr<n32100::base> scene )
{
	return ( parent_.lock()->create_rigid_dynamic_box( scene ) );
}
jess::shared_ptr<n34100::rigid_static_plane>	n31100::base::create_rigid_static_plane( jess::shared_ptr<n32100::base> scene )
{
	return ( parent_.lock()->create_rigid_static_plane( scene ) );
}
jess::shared_ptr<n34100::controller>		n31100::base::create_controller( jess::shared_ptr<n32100::base> scene )
{
	return ( parent_.lock()->create_controller( scene ) );
}

