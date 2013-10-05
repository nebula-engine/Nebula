#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <box_client/framework/app.hpp>
#include <box_client/content/universe/admin/base.hpp>
#include <box_client/content/scene/admin/base.hpp>
#include <box_client/content/view/admin/base.hpp>

//template void nc::base::create_universe( boost::shared_ptr<box_client::content::universe::admin::base>& );


bc0x100::app::app()
{
	
}
void	bc0x100::app::init()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	nf::app::init();
	
	content_->create_universe( universe_ );
	
	//jess::assertion( bool( universe_ ) );
	
	universe_->create_scene( scene_ );
	
	//jess::assertion( bool( scene_ ) );
	
	renderable_ = scene_->get_view();
}






