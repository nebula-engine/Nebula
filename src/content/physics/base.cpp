#include <nebula/content/physics/base.hpp>
#include <nebula/content/scene/admin/base.hpp>


ncp::base::base()
{

}
ncp::base::~base()
{

}
void	ncp::base::init( const boost::shared_ptr<nebula::content::base>& parent )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
}
void	ncp::base::shutdown()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncp::base::register_scene( const boost::shared_ptr<nc_sc_a::base>& scn )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncp::base::register_controller( const boost::shared_ptr<ncaa::controller>& act )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncp::base::register_rigid_dynamic( const boost::shared_ptr<ncaa::rigid_dynamic>& act )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncp::base::add_actor( boost::shared_ptr<ncaa::base> act )
{

}




