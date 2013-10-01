
#include <boost/bind.hpp>

#include <nebula/content/scene/admin/base.hpp>
#include <nebula/content/universe/admin/base.hpp>



nebula::content::universe::admin::base::base()
{

}
nebula::content::universe::admin::base::~base()
{

}
void	nebula::content::universe::admin::base::init(const boost::shared_ptr<nebula::content::base>& parent)
{
	parent_ = parent;
}
void	nebula::content::universe::admin::base::shutdown()
{
	scenes_.foreach(boost::bind(&nebula::content::scene::admin::base::shutdown,_1));
}
void	nebula::content::universe::admin::base::update()
{
	scenes_.foreach(boost::bind(&nebula::content::scene::admin::base::update,_1));
}
/*
void	nebula::content::universe::admin::base::regCreateScene(boost::shared_ptr<nebula::content::scene::admin::base>& scene )
{
	jess::clog.funcsig();
	
	scenes_.create(scene);
	
	AR_Init i;
	i.app = m_app;
	
	scene->init( &i );
}
*/




