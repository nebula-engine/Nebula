#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <nebula/define.hpp>

#include <nebula/content/base.hpp>
#include <nebula/content/scene/admin/base.hpp>

#include <nebula/content/universe/admin/base.hpp>

n31100::base::base( std::shared_ptr<n30000::base> parent ):
	parent_( parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
n31100::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void						n31100::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void						n31100::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	scenes_.foreach( std::bind( &nebula::content::scene::admin::base::shutdown, std::placeholders::_1 ) );
}
void						n31100::base::update()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	scenes_.foreach( std::bind( &nebula::content::scene::admin::base::update, std::placeholders::_1 ) );
}
std::shared_ptr<n22000::base>			n31100::base::request_window()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	return ( parent_.lock()->request_window() );
}
std::shared_ptr<n34200::material>		n31100::base::request_material_physics()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	return ( parent_.lock()->request_physics_material() );
}
std::shared_ptr<n34100::rigid_dynamic_box>	n31100::base::create_rigid_dynamic_box( std::shared_ptr<n32100::base> scene )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	return ( parent_.lock()->create_rigid_dynamic_box( scene ) );
}
std::shared_ptr<n34100::rigid_static_plane>	n31100::base::create_rigid_static_plane( std::shared_ptr<n32100::base> scene )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	return ( parent_.lock()->create_rigid_static_plane( scene ) );
}
std::shared_ptr<n34100::controller::base>	n31100::base::create_controller( std::shared_ptr<n32100::base> scene )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	return ( parent_.lock()->create_controller( scene ) );
}
std::shared_ptr<n35100::box>			n31100::base::create_box( std::shared_ptr<n34100::rigid_actor> actor )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	return ( parent_.lock()->create_box( actor ) );
}
std::shared_ptr<n35100::plane>			n31100::base::create_plane( std::shared_ptr<n34100::rigid_actor> actor )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	return ( parent_.lock()->create_plane( actor ) );
}










