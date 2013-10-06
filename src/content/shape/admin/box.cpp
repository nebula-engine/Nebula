#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/actor/admin/rigid_actor.hpp>
#include <nebula/content/shape/renderer/box.hpp>
#include <nebula/content/shape/physics/box.hpp>
#include <nebula/content/shape/admin/box.hpp>

void	ncsa::box::init( jess::shared_ptr<ncaa::rigid_actor> parent)
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	// call base
	ncsa::base::init( parent );
		
	// create physics
	#if defined(__PHYSX__)
		physics_.reset( new ncspp::box );
	#else
		physics_.reset( new ncsp::box );
	#endif
	
	physics_->init( shared_from_this() );
	
	// create renderer
	renderer_.reset( new ncsr::base );
	renderer_->init( shared_from_this() );
	
	// default dimensions
	x_ = 1;
	y_ = 1;
	z_ = 1;
}
void	ncsa::box::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	ncsa::box::render( jess::shared_ptr<npr::base>& rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	renderer_->render( rnd );
}












