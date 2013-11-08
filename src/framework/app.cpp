#include <stdio.h>

#include <ker/module/desc.hpp>

#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <nebula/define.hpp>
#include <nebula/kernel/module/type.hpp>
#include <nebula/content/base.hpp>
#include <nebula/asio/network/base.hpp>

#if defined(__LIN__)
#include <nebula/platform/platform/lin/base.hpp>
#elif defined(__WIN__)
#include <nebula/platform/platform/win/base.hpp>
#else
#error "__WIN__ or __LIN__ must be defined"
#endif

#include <nebula/framework/renderable.hpp>

#include <nebula/framework/app.hpp>



n10000::app::app()
{
	NEB_LOG_FUNC;

	std::shared_ptr<ker::module::task> task1( new ker::module::task( std::bind( &n10000::app::init, this ) ) );
	
	// add a task
	tasks_init_.task_map_[1] = task1;
	tasks_init_.task_flag_ |= 1;
}
n10000::app::~app()
{
	NEB_LOG_FUNC;
}
void	n10000::app::init()
{
	NEB_LOG_FUNC;

	// content
	std::shared_ptr<ker::module::desc> desc_content( new ker::module::desc() );

	desc_content->type_		= ker::module::type( nebula::kernel::module::type::N30000_BASE );
	desc_content->mode_		= ker::module::mode::CREATE;
	desc_content->parent_		= shared_from_this();

	content_ = std::dynamic_pointer_cast<n30000::base>( request_module( desc_content ) );
	
	
	// platform
	std::shared_ptr<ker::module::desc> desc_platform( new ker::module::desc() );
	
#ifdef __LIN__
	desc_platform->type_		= ker::module::type( nebula::kernel::module::type::N21100_BASE );
#elif defined(__WIN__)
	desc_platform->type_		= ker::module::type( nebula::kernel::module::type::N21200_BASE );
#endif
	
	desc_platform->mode_		= ker::module::mode::CREATE;
	desc_platform->parent_		= shared_from_this();
	
	platform_ = std::dynamic_pointer_cast<n21000::base>( request_module( desc_platform ) );
	

}
void	n10000::app::main_loop()
{
	//	for(int i = 0; i < 10; i++)
	while(1)
	{
		ContinueLoopSequ();
	}
}
void	n10000::app::MainLoopSequ()
{
	//	for(int i = 0; i < 10; i++)
	while(1)
	{
		ContinueLoopSequ();
	}
}
void	n10000::app::MainLoopMulti()
{

}
void	n10000::app::ContinueLoopSequ()
{
	NEB_ASSERT( content_ );
	NEB_ASSERT( platform_ );

	content_->update();
	platform_->update();

	if ( bool( renderable_ ) )
	{
		renderable_->render();
	}
	else
	{
		jess::clog << "no renderable" << std::endl;
	}
}
void	n10000::app::ContinueLoopMulti()
{

}
void	n10000::app::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	content_->shutdown();
	platform_->shutdown();
}
/*std::shared_ptr<n22000::base>	n10000::app::request_window()
  {
  return ( platform_->request_window() );
  }
  std::shared_ptr<n21000::base>	n10000::app::get_platform()
  {
  return platform_;
  }*/














