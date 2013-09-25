
#include <nebula/content/physics/base.hpp>
#include <nebula/content/universe/admin/base.hpp>




#include <nebula/content/base.hpp>

namespace nebula;


nebula::content::base::base()
{
	
}
nebula::content::base::~base()
{
	
}
void	nebula::content::base:register_universe(const boost::shared_ptr<nebula::content::universe::admin::base>& uni)
{
	
}
void	nebula::content::base::init(const boost::shared_ptr<nebula::framework:app>& parent)
{
	parent_ = parent;

	physics_.create(boost::bind(nebula::content::physics::base::init,_1,boost::shared_from_this()));

}
void	nebula::content::base::update()
{
	m_universe.For( &CO_UN_AD_Universe::VUpdate );
}

void	nebula::content::base::shutdown()
{
	m_universe.For( &CO_UN_AD_Universe::VShutDown );
	m_universe.Clear();
}





