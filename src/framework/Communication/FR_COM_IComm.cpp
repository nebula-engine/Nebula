#include <framework/Communication/FR_COM_IComm.h>
#include <framework/Communication/Message/FR_COM_MSG_Message.h>


		FR_COM_IComm::IComm() {
}
		FR_COM_IComm::~IComm() {
}
void	FR_COM_IComm::Update() {
	FR_COM_MSG_Message* message;
	
	while ( !m_messages.empty() ) {
		message = m_messages.front();
		m_messages.pop();
		Process( message );
	}
	
	
}
void	FR_COM_IComm::Post( FR_COM_MSG_Message* message ) {
	m_messages.push( message );
	
	
}










