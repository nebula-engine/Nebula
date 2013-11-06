#include <nebula/define.hpp>

#include <ker/kernel.hpp>

#include <nebula/kernel/module/type.hpp>

#include <box_client/kernel/factory.hpp>
#include <box_client/kernel/module/type.hpp>


int main( int argc, char** argv )
{
	NEB_LOG_FUNC;
	/*
	   jess::clog << NEB_FUNCSIG << std::endl;

	   std::shared_ptr<bc10000::app> a( new bc10000::app() );

	   try
	   {
	   a->init();

	   a->MainLoopSequ();

	   a->shutdown();
	   }
	   catch ( std::exception& e )	
	   {
	   printf( "caught: %s\n", e.what() );
	   }
	   */

	/* the factory knows can create empty modules of specific types based on a enum value.
	 * it is necessary because the kernel doesn't know anything about the implementation.
	 */
	std::shared_ptr<box_client::kernel::factory> factory( new box_client::kernel::factory() );

	std::shared_ptr<ker::kernel> k( new ker::kernel() );
	k->factory_ = factory;
	k->desc_.reset( new ker::module::desc );
	k->desc_->mode_ = ker::module::mode::KERNEL;
	
	/* the following descriptions can be loaded from files */

	
	
	
	std::shared_ptr<ker::module::desc> desc_content( new ker::module::desc() );
	
	desc_content->type_		= ker::module::type( nebula::kernel::module::type::CONTENT );
	desc_content->mode_		= ker::module::mode::CREATE;
	desc_content->desc_parent_	= k->desc_;
	
	
	std::shared_ptr<ker::module::desc> desc_uni( new ker::module::desc() );
	
	desc_uni->type_			= ker::module::type( box_client::kernel::module::type::BC31100_BASE );
	desc_uni->mode_			= ker::module::mode::CREATE;
	desc_uni->desc_parent_		= desc_content;
	
	
	std::shared_ptr<ker::module::desc> desc_scene( new ker::module::desc() );
	
	desc_scene->type_		= ker::module::type( box_client::kernel::module::type::BC32100_BASE );
	desc_scene->mode_		= ker::module::mode::CREATE;
	desc_scene->desc_parent_	= desc_uni;
	
	
	
	std::shared_ptr<ker::module::desc> desc_view( new ker::module::desc() );
	
	desc_view->type_		= ker::module::type( box_client::kernel::module::type::BC33100_BASE );
	desc_view->mode_		= ker::module::mode::CREATE;
	desc_view->desc_parent_		= desc_scene;
	
	
	
	
	
	std::shared_ptr<ker::module::module> m = k->request_module( desc_view );
	
	return 0;
}









