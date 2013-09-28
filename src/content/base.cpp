#include <boost/bind.hpp>

#include <nebula/content/physics/base.hpp>
#include <nebula/content/universe/admin/base.hpp>




#include <nebula/content/base.hpp>

#include <nebula/ns.hpp>

nebula::content::base::base()
{
	
}
nebula::content::base::~base()
{
	
}
void	nebula::content::base::register_universe(const boost::shared_ptr<ncua::base>& uni)
{
	
}
void	nebula::content::base::init(const boost::shared_ptr<nebula::framework::app>& parent)
{
	parent_ = parent;

	physics_.create<ncp::base>(boost::bind(&ncp::base::init,_1,shared_from_this()));
	
}
void	nebula::content::base::update()
{
	universes_.foreach(boost::bind(&ncua::base::update,_1));
}
void	nebula::content::base::shutdown()
{
	universes_.foreach(boost::bind(&ncua::base::shutdown,_1));

	universes_.clear();
}





