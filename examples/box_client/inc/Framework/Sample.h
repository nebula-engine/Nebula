#ifndef _SAMPLE_H
#define _SAMPLE_H

#include <NebulaAPI.h>

namespace Content {
	class RigidStaticPlane;
};

class Sample: public Framework::App {
public:
			Sample();
	void	VInit( Void* data );
	
	
	
	CO_UN_AD_Universe*			m_universeAuth;
	CO_SC_AD_Scene*				m_scene;
	CO_VI_AD_HU_View*			m_viewHuman;
	CO_AC_AD_RigidDynamicBox*	m_rigidDynamicBox;
	CO_AC_AD_RigidStaticPlane*	m_rigidStaticPlane;
	CO_AC_AD_Controller*		m_controller;
	
};


#endif









