#include <nebula/content/scene/physics/base.hpp>

namespace nc_sc = nebula::content::scene;
namespace nc_sc_p = nc_sc::physics;


nc_sc_p::base::base()
{
	
}
nc_sc_p::base::base(const nc_sc_p::base& cpy)
{
	//printf("Copy Constructor------");
}
nc_sc_p::base::~base()
{
	
}
nc_sc_p::base&		CO_SC_PH_Scene::operator=( const CO_SC_PH_Scene& physicsScene )
{
	return *this;
}
void				nc_sc_p::base::VInit( Void* data ) {

}
void				nc_sc_p::base::VUpdate() {

}
void				nc_sc_p::base::VStep( Void* data )
{
	
}
void				nc_sc_p::base::VRender( Void* data )
{
	
}
void				nc_sc_p::base::AddActor( CO_AC_AD_ActorBase* actor )
{
	
}









