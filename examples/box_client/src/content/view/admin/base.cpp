#include <nebula/define.hpp>
#include <nebula/platform/window/base.hpp>
#include <nebula/content/scene/admin/base.hpp>
#include <nebula/content/camera.hpp>
#include <nebula/content/actor/admin/controller.hpp>

#include <box_client/content/scene/admin/base.hpp>
#include <box_client/ui/layout/base.hpp>

#include <box_client/content/view/admin/base.hpp>


void	bc33100::base::init( jess::shared_ptr<nc_sc_a::base> parent )
{
	//log
	jess::clog << NEB_FUNCSIG << std::endl;

	// get derived parent
	jess::shared_ptr<bc32100::base> bc_parent = std::dynamic_pointer_cast<bc32100::base>( parent );	

	// init parent
	ncva::base::init( parent );

	// request window
	window_ = parent->request_window();

	// ui
	layout_.reset( new bc51000::base );
	layout_->init();
	
	// camera
	camera_.reset( new n30000::camera );
	camera_->controller_ = bc_parent->ctrlr_;

	// set signal handlers
	window_->sig_pointer_motion_.connect
		(
		 std::bind
		 (
		  &ncaa::controller::handle_pointer_motion,
		  bc_parent->ctrlr_,
		  std::placeholders::_1,
		  std::placeholders::_2
		 )
		);

	window_->sig_key_down_.connect
		(
		 std::bind
		 (
		  &ncaa::controller::handle_key_down,
		  bc_parent->ctrlr_,
		  std::placeholders::_1,
		  std::placeholders::_2
		 )
		);
	window_->sig_key_up_.connect
		(
		 std::bind
		 (
		  &ncaa::controller::handle_key_up,
		  bc_parent->ctrlr_,
		  std::placeholders::_1,
		  std::placeholders::_2
		 )
		);

}


