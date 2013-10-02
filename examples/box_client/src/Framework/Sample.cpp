#include <Framework/Sample.h>

Sample::Sample()
{
	
}
void	Sample::init()
{
	nf::app::init();
	
	content_.pointer_->create_universe( m_universeAuth );
	
	
	
	m_universeAuth->create_scene( m_scene );
	
	m_scene->create_view_human( m_viewHuman );
	
	m_scene->create_rigid_dynamic_box( m_rigidDynamicBox );

	m_scene->create_controller( m_controller );
	
	//FR_COM_MSG_Dest dest;
	//dest.icomm = m_controller;
	
	//m_platform->windows_.at(0)->GetInput()->SetMouseMoveReceiver( dest );
	
	m_viewHuman->create_camera();
	
	m_viewHuman->camera_.pointer_->controller_ = m_controller;


}






