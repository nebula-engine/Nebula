#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <box_client/ns.hpp>
#include <box_client/framework/app.hpp>
#include <box_client/content/universe/admin/base.hpp>
#include <box_client/content/scene/admin/base.hpp>
#include <box_client/content/view/admin/base.hpp>
#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/actor/admin/rigid_static_plane.hpp>

//template void nc::base::create_universe( boost::shared_ptr<box_client::content::universe::admin::base>& );


bc0x100::app::app()
{
	
}
void	bc0x100::app::init()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	nf::app::init();
	
	universe_ = content_->create_universe<bc31100::base>();
	
	//jess::assertion( bool( universe_ ) );
	
	scene_ = universe_->create_scene<bc32100::base>();
	
	//jess::assertion( bool( scene_ ) );
	
	renderable_ = scene_->get_view();
}






