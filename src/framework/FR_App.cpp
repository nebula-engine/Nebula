#include <stdio.h>


#include <utilities/Types/Utilities.h>
#include <content/Content.h>
#include <Network/Network.h>
#include <Platform/Platform/PL_PL_Platform.h>

#if defined(__LINUX)
#include <Platform/Platform/Linux/PL_PL_LIN_Platform.h>
#elif defined(__WINDOWS)
#include <Platform/Platform/Win/PL_PL_WIN_Platform.h>
#else
#error "__WINDOWS or __LINUX must be defined"
#endif






#include <framework/FR_App.h>

		FR_App::App() {
	PRINTSIG;

	m_content = 0;
	m_network = 0;
	m_platform = 0;
}
		FR_App::~App() {
	//m_platform->ShutDown();
}
void	FR_App::MainLoopSequ() {
    while(1) {
		ContinueLoopSequ();
	}
}
void	FR_App::MainLoopMulti() {
}
void	FR_App::ContinueLoopSequ() {
	if ( !m_content )  throw Except("m_content is null");
	if ( !m_platform ) throw Except("m_platform is null");
	if ( !m_network )  throw Except("m_network is null");

	m_content->Update();
	m_platform->update();
	m_network->Update(NULL);
	
}
void	FR_App::ContinueLoopMulti() {
}
void	FR_App::init(  v ) {
	PRINTSIG;
	
	m_content = new CO_Content();
	m_network = new Network();
	
    #ifdef __LINUX
		m_platform = new PL_PL_LIN_Platform();
	#elif defined(__WINDOWS)
		m_platform = new PL_PL_WIN_Platform();
	#endif
	

	m_content->init(v);
	m_network->init(v);
	m_platform->init(v);
	
	
}
void	FR_App::shutdown() {
	m_content->ShutDown();
	m_network->Shutdown(NULL);
	m_platform->shutdown();
	delete m_content;
	delete m_network;
	delete m_platform;
	
}
















