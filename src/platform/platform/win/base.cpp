#include <Windows.h>
#include <WinUser.h>

#define IDS_APP_TITLE 103
#define IDI_WIN32PROJECT1 107
#define IDI_SMALL 108
#define IDC_WIN32PROJECT1 109

#include <nebula/platform/platform/win/base.hpp>

n21200::base()
{

}
n21200::~base()
{

}
void	n21200::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	int nCmdShow = SW_SHOWNORMAL;

	HINSTANCE hInst = GetModuleHandleA(NULL);

}
void						n21200::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void						n21200::base::update()
{

}
v jess::shared_ptr<n22000::base> window		n21200::base::create_window()
{
	jess::clog << NEB_FUNCSIG << std::endl;
/*
	PL_WI_WIN_Window* pl_wi_win_window = NULL;
	m_window.Create(pl_wi_win_window);

	window = pl_wi_win_window;

	windowWin->init( data );
*/
}



