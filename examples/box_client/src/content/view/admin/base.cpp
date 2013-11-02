#include <nebula/define.hpp>
#include <nebula/platform/window/base.hpp>
#include <nebula/content/scene/admin/base.hpp>
#include <nebula/content/camera.hpp>
#include <nebula/content/actor/admin/controller.hpp>

#include <box_client/content/scene/admin/base.hpp>
#include <box_client/ui/layout/base.hpp>

#include <box_client/content/view/admin/base.hpp>


void	bc33100::base::init( std::shared_ptr<n32100::base> parent )
{
	//log
	jess::clog << NEB_FUNCSIG << std::endl;

	// get derived parent
	std::shared_ptr<bc32100::base> bc_parent = std::dynamic_pointer_cast<bc32100::base>( parent );	

	// init parent
	n33100::base::init( parent );

	// request window
	window_ = parent->request_window();

	// ui
	layout_.reset( new bc51000::base );
	layout_->init();
	
	// camera
	camera_.reset( new n30000::camera );
	camera_->controller_ = bc_parent->ctrlr_;

	// route inputs to controller
	//bc_parent->ctrlr_->control_->connect_to_window( window_ );

}


