#include <boost/bind.hpp>

#include <jess/except.hpp>

#include <nebula/content/actor/admin/rigid_actor.hpp>

#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/shape/renderer/box.hpp>
#include <nebula/content/shape/physics/box.hpp>
#include <nebula/content/shape/admin/box.hpp>

#include <nebula/ns.hpp>

void	ncsa::box::init(const boost::shared_ptr<nebula::content::actor::admin::rigid_actor>& parent)
{
	// call base
	ncsa::base::init( parent );
	
	// create renderer
	//renderer_.create<ncsr::box>( boost::bind( &ncsr::box::init, _1, shared_from_this() ) );
	
	// create physics
	//physics_.create<ncsp::box>( boost::bind( &ncsp::box::init, _1, shared_from_this() ) );
	
	// default dimensions
	x_ = 1;
	y_ = 1;
	z_ = 1;
}
void	ncsa::box::shutdown()
{
	
}
void	ncsa::box::render(const boost::shared_ptr<npr::base>& rnd)
{
	if ( !renderer_ )
	{
		throw jess::except("renderer is null");
	}
	renderer_.pointer_->render(rnd);
}












