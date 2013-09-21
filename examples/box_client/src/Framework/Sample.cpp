#include <Framework/Sample.h>

		Sample::Sample(): App() {
	
}
void	Sample::VInit( Void* data ) {
	Framework::App::VInit( data );
	
	m_content->CreateUniverse( m_universeAuth );
	
	m_universeAuth->CreateScene( m_scene );
	
	m_scene->CreateViewHuman( m_viewHuman );
	
	m_scene->CreateRigidDynamicBox( m_rigidDynamicBox );

	m_scene->CreateController( m_controller );

	FR_COM_MSG_Dest dest;
	dest.icomm = m_controller;

	m_platform->GetWindow(0)->GetInput()->SetMouseMoveReceiver( dest );

	m_viewHuman->m_camera = new Content::Camera();

	m_viewHuman->m_camera->m_controller = m_controller;


}






