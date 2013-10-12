#include <nebula/content/view/admin/human/base.hpp>
#include <nebula/content/camera.hpp>

#include <box_client/content/view/admin/base.hpp>

#include <box_client/content/scene/admin/base.hpp>

void	box_client::content::scene::admin::base::init( jess::shared_ptr<n31100::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n32100::base::init( parent );
	
	rigid_dyn_box_ = create_rigid_dynamic_box();
	
	rigid_sta_pln_ = create_rigid_static_plane();
	
	ctrlr_ = create_controller();
	
	view_ = create_view<bc33100::base>();
}


