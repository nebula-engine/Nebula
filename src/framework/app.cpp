#include <stdio.h>


#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <nebula/define.hpp>
#include <nebula/content/base.hpp>
#include <nebula/asio/network/base.hpp>
//#include <nebula/platform/platform/base.h>

#if defined(__LIN__)
	#include <nebula/platform/platform/lin/base.hpp>
#elif defined(__WIN__)
	#include <nebula/platform/platform/win/base.hpp>
#else
	#error "__WIN__ or __LIN__ must be defined"
#endif


#include <nebula/framework/renderable.hpp>
#include <nebula/framework/app.hpp>


//template class jess::shared_ptr<n30000::base>;
//template void jess::shared_ptr<n30000::base>::create( boost::fun30000tion<void(jess::shared_ptr<n30000::base>)> );



//template class jess::shared_ptr<n30000::base>;
//template void jess::shared_ptr<n30000::base>::create( boost::fun30000tion<void(jess::shared_ptr<n30000::base>)> );


n10000::app::app()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	//m_content = 0;
	//m_network = 0;
	//m_platform = 0;
}
n10000::app::~app()
{
	jess::clog << NEB_FUNCSIG << std::endl;//jess::clog.fun30000sig();//m_platform->ShutDown();
}
void	n10000::app::MainLoopSequ()
{
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
void	n10000::app::init()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;//.fun30000sig();//jess::clog << NEB_FUNCSIG << std::endl;

	// make sure content_ and platform_ are null before reseting them
	jess::assertion( !( content_ || platform_ ) );
	
	
	content_.reset( new n30000::base );
	content_->init( shared_from_this() );
	
	#ifdef __LIN__
		platform_.reset( new n21100::base );
	#elif defined(__WIN__)
		platform_.reset( new n21200::base );
	#endif
	
	platform_->init( shared_from_this() );
}
void	n10000::app::shutdown()
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














