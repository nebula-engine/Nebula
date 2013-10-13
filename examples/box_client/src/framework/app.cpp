#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/actor/admin/rigid_static_plane.hpp>

#include <box_client/ns.hpp>
#include <box_client/content/universe/admin/base.hpp>
#include <box_client/content/scene/admin/base.hpp>
#include <box_client/content/view/admin/base.hpp>

#include <box_client/framework/app.hpp>

bc10000::app::app()
{
	
}
void	bc10000::app::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n10000::app::init();
	
	universe_ = content_->create_universe<bc31100::base>();
	
	scene_ = universe_->create_scene<bc32100::base>();
	
	renderable_ = scene_->view_; jess::assertion( bool( renderable_ ) );
}


