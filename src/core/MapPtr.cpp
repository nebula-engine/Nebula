
#include <core/Core.h>

#include <content/Universe/Admin/CO_UN_AD_Universe.h>
#include <content/Scene/Admin/CO_SC_AD_Scene.h>
#include <content/View/Admin/Human/CO_VI_AD_HU_View.h>

#include <content/Actor/Admin/CO_AC_AD_Controller.h>
#include <content/Actor/Admin/CO_AC_AD_RigidDynamicBox.h>

#include <content/Actor/Physics/CO_AC_PH_Material.h>

#include <content/Shape/Admin/CO_SH_AD_Box.h>

#include <Platform/Window/Linux/PL_WI_LIN_Window.h>







#include <core/MapPtr.h>

using namespace std;

template <class T>								MapPtr<T>::MapPtr() {
	m_map = map<int,T*>();
	m_next = 0;
}
template <class T>								MapPtr<T>::~MapPtr() {
}
template <class T>						T*		MapPtr<T>::Find( int a ) {
	auto it = m_map.find(a);
	
	if ( it == m_map.end() ) {
		return 0;
	}
	else {
		return it->second;
	}
}
template <class T>						void	MapPtr<T>::Erase( int a ) {
	auto it = m_map.find(a);
	if ( it != m_map.end() ) {
		delete it->second;
		m_map.erase( a );
	}
}
template <class T>						void	MapPtr<T>::Clear() {
	auto it = m_map.begin();
	
	for ( ; it != m_map.end(); it++ ) {
		if ( it->second ) {
			delete it->second;
		}
	}
	
	m_map.clear();
}
template <class T>						void	MapPtr<T>::For( MapPtr<T>::memFun1 f )
{
	if ( !f ) throw Except("func pointer invalid");
	
	auto it = m_map.begin();
	
	

	for ( ; it != m_map.end(); it++ ) {
		if ( !(it->second) ) throw Except("pointer invalid");

		CALL_MEMBER_FN(*(it->second),f)();
	}
}
template <class T>						void	MapPtr<T>::For( MapPtr<T>::memFun2 f, Void* data )
{
	if ( !f ) throw Except("func pointer invalid");
	
	auto it = m_map.begin();
	
	

	for ( ; it != m_map.end(); it++ ) {
		if ( !(it->second) ) throw Except("pointer invalid");
		
		CALL_MEMBER_FN(*(it->second),f)(data);
	}
}
template <class T>	template <class U>	void	MapPtr<T>::Create(U*& u)
{
	int no = m_next++;

	u = new U();

	m_map[no] = u;

	u->m_no = no;

	u->VInit(m_ar_init);
}



template class	MapPtr<CO_UN_AD_Universe>;
template class	MapPtr<CO_SC_AD_Scene>;
template class	MapPtr<CO_VI_AD_View>;
template class	MapPtr<CO_AC_AD_ActorBase>;
template class	MapPtr<CO_SH_AD_Shape>;
template class	MapPtr<CO_AC_PH_Material>;
template class	MapPtr<PL_WI_Window>;


template void	MapPtr<CO_UN_AD_Universe>::Create(CO_UN_AD_Universe*&);
template void	MapPtr<CO_SC_AD_Scene>::Create(CO_SC_AD_Scene*&);

template void	MapPtr<CO_VI_AD_View>::Create(CO_VI_AD_View*&);
template void	MapPtr<CO_VI_AD_View>::Create(CO_VI_AD_HU_View*&);

template void	MapPtr<CO_AC_AD_ActorBase>::Create(CO_AC_AD_ActorBase*&);
template void	MapPtr<CO_AC_AD_ActorBase>::Create(CO_AC_AD_Controller*&);
template void	MapPtr<CO_AC_AD_ActorBase>::Create(CO_AC_AD_RigidDynamicBox*&);

template void	MapPtr<CO_AC_PH_Material>::Create(CO_AC_PH_Material*&);

template void	MapPtr<CO_SH_AD_Shape>::Create(CO_SH_AD_Shape*&);
template void	MapPtr<CO_SH_AD_Shape>::Create(CO_SH_AD_Box*&);

template void	MapPtr<PL_WI_Window>::Create(PL_WI_Window*&);
template void	MapPtr<PL_WI_Window>::Create(PL_WI_LIN_Window*&);

