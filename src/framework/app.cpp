#include <stdio.h>

#include <boost/bind.hpp>

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






#include <nebula/framework/app.hpp>


template class jess::shared_ptr<nc::base>;
template void jess::shared_ptr<nc::base>::create( boost::function<void(boost::shared_ptr<nc::base>)> );



//template class jess::shared_ptr<nc::base>;
//template void jess::shared_ptr<nc::base>::create( boost::function<void(boost::shared_ptr<nc::base>)> );


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
	//m_network->Update(NULL);
	
}
void	nf::app::ContinueLoopMulti()
{

}
void	nf::app::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;//.funcsig();//jess::clog << NEB_FUNCSIG << std::endl;
	
	content_.create<nc::base>( boost::bind( &nc::base::init, _1, shared_from_this() ) );
	//network_ = new Network();
	
	#ifdef __LIN__
		platform_.create<nppl::base>( boost::bind( &nppl::base::init, _1, shared_from_this() ) );
	#elif defined(__WIN__)
		//m_platform = new PL_PL_WIN_Platform();
	#endif
	
	
}
void	nf::app::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;//jess::clog.funcsig();

	content_->shutdown();
	//network->Shutdown(NULL);
	platform_->shutdown();
}
boost::shared_ptr<npp::base>	nf::app::get_platform()
{
	return platform_.get();
}














