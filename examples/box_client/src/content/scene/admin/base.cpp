#include <nebula/content/view/admin/human/base.hpp>
#include <nebula/content/actor/admin/rigid_dynamic_box.hpp>
#include <nebula/content/actor/admin/rigid_static_plane.hpp>
#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/camera.hpp>

#include <box_client/content/view/admin/base.hpp>

#include <box_client/content/scene/admin/base.hpp>

bc32100::base::base( jess::shared_ptr<n31100::base> parent ):
	n32100::base( parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;	
}
bc32100::base::~base()
{
	
}
void	bc32100::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	n32100::base::init();

	rigid_dyn_box_ = create_rigid_dynamic_box();

	rigid_sta_pln_ = create_rigid_static_plane();

	ctrlr_ = create_controller();

	view_ = create_view<bc33100::base>();
	NEB_ASSERT( bool( view_ ) );

	// connect controller to view
	/// \todo write function for this
	connect_control_to_view( ctrlr_, view_ );
	//ctrlr_->control_->connect_to_window( view_->window_ );

}

