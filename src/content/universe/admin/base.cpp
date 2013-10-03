#include <boost/bind.hpp>

#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <nebula/define.hpp>

#include <nebula/content/scene/admin/base.hpp>
#include <nebula/content/universe/admin/base.hpp>



nebula::content::universe::admin::base::base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
nebula::content::universe::admin::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	nebula::content::universe::admin::base::init(const boost::shared_ptr<nebula::content::base>& parent)
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	parent_ = parent;
}
void	nebula::content::universe::admin::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	scenes_.foreach( boost::bind(&nebula::content::scene::admin::base::shutdown,_1) );
}
void	nebula::content::universe::admin::base::update()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	scenes_.foreach(boost::bind(&nebula::content::scene::admin::base::update,_1));
}
void	nebula::content::universe::admin::base::create_scene( boost::shared_ptr<nc_sc_a::base>& scn )
{
	jess::clog.funcsig();
	
	scenes_.push<nc_sc_a::base>( scn, boost::bind( &nc_sc_a::base::init, _1, shared_from_this() ) );
}





