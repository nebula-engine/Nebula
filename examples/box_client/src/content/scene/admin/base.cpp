#include <nebula/content/view/admin/human/base.hpp>
#include <nebula/content/camera.hpp>

#include <box_client/content/view/admin/base.hpp>

#include <box_client/content/scene/admin/base.hpp>

void	box_client::content::scene::admin::base::init( boost::shared_ptr<ncua::base>& parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	nc_sc_a::base::init( parent );

	create_rigid_dynamic_box( rigid_dyn_box_ );

	create_controller( ctrlr_ );

	create_view( view_.pointer_ );
}


