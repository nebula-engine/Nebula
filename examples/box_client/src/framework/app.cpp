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
	std::shared_ptr<ker::module::init_task> task1( new ker::module::init_task( std::bind( &bc10000::app::init, this ) ) );
	
//	ker::module::init_task task1( std::bind( &bc10000::app::init, this ) );
	
	
	/// \todo neb init is a prereq of box init( could be more robust )
	task1.init_map_[1] = init_map_[1];
	
	init_map_[2] = task1;
	
	init_flag_ |= 2;

}
voi:	bc10000::app::init()
{
	NEB_LOG_FUNC;

	//n10000::app::init();

	//universe_ = content_->create_universe<bc31100::base>();

	//scene_ = universe_->create_scene<bc32100::base>();



	//renderable_ = scene_->view_;

}


