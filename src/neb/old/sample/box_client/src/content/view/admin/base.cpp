#include <ker/module/desc.hpp>

#include <nebula/define.hpp>
#include <nebula/kernel/module/type.hpp>

#include <nebula/platform/window/base.hpp>
#include <nebula/content/scene/admin/base.hpp>
#include <nebula/content/camera.hpp>
#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/actor/control/controller/base.hpp>

#include <box_client/content/scene/admin/base.hpp>
#include <box_client/ui/layout/base.hpp>

#include <box_client/content/view/admin/base.hpp>

void	bc33100::base::init()
{
	NEB_LOG_FUNC;

	// request window
	std::shared_ptr<ker::module::desc> desc_window( new ker::module::desc );
	desc_window->type_		= ker::module::type( nebula::kernel::module::type::N22100_BASE ); /// \todo make platform independent
	desc_window->mode_		= ker::module::mode::CREATE;
	desc_window->parent_		= shared_from_this();

	
	window_ = std::dynamic_pointer_cast<n22000::base>( request_module( desc_window ) );

	// ui
	//layout_.reset( new bc51000::base );
	//layout_->init();
	
	// camera
	std::shared_ptr<ker::module::desc> desc_camera( new ker::module::desc );
	desc_camera->type_		= ker::module::type( nebula::kernel::module::type::N30000_CAMERA );
	desc_camera->mode_		= ker::module::mode::CREATE;
	desc_camera->parent_		= shared_from_this();

	camera_ = std::dynamic_pointer_cast<n30000::camera>( request_module( desc_camera ) );
	
	std::shared_ptr<bc32100::base> bc_parent = std::dynamic_pointer_cast<bc32100::base>( parent_.lock() );
	camera_->controller_ = bc_parent->ctrlr_;
	
	// route inputs to controller
	bc_parent->ctrlr_->control_->connect_to_window( window_ );
}


