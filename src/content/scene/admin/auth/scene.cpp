#include <utilities/Types/Utilities.h>
#include <framework/FR_App.h>

#include <content/Physics/CO_PH_Physics.h>
#include <content/Physics/PhysicsScene.h>
#include <content/SceneAuth.h>
#include <content/Actor/Admin/CO_AC_AD_RigidDynamicBox.h>
#include <content/Actor/Admin/Controller.h>


		Content::SceneAuth::SceneAuth(): CO_SC_AD_Scene( app ) {
	PRINTSIG;
}
		Content::SceneAuth::~SceneAuth() {
}
void	Content::SceneAuth::VInit( Void* data ) {
	PRINTSIG;
	CO_SC_AD_Scene::VInit( data );
}
void	Content::SceneAuth::VUpdate() {
	CO_SC_AD_Scene::VUpdate();
}


















