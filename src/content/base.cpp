#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <nebula/define.hpp>
#include <nebula/framework/app.hpp>
#include <nebula/content/physics/base.hpp>
#include <nebula/content/universe/admin/base.hpp>
#include <nebula/content/actor/admin/rigid_dynamic_box.hpp>
#include <nebula/content/actor/physics/rigid_dynamic_box.hpp>
#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/actor/physics/controller.hpp>

#include <nebula/content/base.hpp>

nebula::content::base::base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
nebula::content::base::~base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	nebula::content::base::init( jess::shared_ptr<nebula::framework::app> parent)
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	parent_ = parent;
	
	physics_.reset( new n36000::base() );
	physics_->init( shared_from_this() );
}
void	nebula::content::base::update()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	universes_.foreach(std::bind(&n31100::base::update,std::placeholders::_1));
}
void	nebula::content::base::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	universes_.foreach( std::bind( &n31100::base::shutdown, std::placeholders::_1 ) );
	
	universes_.clear();
}
jess::shared_ptr<n22000::base>	n30000::base::request_window()
{
	// request
	return ( parent_.lock()->request_window() );
}

jess::shared_ptr<n34200::material>	n30000::base::request_physics_material()
{
	return ( physics_->request_physics_material() );
}
jess::shared_ptr<n34100::rigid_dynamic_box>	n30000::base::create_rigid_dynamic_box()
{
	jess::shared_ptr<n34100::rigid_dynamic_box> act( new n34100::rigid_dynamic_box() );
	
	act->physics_ = std::static_pointer_cast<n34200::base>( physics_->create_rigid_dynamic_box() );
	
	return act;
}	
jess::shared_ptr<n34100::controller>		n30000::base::create_controller( jess::shared_ptr<n32100::base> scene )
{
	jess::shared_ptr<n34100::controller> act( new n34100::controller() );
	
	act->physics_ = std::static_pointer_cast<n34200::base>( physics_->create_controller( scene ) );
	
	return act;
}



