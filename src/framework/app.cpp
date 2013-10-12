#include <stdio.h>

#include <boost/thread.hpp>
#include <boost/asio/io_service.hpp>

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
boost::asio::io_service		g_io_;
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
void	nf::app::init()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;//.funcsig();//jess::clog << NEB_FUNCSIG << std::endl;

	// make sure content_ and platform_ are null before reseting them
	jess::assertion( !( content_ || platform_ ) );


	content_.reset( new nc::base );
	content_->init( shared_from_this() );

#ifdef __LIN__
	platform_.reset( new nppl::base );
#elif defined(__WIN__)
	platform_.reset( new nppw::base );
#endif

	platform_->init( shared_from_this() );
}
void	n10000::app::MainLoopSequ()
{
	boost::thread* t = 0;

	{
		boost::asio::io_service::work work( g_io_ );

		t = new boost::thread( io_service_run );
		
		while (1)
		{
			ContinueLoopSequ();
		}
	}
	
	// wait until asynchronous operations finish
	t->join();
}
void	n10000::app::MainLoopMulti()
{
	
}
void	n10000::app::ContinueLoopSequ()
{
	//if ( !m_content )  throw Except("m_content is null");
	//if ( !m_platform ) throw Except("m_platform is null");
	//if ( !m_network )  throw Except("m_network is null");

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
void	nf::app::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;//jess::clog.fun30000sig();

	content_->shutdown();
	//network->Shutdown(NULL);
	platform_->shutdown();
}
jess::shared_ptr<n22000::base>	n10000::app::request_window()
{
	// request
	return ( platform_->request_window() );
}
jess::shared_ptr<n21000::base>	n10000::app::get_platform()
{
	// get
	return platform_;
}














