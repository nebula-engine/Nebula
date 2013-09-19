
#include <content/Scene/Physics/CO_SC_PH_Scene.h>




					CO_SC_PH_Scene::Scene() {
}
					CO_SC_PH_Scene::Scene( const CO_SC_PH_Scene& physicsScene ) {
	printf("Copy Constructor------");
}
					CO_SC_PH_Scene::~Scene() {

}
CO_SC_PH_Scene&		CO_SC_PH_Scene::operator=( const CO_SC_PH_Scene& physicsScene ) {
	return *this;
}
void				CO_SC_PH_Scene::VInit( Void* data ) {

}
void				CO_SC_PH_Scene::VUpdate() {

}
void				CO_SC_PH_Scene::VStep( Void* data ) {

}
void				CO_SC_PH_Scene::VRender( Void* data ) {

}
void				CO_SC_PH_Scene::AddActor( CO_AC_AD_ActorBase* actor ) {

}









