#include <stdio.h>

#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <nebula/define.hpp>
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

namespace nebula
{
	namespace framework
	{
	}
}


void	io_service_run()
{
	n10000::g_io_.run();
}

n10000::app::app()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
n10000::app::~app()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n10000::app::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// make sure content_ and platform_ are null before reseting them
	jess::assertion( !( content_ || platform_ ) );

	content_.reset( new n30000::base( shared_from_this() ) );
	content_->init();

#ifdef __LIN__
	platform_.reset( new n21100::base );
#elif defined(__WIN__)
	platform_.reset( new n21200::base );
#endif

	platform_->init( shared_from_this() );
}
void	n10000::app::MainLoopSequ()
{
	while (1)
	{
		ContinueLoopSequ();
	}
}
void	n10000::app::MainLoopMulti()
{
	
}
void	n10000::app::ContinueLoopSequ()
{
	content_->update();
	platform_->update();

	if ( bool( renderable_ ) )
	{
		renderable_->render();
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
jess::shared_ptr<n22000::base>	n10000::app::request_window()
{
	return ( platform_->request_window() );
}
jess::shared_ptr<n21000::base>	n10000::app::get_platform()
{
	return platform_;
}














