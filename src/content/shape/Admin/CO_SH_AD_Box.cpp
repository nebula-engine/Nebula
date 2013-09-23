#include <boost/bind.hpp>

#include <jess/except.hpp>

#include <nebula/content/actor/admin/rigid_actor.hpp>

#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/shape/renderer/box.hpp>
#include <nebula/content/shape/physics/box.hpp>
#include <nebula/content/shape/admin/box.hpp>

void	nebula::content::shape::admin::box::init(const boost::shared_ptr<nebula::content::actor::admin::rigid_actor>& parent)
{
	// call base
	nebula::content::shape::admin::base::init(parent);
	
	// create renderer
	renderer_.create<nebula::content::shape::renderer::box>(boost::bind(&nebula::content::shape::renderer::box::init,_1,shared_from_this()));
	
	// create physics
	physics_.create<nebula::content::shape::physics::box>(boost::bind(&nebula::content::shape::physics::box::init,_1,shared_from_this()));
	
	// default dimensions
	x_ = 1;
	y_ = 1;
	z_ = 1;
}
void	nebula::content::shape::admin::box::shutdown()
{
	
}
void	nebula::content::shape::admin::box::render(const boost::shared_ptr<nebula::platform::renderer::base>& rnd)
{
	if ( !renderer_ )
	{
		throw jess::except("renderer is null");
	}
	renderer_.pointer_->render(rnd);
}












