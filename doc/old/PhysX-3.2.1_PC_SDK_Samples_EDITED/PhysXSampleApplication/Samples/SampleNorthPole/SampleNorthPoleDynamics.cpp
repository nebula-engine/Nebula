

#include "PxPhysicsAPI.h"
#include "extensions/PxExtensionsAPI.h"
#include "PxTkStream.h"
#include "SampleNorthPole.h"
#include "RenderBaseActor.h"

using namespace PxToolkit;

//#define USE_RAYCAST_CCD_FOR_SNOWBALLS

void SampleNorthPole::detach()
{
	std::vector<PxShape*>::const_iterator ite;
	for(ite=mDetaching.begin(); ite<mDetaching.end(); ++ite)
	{
		PxShape* shape = *ite;
		
		PxMaterial* mat;
		shape->getMaterials(&mat,1);
		PxGeometryHolder geometry = shape->getGeometry();
		PxTransform newActorPose = PxShapeExt::getGlobalPose(*shape);

		PxRigidDynamic* newActor = PxCreateDynamic(*mPhysics, newActorPose, geometry.any(), *mat, 1);
		if(!newActor) 
			fatalError("creating detached actor failed");
		getActiveScene().addActor(*newActor);
		mPhysicsActors.push_back(newActor);

		// the only convex shape is the nose, so we can just test the type
		if(geometry.getType() == PxGeometryType::eCONVEXMESH)
		{
			newActor->addForce(PxVec3(0,.1,0),PxForceMode::eFORCE);
			size_t index = reinterpret_cast<size_t>(shape->getActor().userData);
			mSnowman[index].changeMood();
		}

		// reuse the old shape's rendering actor
		RenderBaseActor* render = reinterpret_cast<RenderBaseActor*>(shape->userData);
		PxShape* newShape;
		newActor->getShapes(&newShape,1);
		render->setPhysicsShape(newShape);
		newShape->userData = render;
		setCCDActive(*newShape);

		shape->release();
	}
	mDetaching.clear();
}

void SampleNorthPole::cookCarrotConvexMesh()
{
	static const PxVec3 carrotVerts[] = {PxVec3(0,0,.3),PxVec3(.05,0,0),PxVec3(-.05,0,0),PxVec3(0,.05,0),PxVec3(0,-.05,0)};

	mCarrotConvex = PxToolkit::createConvexMesh(getPhysics(), getCooking(), carrotVerts, 5, PxConvexFlag::eCOMPUTE_CONVEX);
	if(!mCarrotConvex)
		fatalError("creating the convex mesh failed");
}

PxRigidDynamic* SampleNorthPole::throwBall()
{
	static unsigned int numBall = 0;

	PxVec3 vel = getCamera().getViewDir() * 20.0f;

	PxRigidDynamic* ballActor = getPhysics().createRigidDynamic(PxTransform(getCamera().getPos()+getCamera().getViewDir()));
	if(!ballActor)
		fatalError("creating ball actor failed");

	ballActor->setLinearVelocity(vel);

	PxShape* ballShape = ballActor->createShape(PxSphereGeometry(0.1f),getDefaultMaterial());
	if(!ballShape)
		fatalError("creating ball shape failed");

	setSnowball(*ballShape);

	PxRigidBodyExt::updateMassAndInertia(*ballActor,1);

#ifndef USE_RAYCAST_CCD_FOR_SNOWBALLS
	setCCDActive(*ballShape);
#endif
	
	getActiveScene().addActor(*ballActor);

	RenderBaseActor* actor = mSnowBallsRenderActors[numBall];;
	if(actor)
	{
		ballShape->userData = actor;
		actor->setPhysicsShape(ballShape);
	}
	else
	{
#ifdef RENDERER_GXM
		actor = createRenderObjectFromShape(ballShape,mSnowManMaterial);
#else
		actor = createRenderObjectFromShape(ballShape,mSnowMaterial);
#endif
		mSnowBallsRenderActors[numBall] = actor;
	}	

#ifdef USE_RAYCAST_CCD_FOR_SNOWBALLS
	if(ballShape)
	{
		RenderBaseActor* renderActor = reinterpret_cast<RenderBaseActor*>(ballShape->userData);
		renderActor->setRaycastCCD(true);
	}
#endif

	PxRigidDynamic* oldBall = mSnowBalls[numBall];

	if(oldBall) 
	{
		removeActor(oldBall);		
		oldBall->release();
	}	

	mSnowBalls[numBall] = ballActor;
	if(! (++numBall < NUM_BALLS)) 
		numBall=0;

	return ballActor;
}

void SampleNorthPole::createSnowMen()
{
	for(PxU32 i=0; i<NUM_SNOWMEN; i++)
	{	
		PxVec3 pos(0,1,-8);
		PxQuat rot(2*PxPi*i/NUM_SNOWMEN,PxVec3(0,1,0));
		createSnowMan(PxTransform(rot.rotate(pos),rot),i,i);
	}

}

PxRigidDynamic* SampleNorthPole::createSnowMan(const PxTransform& pos, const PxU32 mode, const PxU32 index)
{
	PxRigidDynamic* snowmanActor = getPhysics().createRigidDynamic(PxTransform(pos));
	if(!snowmanActor)
		fatalError("create snowman actor failed");

	PxMaterial&	material = getApplication()->getContentManager->getMaterialManager()->getDefaultMaterial();
	
	PxShape* armL = NULL;
	PxShape* armR = NULL;

	switch(mode%5)
	{
	case 0: // with a weight at the bottom
		{
			if(!snowmanActor->createShape(PxSphereGeometry(.2),material,PxTransform(PxVec3(0,-.29,0))))
				fatalError("creating snowman shape failed");
			
			PxRigidBodyExt::updateMassAndInertia(*snowmanActor,10);
			
			if(!snowmanActor->createShape(PxSphereGeometry(.5),material))
				fatalError("creating snowman shape failed");
			if(!snowmanActor->createShape(PxSphereGeometry(.4),material,PxTransform(PxVec3(0,.6,0))))
				fatalError("creating snowman shape failed");
			if(!snowmanActor->createShape(PxSphereGeometry(.3),material,PxTransform(PxVec3(0,1.1,0))))
				fatalError("creating snowman shape failed");

			armL = snowmanActor->createShape(PxCapsuleGeometry(.1,.1),material,PxTransform(PxVec3(-.4,.7,0)));
			armR = snowmanActor->createShape(PxCapsuleGeometry(.1,.1),material,PxTransform(PxVec3( .4,.7,0)));
		}
		break;
	case 1: // only considering lowest shape mass
		{
			if(!snowmanActor->createShape(PxSphereGeometry(.5),material))
				fatalError("creating snowman shape failed");
			
			PxRigidBodyExt::updateMassAndInertia(*snowmanActor,1);

			if(!snowmanActor->createShape(PxSphereGeometry(.4),material,PxTransform(PxVec3(0,.6,0))))
				fatalError("creating snowman shape failed");
			if(!snowmanActor->createShape(PxSphereGeometry(.3),material,PxTransform(PxVec3(0,1.1,0))))
				fatalError("creating snowman shape failed");
			armL = snowmanActor->createShape(PxCapsuleGeometry(.1,.1),material,PxTransform(PxVec3(-.4,.7,0)));
			armR = snowmanActor->createShape(PxCapsuleGeometry(.1,.1),material,PxTransform(PxVec3( .4,.7,0)));

			snowmanActor->setCMassLocalPose(PxTransform(PxVec3(0,-.5,0)));
		}
		break;
	case 2: // considering whole mass
		{
			if(!snowmanActor->createShape(PxSphereGeometry(.5),material))
				fatalError("creating snowman shape failed");
			if(!snowmanActor->createShape(PxSphereGeometry(.4),material,PxTransform(PxVec3(0,.6,0))))
				fatalError("creating snowman shape failed");
			if(!snowmanActor->createShape(PxSphereGeometry(.3),material,PxTransform(PxVec3(0,1.1,0))))
				fatalError("creating snowman shape failed");
			armL = snowmanActor->createShape(PxCapsuleGeometry(.1,.1),material,PxTransform(PxVec3(-.4,.7,0)));
			armR = snowmanActor->createShape(PxCapsuleGeometry(.1,.1),material,PxTransform(PxVec3( .4,.7,0)));

			PxRigidBodyExt::updateMassAndInertia(*snowmanActor,1);
			snowmanActor->setCMassLocalPose(PxTransform(PxVec3(0,-.5,0)));
		}
		break;
	case 3: // considering whole mass with low COM
		{
			if(!snowmanActor->createShape(PxSphereGeometry(.5),material))
				fatalError("creating snowman shape failed");
			if(!snowmanActor->createShape(PxSphereGeometry(.4),material,PxTransform(PxVec3(0,.6,0))))
				fatalError("creating snowman shape failed");
			if(!snowmanActor->createShape(PxSphereGeometry(.3),material,PxTransform(PxVec3(0,1.1,0))))
				fatalError("creating snowman shape failed");
			armL = snowmanActor->createShape(PxCapsuleGeometry(.1,.1),material,PxTransform(PxVec3(-.4,.7,0)));
			armR = snowmanActor->createShape(PxCapsuleGeometry(.1,.1),material,PxTransform(PxVec3( .4,.7,0)));

			const PxVec3 localPos = PxVec3(0,-.5,0);
			PxRigidBodyExt::updateMassAndInertia(*snowmanActor,1,&localPos);
		}
		break;
	case 4: // setting up mass properties manually
		{
			if(!snowmanActor->createShape(PxSphereGeometry(.5),material))
				fatalError("creating snowman shape failed");
			if(!snowmanActor->createShape(PxSphereGeometry(.4),material,PxTransform(PxVec3(0,.6,0))))
				fatalError("creating snowman shape failed");
			if(!snowmanActor->createShape(PxSphereGeometry(.3),material,PxTransform(PxVec3(0,1.1,0))))
				fatalError("creating snowman shape failed");
			armL = snowmanActor->createShape(PxCapsuleGeometry(.1,.1),material,PxTransform(PxVec3(-.4,.7,0)));
			armR = snowmanActor->createShape(PxCapsuleGeometry(.1,.1),material,PxTransform(PxVec3( .4,.7,0)));

			snowmanActor->setMass(1);
			snowmanActor->setCMassLocalPose(PxTransform(PxVec3(0,-.5,0)));
			snowmanActor->setMassSpaceInertiaTensor(PxVec3(.05,100,100));
		}
		break;
	default:
		break;
	}
	
	if(!armL)
		fatalError("creating snowman shape failed");
	if(!armR)
		fatalError("creating snowman shape failed");

	setDetachable(*armL);
	setDetachable(*armR);

#ifdef RENDERER_PSP2
	createRenderObjectsFromActor(snowmanActor,mSnowManMaterial);
#else
	createRenderObjectsFromActor(snowmanActor,mSnowMaterial);
#endif

	PxShape* carrot = snowmanActor->createShape(PxConvexMeshGeometry(mCarrotConvex),material,PxTransform(PxVec3(0,1.1,.3)));
	if(!carrot)
		fatalError("create snowman shape failed");
	setDetachable(*carrot);
	setCCDActive(*carrot);

	createRenderObjectFromShape(carrot,mCarrotMaterial);

	PxShape* button = NULL;
	
	button = snowmanActor->createShape(PxCapsuleGeometry(.02,.05),material,PxTransform(PxVec3(.1,1.2,.3),PxQuat(PxHalfPi/3,PxVec3(0,0,1))));
	if(!button)
		fatalError("create snowman shape failed");
	mSnowman[index].eyeL = button;
	button->setFlag(PxShapeFlag::eSIMULATION_SHAPE,false);
	createRenderObjectFromShape(button,mButtonMaterial);

	button = snowmanActor->createShape(PxCapsuleGeometry(.02,.05),material,PxTransform(PxVec3(-.1,1.2,.3),PxQuat(-PxHalfPi/3,PxVec3(0,0,1))));
	if(!button)
		fatalError("create snowman shape failed");
	mSnowman[index].eyeR = button;
	button->setFlag(PxShapeFlag::eSIMULATION_SHAPE,false);
	createRenderObjectFromShape(button,mButtonMaterial);

	button = snowmanActor->createShape(PxSphereGeometry(.05),material,PxTransform(PxVec3(0,.8,.35)));
	if(!button)
		fatalError("create snowman shape failed");
	setDetachable(*button);
	createRenderObjectFromShape(button,mButtonMaterial);

	button = snowmanActor->createShape(PxSphereGeometry(.05),material,PxTransform(PxVec3(0,.6,.4)));
	if(!button)
		fatalError("create snowman shape failed");
	setDetachable(*button);
	createRenderObjectFromShape(button,mButtonMaterial);
	
	button = snowmanActor->createShape(PxSphereGeometry(.05),material,PxTransform(PxVec3(0,.4,.35)));
	if(!button)
		fatalError("create snowman shape failed");
	setDetachable(*button);
	createRenderObjectFromShape(button,mButtonMaterial);

	getActiveScene().addActor(*snowmanActor);

	snowmanActor->userData = (void*)size_t(index);

	mPhysicsActors.push_back(snowmanActor);

	return snowmanActor;
}

