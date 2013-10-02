#ifndef _SAMPLE_H
#define _SAMPLE_H

//#include <NebulaAPI.h>

#include <nebula/api.hpp>


class Sample:
	public nf::app
{
public:
	Sample();
	void							init();
	
	
	
	boost::shared_ptr<ncua::base>				m_universeAuth;
	boost::shared_ptr<nc_sc_a::base>			m_scene;
	boost::shared_ptr<ncvah::base>				m_viewHuman;
	boost::shared_ptr<ncaa::rigid_dynamic_box>		m_rigidDynamicBox;
	boost::shared_ptr<ncaa::rigid_static_plane>		m_rigidStaticPlane;
	boost::shared_ptr<ncaa::controller>			m_controller;
	
};


#endif









