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


//template class jess::shared_ptr<nc::base>;
//template void jess::shared_ptr<nc::base>::create( boost::function<void(jess::shared_ptr<nc::base>)> );



//template class jess::shared_ptr<nc::base>;
//template void jess::shared_ptr<nc::base>::create( boost::function<void(jess::shared_ptr<nc::base>)> );


nf::app::app()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	//m_content = 0;
	//m_network = 0;
	//m_platform = 0;
}
nf::app::~app()
{
	jess::clog << NEB_FUNCSIG << std::endl;//jess::clog.funcsig();//m_platform->ShutDown();
}
void	nf::app::MainLoopSequ()
{
	while(1)
	{
		ContinueLoopSequ();
	}
}
void	nf::app::MainLoopMulti()
{

}
void	nf::app::ContinueLoopSequ()
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
void	nf::app::ContinueLoopMulti()
{

}
void	nf::app::init()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;//.funcsig();//jess::clog << NEB_FUNCSIG << std::endl;
	
	content_.reset( new nc::base );
	content_->init( shared_from_this() );
	
	#ifdef __LIN__
		platform_.reset( new nppl::base );
	#elif defined(__WIN__)
		platform_.reset( new nppw::base );
	#endif
	
	platform_->init( shared_from_this() );
}
void	nf::app::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;//jess::clog.funcsig();

	content_->shutdown();
	//network->Shutdown(NULL);
	platform_->shutdown();
}
jess::shared_ptr<npw::base>	nf::app::request_window()
{
	// request
	return ( platform_->request_window() );
}
jess::shared_ptr<npp::base>	nf::app::get_platform()
{
	// get
	return platform_;
}














