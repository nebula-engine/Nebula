#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <nebula/define.hpp>
#include <nebula/framework/app.hpp>
#include <nebula/content/physics/base.hpp>
#include <nebula/content/universe/admin/base.hpp>
#include <nebula/content/base.hpp>
#include <nebula/ns.hpp>

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
void	nebula::content::base::register_universe( jess::shared_ptr<ncua::base> uni )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	nebula::content::base::init( jess::shared_ptr<nebula::framework::app> parent)
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	parent_ = parent;
	
	physics_.reset( new ncp::base );
	physics_->init( shared_from_this() );
}
void	nebula::content::base::update()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	universes_.foreach(std::bind(&ncua::base::update,std::placeholders::_1));
}
void	nebula::content::base::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	universes_.foreach( std::bind( &ncua::base::shutdown, std::placeholders::_1 ) );
	
	universes_.clear();
}
jess::shared_ptr<npw::base>	nc::base::request_window()
{
	// request
	return ( parent_.lock()->request_window() );
}
void	nc::base::register_scene( jess::shared_ptr<nc_sc_a::base> )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}






