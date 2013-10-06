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
jess::shared_ptr<npw::base>	ncua::base::request_window()
{
	return ( parent_.lock()->request_window() );
}
/*void	nebula::content::universe::admin::base::create_scene( jess::shared_ptr<nc_sc_a::base>& scn )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	scenes_.push<nc_sc_a::base>( scn, boost::bind( &nc_sc_a::base::init, _1, shared_from_this() ) );
}*/





