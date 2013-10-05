#include <nebula/define.hpp>
#include <nebula/platform/window/base.hpp>
#include <nebula/content/scene/admin/base.hpp>
#include <nebula/content/camera.hpp>
#include <nebula/content/actor/admin/controller.hpp>

#include <box_client/content/scene/admin/base.hpp>
#include <box_client/content/view/admin/base.hpp>

void	bc33100::base::init_bc( boost::shared_ptr<bc32100::base>& parent )
{
	//log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	// init parent
	boost::shared_ptr<nc_sc_a::base> neb_parent = boost::static_pointer_cast<nc_sc_a::base>( parent );	
	ncva::base::init( neb_parent );
	
	// request window
	parent->request_window( window_ );
	
	// camera
	create_camera();
	
	// connect controller to camera
	camera_->controller_ = parent->ctrlr_;
	
	// set signal handlers
	window_->sig_pointer_motion_.connect( boost::bind( &ncaa::controller::handle_pointer_motion, parent->ctrlr_, _1, _2 ) );
}
void	bc33100::base::init( boost::shared_ptr<nc_sc_a::base>& parent )
{
	//log
	jess::clog << NEB_FUNCSIG << std::endl;

	
}


