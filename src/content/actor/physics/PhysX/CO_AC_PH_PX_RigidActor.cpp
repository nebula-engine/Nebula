#include <nebula/framework/app.hpp>
#include <nebula/content/actor/physics/physx/material.hpp>





#include <nebula/content/actor/physics/physx/rigid_actor.hpp>

#include <nebula/ns.hpp>

void	ncapp::rigid_actor::init(const boost::shared_ptr<ncaa::base>& parent)
{
	parent_ = parent;

	//physx::PxPhysics* physics = m_app->GetContent()->GetPhysics()->GetPxPhysics();

	//physx::PxMaterial* material = 0;



	/*
	CO_AC_PH_PX_Material* material = (CO_AC_PH_PX_Material*)m_material.Find(0);
	
	if(!material) throw("no material");
	material->m_pxMaterial
	*/



	//material = m_pxPhysics->createMaterial(0.5f, 0.5f, 0.1f);    //static friction, dynamic friction, restitution
	//if(!material) throw("no material");

	//m_material.Push(material);

}



