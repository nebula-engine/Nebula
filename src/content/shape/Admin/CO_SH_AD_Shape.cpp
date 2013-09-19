#include <jess/print/print.hpp>

#include <nebula/content/shape/admin/base.hpp>




nebula::content::shape::admin::base::base()
{
}
nebula::content::shape::admin::base::~base()
{
}
void	nebula::content::shape::admin::base::init(const boost::shared_ptr<nebula::content::actor::admin::rigid_actor>& parent)
{
	jess::clog.funcsig();
	
	parent_ = parent;
}
void	nebula::content::shape::admin::base::shutdown()
{
	
}
void	nebula::content::shape::admin::base::render(const boost::shared_ptr<nebula::platform::renderer::base>&)
{
	
}











