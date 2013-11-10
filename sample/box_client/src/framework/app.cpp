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
	std::shared_ptr<ker::module::task> task1( new ker::module::task( std::bind( &bc10000::app::init, this ) ) );
	
//	ker::module::init_task task1( std::bind( &bc10000::app::init, this ) );
	
	
	/// \todo neb init is a prereq of box init( could be more robust )
	task1->tasks_.task_map_[1] = tasks_init_.task_map_[1];
	task1->tasks_.task_flag_ |= 1;
	

	
	tasks_init_.task_map_[2] = task1;
	tasks_init_.task_flag_ |= 2;

}
void	bc10000::app::init()
{
	NEB_LOG_FUNC;




	
	std::shared_ptr<ker::module::desc> desc_uni( new ker::module::desc() );
	
	desc_uni->type_			= ker::module::type( box_client::kernel::module::type::BC31100_BASE );
	desc_uni->mode_			= ker::module::mode::CREATE;
	desc_uni->parent_		= content_;
	
	universe_ = std::dynamic_pointer_cast<bc31100::base>( k->request_module( desc_uni ) );
	


	
	
	
	std::shared_ptr<ker::module::desc> desc_scene( new ker::module::desc() );
	
	desc_scene->type_		= ker::module::type( box_client::kernel::module::type::BC32100_BASE );
	desc_scene->mode_		= ker::module::mode::CREATE;
	desc_scene->parent_		= universe_;
	
	scene_ = std::dynamic_pointer_cast<bc32100::base>( k->request_module( desc_scene ) );
	
	
	
	

	
	renderable_ = scene_->view_;

}


