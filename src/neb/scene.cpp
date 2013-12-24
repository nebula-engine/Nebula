#include <math/free.h>

#include <neb/app.h>
#include <neb/actor/desc.h>
#include <neb/packet/packet.h>
#include <neb/physics.h>
#include <neb/scene.h>
#include <neb/simulation_callback.h>
#include <neb/actor/free.h>
#include <neb/actor/Base.h>
#include <neb/actor/Rigid_Dynamic.h>
#include <neb/actor/Rigid_Static.h>
#include <neb/actor/Controller.h>
#include <neb/actor/Light.h>
#include <neb/shape.h>

int		parse_shape_type(char const * str)
{
	assert(str);
	if(strcmp(str,"box") == 0) return neb::shape::BOX;
	if(strcmp(str ,"sphere") == 0) return neb::shape::SPHERE;
	return neb::shape::NONE;
}
neb::shape	xml_parse_geo(tinyxml2::XMLElement* element)
{
	int type = parse_shape_type(element->Attribute("type"));
	
	neb::shape shape;
	shape.type = type;
	
	switch(type)
	{
		case neb::shape::BOX:
			shape.box(element);
			break;
		case neb::shape::SPHERE:
			shape.sphere(element);
			break;
		default:
			break;
	}
	
	return shape;
}


neb::scene::scene(): px_scene_(NULL), px_filter_shader_(NULL) {
}
std::shared_ptr<neb::app>	neb::scene::get_app() {
	
	assert(!app_.expired());
	
	return app_.lock();
}
std::shared_ptr<neb::actor::Light>	neb::scene::Create_Light(tinyxml2::XMLElement* el_actor, std::shared_ptr<neb::actor::Base> parent) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	glutpp::desc_light desc;
	desc.load(el_actor);
	
	return Create_Light(desc, parent);
}
std::shared_ptr<neb::actor::Light>			neb::scene::Create_Light(glutpp::desc_light desc,		std::shared_ptr<neb::actor::Base> parent) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	// create
	std::shared_ptr<neb::actor::Light> actor(new neb::actor::Light);
	
	actor->desc_ = desc;
	
	actor->parent_ = parent;
	
	add_light(actor);
	
	if(parent)
	{
		parent->lights_.push_back(actor->i_);
	}
	
	return actor;
}
void	neb::scene::Create_Actors(tinyxml2::XMLElement* el_scene,		std::shared_ptr<neb::actor::Base> parent) {

	printf("%s\n",__PRETTY_FUNCTION__);

	tinyxml2::XMLElement* el_actor = el_scene->FirstChildElement("actor");

	std::shared_ptr<neb::actor::Base> actor;

	while( el_actor )
	{
		actor = Create_Actor(el_actor, parent);

		// recursivly create children
		Create_Actors(el_actor, actor);
		Create_Lights(el_actor, actor);

		el_actor = el_actor->NextSiblingElement("actor");
	}


}
void	neb::scene::Create_Lights(tinyxml2::XMLElement* element, std::shared_ptr<neb::actor::Base> parent) {

	printf("%s\n",__PRETTY_FUNCTION__);

	//std::shared_ptr<neb::actor::Light> light;

	tinyxml2::XMLElement* element_light = element->FirstChildElement("light");
	while(element_light)
	{	
		Create_Light(element_light, parent);

		element_light = element_light->NextSiblingElement("light");
	}
}
neb::scene::base_t	neb::scene::Create_Actor(tinyxml2::XMLElement* el_actor, std::shared_ptr<neb::actor::Base> parent) {

	printf("%s\n",__PRETTY_FUNCTION__);

	const char* buf = el_actor->Attribute("type");

	assert(buf);

	std::shared_ptr<neb::actor::Base> actor;

	if( strcmp(buf, "rigid_dynamic") == 0)
	{
		actor = Create_Rigid_Dynamic(el_actor, parent);
	}
	else if( strcmp(buf, "rigid_static") == 0)
	{
		actor = Create_Rigid_Static(el_actor, parent);
	}	
	else if( strcmp(buf, "rigid_static_plane") == 0)
	{
		actor = Create_Rigid_Static_Plane(el_actor, parent);
	}	
	else if( strcmp(buf, "controller") == 0)
	{
		actor = Create_Controller(el_actor);
	}


	return actor;
}
neb::scene::rigid_dynamic_t neb::scene::Create_Rigid_Dynamic(tinyxml2::XMLElement* el_actor, neb::scene::base_t parent) {

	neb::actor::desc desc;
	desc.type = neb::actor::RIGID_DYNAMIC;

	desc.load(el_actor);
	
	return Create_Rigid_Dynamic(desc, parent);
}
std::shared_ptr<neb::actor::Rigid_Static>		neb::scene::Create_Rigid_Static(tinyxml2::XMLElement* el_actor, neb::scene::base_t parent) {

	printf("%s\n", __PRETTY_FUNCTION__);

	neb::actor::desc desc;
	desc.type = neb::actor::RIGID_STATIC;

	desc.load(el_actor);

	return Create_Rigid_Static(desc, parent);
}
neb::scene::rigid_dynamic_t	neb::scene::Create_Rigid_Dynamic(neb::actor::desc desc, neb::scene::base_t parent) {

	printf("%s\n", __PRETTY_FUNCTION__);

	// create
	std::shared_ptr<neb::actor::Rigid_Dynamic> actor(new neb::actor::Rigid_Dynamic);

	actor->desc_ = desc;

	actor->pose_ = desc.pose.to_math();

	actor->velocity_ = math::vec3(
			desc.velocity.x,
			desc.velocity.y,
			desc.velocity.z
			);

	actor->density_ = desc.density;


	// PxMaterial
	physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);

	physx::PxRigidDynamic* px_rigid_dynamic =
		neb::__physics.px_physics_->createRigidDynamic( actor->pose_ );

	if (!px_rigid_dynamic)
	{
		printf("create shape failed!");
		exit(1);
	}
	
	// PxShape
	actor->px_shape_ = px_rigid_dynamic->createShape( *(desc.shape.to_geo()), *px_mat );
	
	
	
	px_rigid_dynamic->setLinearVelocity(actor->velocity_, true);


	physx::PxRigidBodyExt::updateMassAndInertia(*px_rigid_dynamic, desc.density);

	// PxActor
	actor->px_actor_ = px_rigid_dynamic;

	// userData
	px_rigid_dynamic->userData = actor.get();

	//printf("box=%p\n",box);

	// add PxActor to PxScene
	px_scene_->addActor(*px_rigid_dynamic);

	// init actor
	actor->scene_ = shared_from_this();
	actor->shape_ = desc.shape;
	actor->init();
	
	actor->setupFiltering(
			desc.filter_group,
			desc.filter_mask
			);

	add_actor(actor);

	if(parent)
	{
		parent->actors_.push_back(actor->i_);
	}

	return actor;
}
std::shared_ptr<neb::actor::Rigid_Static>		neb::scene::Create_Rigid_Static(neb::actor::desc desc, neb::scene::base_t parent) {

	printf("%s\n", __PRETTY_FUNCTION__);

	// create
	std::shared_ptr<neb::actor::Rigid_Static> actor(new neb::actor::Rigid_Static);

	actor->desc_ = desc;

	actor->pose_ = desc.pose.to_math();
	
	// PxMaterial
	printf("create material\n");
	physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);

	printf("create px actor\n");
	physx::PxRigidStatic* px_rigid_static =
		neb::__physics.px_physics_->createRigidStatic( actor->pose_ );

	if(px_rigid_static == NULL)
	{
		printf("create actor failed!");
		exit(1);
	}

	// PxShape
	printf("create shape\n");
	actor->px_shape_ = px_rigid_static->createShape( *(desc.shape.to_geo()), *px_mat );
	
	// PxActor
	actor->px_actor_ = px_rigid_static;
	
	// userData
	px_rigid_static->userData = actor.get();

	//printf("box=%p\n",box);
	
	// add PxActor to PxScene
	assert(px_scene_ != NULL);
	printf("add actor\n");
	px_scene_->addActor(*px_rigid_static);
	printf("add actor\n");

	// init actor
	actor->shape_ = desc.shape;
	actor->init();
	
	printf("setup filtering\n");
	actor->setupFiltering(desc.filter_group, desc.filter_mask);
	
	add_actor(actor);
	if(parent)
	{
		parent->actors_.push_back(actor->i_);
	}
	
	printf("return\n");
	return actor;
}
std::shared_ptr<neb::actor::Rigid_Static>	neb::scene::Create_Rigid_Static_Plane(tinyxml2::XMLElement* el_actor, neb::scene::base_t) {
	printf("%s\n", __PRETTY_FUNCTION__);

	// create
	std::shared_ptr<neb::actor::Rigid_Static> actor(new neb::actor::Rigid_Static);

	// xml
	math::vec3 n = math::xml_parse_vec3(el_actor->FirstChildElement("n"));
	float d = math::xml_parse_float(el_actor->FirstChildElement("d"));

	n.normalize();

	printf("n=%f,%f,%f\n", n.x, n.y, n.z);
	printf("d=%f\n", d);

	// PxMaterial
	physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);

	// construct global pose for rendering
	//physx::PxQuat q(n.x, n.y, n.z, 0.0f);
	math::quat q(3.14f, math::vec3(1,0,0));


	math::transform pose(n * -1.0f * d, q);

	actor->pose_ = pose;

	printf("%f,%f,%f\n", pose.p.x, pose.p.y, pose.p.z);

	physx::PxPlane p(physx::PxVec3(n.x,n.y,n.z), d);

	// PxActor
	physx::PxRigidStatic* px_rigid_static = PxCreatePlane(*(neb::__physics.px_physics_), p, *px_mat);

	if (!px_rigid_static)
	{
		printf("create shape failed!");
		exit(1);
	}

	actor->px_actor_ = px_rigid_static;

	// userData
	px_rigid_static->userData = actor.get();

	//printf("box=%p\n",box);


	// add PxActor to PxScene
	px_scene_->addActor(*px_rigid_static);

	add_actor(actor);

	return actor;
}
std::shared_ptr<neb::actor::Controller>			neb::scene::Create_Controller(tinyxml2::XMLElement* el_actor){
	printf("%s\n",__FUNCTION__);

	//jess::scoped_ostream( &jess::clog, neb_FUNCSIG );
	math::vec3 p = math::xml_parse_vec3(el_actor->FirstChildElement("p"));	
	// create
	std::shared_ptr<neb::actor::Controller> actor(new neb::actor::Controller);

	physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);

	// description 
	physx::PxExtendedVec3 position(p.x, p.y, p.z);

	physx::PxCapsuleControllerDesc desc;

	desc.position = position;
	desc.height = 1.0;
	desc.radius = 0.5;
	desc.scaleCoeff = 1.0;
	desc.volumeGrowth = 2.0;
	desc.density = 1000.0;
	desc.slopeLimit = 0.707;
	desc.stepOffset = 1.0;
	desc.contactOffset = 1.0;
	desc.material = px_mat;
	desc.climbingMode = physx::PxCapsuleClimbingMode::eEASY;
	desc.userData = actor.get();


	actor->px_controller_ = neb::__physics.px_character_controller_manager_->createController(
			*neb::__physics.px_physics_, px_scene_, desc );

	return actor;
}

void createVehicle4WSimulationData(
		const PxF32 chassisMass,
		PxConvexMesh* chassisConvexMesh,
		const PxF32 wheelMass,
		PxConvexMesh** wheelConvexMeshes,
		const PxVec3* wheelCentreOffsets,
		PxVehicleWheelsSimData& wheelsData,
		PxVehicleDriveSimData4W& driveData, 
		PxVehicleChassisData& chassisData)
{
	//Extract the chassis AABB dimensions from the chassis convex mesh.
	const PxVec3 chassisDims=computeChassisAABBDimensions(chassisConvexMesh);

	//The origin is at the center of the chassis mesh.
	//Set the center of mass to be below this point and a little towards the front.
	const PxVec3 chassisCMOffset=PxVec3(0.0f,-chassisDims.y*0.5f+0.65f,0.25f);

	//Now compute the chassis mass and moment of inertia.
	//Use the moment of inertia of a cuboid as an approximate value for the chassis moi.
	PxVec3 chassisMOI
		((chassisDims.y*chassisDims.y + chassisDims.z*chassisDims.z)*chassisMass/12.0f,
		 (chassisDims.x*chassisDims.x + chassisDims.z*chassisDims.z)*chassisMass/12.0f,
		 (chassisDims.x*chassisDims.x + chassisDims.y*chassisDims.y)*chassisMass/12.0f);
	//A bit of tweaking here.  The car will have more responsive turning if we reduce the
	//y-component of the chassis moment of inertia.
	chassisMOI.y*=0.8f;

	//Let's set up the chassis data structure now.
	chassisData.mMass=chassisMass;
	chassisData.mMOI=chassisMOI;
	chassisData.mCMOffset=chassisCMOffset;

	//Work out the front/rear mass split from the cm offset.
	//This is a very approximate calculation with lots of assumptions.
	//massRear*zRear + massFront*zFront = mass*cm           (1)
	//massRear       + massFront        = mass                      (2)
	//Rearrange (2)
	//massFront = mass - massRear                                           (3)
	//Substitute (3) into (1)
	//massRear(zRear - zFront) + mass*zFront = mass*cm      (4)
	//Solve (4) for massRear
	//massRear = mass(cm - zFront)/(zRear-zFront)           (5)
	//Now we also have
	//zFront = (z-cm)/2                                                                     (6a)
	//zRear = (-z-cm)/2                                                                     (6b)
	//Substituting (6a-b) into (5) gives
	//massRear = 0.5*mass*(z-3cm)/z                                         (7)
	const PxF32 massRear=0.5f*chassisMass*(chassisDims.z-3*chassisCMOffset.z)/chassisDims.z;
	const PxF32 massFront=chassisMass-massRear;

	//Extract the wheel radius and width from the wheel convex meshes.
	PxF32 wheelWidths[4];
	PxF32 wheelRadii[4];
	computeWheelWidthsAndRadii(wheelConvexMeshes,wheelWidths,wheelRadii);

	//Now compute the wheel masses and inertias components around the axle's axis.
	//http://en.wikipedia.org/wiki/List_of_moments_of_inertia
	PxF32 wheelMOIs[4];
	for(PxU32 i=0;i<4;i++)
	{
		wheelMOIs[i]=0.5f*wheelMass*wheelRadii[i]*wheelRadii[i];
	}
	//Let's set up the wheel data structures now with radius, mass, and moi.
	PxVehicleWheelData wheels[4];
	for(PxU32 i=0;i<4;i++)
	{
		wheels[i].mRadius=wheelRadii[i];
		wheels[i].mMass=wheelMass;
		wheels[i].mMOI=wheelMOIs[i];
		wheels[i].mWidth=wheelWidths[i];
	}
	//Disable the handbrake from the front wheels and enable for the rear wheels
	wheels[PxVehicleDrive4W::eFRONT_LEFT_WHEEL].mMaxHandBrakeTorque=0.0f;
	wheels[PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].mMaxHandBrakeTorque=0.0f;
	wheels[PxVehicleDrive4W::eREAR_LEFT_WHEEL].mMaxHandBrakeTorque=4000.0f;
	wheels[PxVehicleDrive4W::eREAR_RIGHT_WHEEL].mMaxHandBrakeTorque=4000.0f;
	//Enable steering for the front wheels and disable for the front wheels.
	wheels[PxVehicleDrive4W::eFRONT_LEFT_WHEEL].mMaxSteer=PxPi*0.3333f;
	wheels[PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].mMaxSteer=PxPi*0.3333f;
	wheels[PxVehicleDrive4W::eREAR_LEFT_WHEEL].mMaxSteer=0.0f;
	wheels[PxVehicleDrive4W::eREAR_RIGHT_WHEEL].mMaxSteer=0.0f;

	//Let's set up the tire data structures now.
	//Put slicks on the front tires and wets on the rear tires.
	PxVehicleTireData tires[4];
	tires[PxVehicleDrive4W::eFRONT_LEFT_WHEEL].mType=TIRE_TYPE_SLICKS;
	tires[PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].mType=TIRE_TYPE_SLICKS;
	tires[PxVehicleDrive4W::eREAR_LEFT_WHEEL].mType=TIRE_TYPE_WETS;
	tires[PxVehicleDrive4W::eREAR_RIGHT_WHEEL].mType=TIRE_TYPE_WETS;

	//Let's set up the suspension data structures now.
	PxVehicleSuspensionData susps[4];
	for(PxU32 i=0;i<4;i++)
	{
		susps[i].mMaxCompression=0.3f;
		susps[i].mMaxDroop=0.1f;
		susps[i].mSpringStrength=35000.0f;
		susps[i].mSpringDamperRate=4500.0f;
	}
	susps[PxVehicleDrive4W::eFRONT_LEFT_WHEEL].mSprungMass=massFront*0.5f;
	susps[PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].mSprungMass=massFront*0.5f;
	susps[PxVehicleDrive4W::eREAR_LEFT_WHEEL].mSprungMass=massRear*0.5f;
	susps[PxVehicleDrive4W::eREAR_RIGHT_WHEEL].mSprungMass=massRear*0.5f;

	//We need to set up geometry data for the suspension, wheels, and tires.
	//We already know the wheel centers described as offsets from the rigid body centre of mass.
	//From here we can approximate application points for the tire and suspension forces.
	//Lets assume that the suspension travel directions are absolutely vertical.
	//Also assume that we apply the tire and suspension forces 30cm below the centre of mass.
	PxVec3 suspTravelDirections[4]={PxVec3(0,-1,0),PxVec3(0,-1,0),PxVec3(0,-1,0),PxVec3(0,-1,0)};
	PxVec3 wheelCentreCMOffsets[4];
	PxVec3 suspForceAppCMOffsets[4];
	PxVec3 tireForceAppCMOffsets[4];
	for(PxU32 i=0;i<4;i++)
	{
		wheelCentreCMOffsets[i]=wheelCentreOffsets[i]-chassisCMOffset;
		suspForceAppCMOffsets[i]=PxVec3(wheelCentreCMOffsets[i].x,-0.3f,wheelCentreCMOffsets[i].z);
		tireForceAppCMOffsets[i]=PxVec3(wheelCentreCMOffsets[i].x,-0.3f,wheelCentreCMOffsets[i].z);
	}

	//Now add the wheel, tire and suspension data.
	for(PxU32 i=0;i<4;i++)
	{
		wheelsData.setWheelData(i,wheels[i]);
		wheelsData.setTireData(i,tires[i]);
		wheelsData.setSuspensionData(i,susps[i]);
		wheelsData.setSuspTravelDirection(i,suspTravelDirections[i]);
		wheelsData.setWheelCentreOffset(i,wheelCentreCMOffsets[i]);
		wheelsData.setSuspForceAppPointOffset(i,suspForceAppCMOffsets[i]);
		wheelsData.setTireForceAppPointOffset(i,tireForceAppCMOffsets[i]);
	}

	//Now set up the differential, engine, gears, clutch, and ackermann steering.

	//Diff
	PxVehicleDifferential4WData diff;
	diff.mType=PxVehicleDifferential4WData::eDIFF_TYPE_LS_4WD;
	driveData.setDiffData(diff);

	//Engine
	PxVehicleEngineData engine;
	engine.mPeakTorque=500.0f;
	engine.mMaxOmega=600.0f;//approx 6000 rpm
	driveData.setEngineData(engine);

	//Gears
	PxVehicleGearsData gears;
	gears.mSwitchTime=0.5f;
	driveData.setGearsData(gears);

	//Clutch
	PxVehicleClutchData clutch;
	clutch.mStrength=10.0f;
	driveData.setClutchData(clutch);

	//Ackermann steer accuracy
	PxVehicleAckermannGeometryData ackermann;
	ackermann.mAccuracy=1.0f;
	ackermann.mAxleSeparation =
		wheelCentreOffsets[PxVehicleDrive4W::eFRONT_LEFT_WHEEL].z -
		wheelCentreOffsets[PxVehicleDrive4W::eREAR_LEFT_WHEEL].z;

	ackermann.mFrontWidth =
		wheelCentreOffsets[PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].x -
		wheelCentreOffsets[PxVehicleDrive4W::eFRONT_LEFT_WHEEL].x;

	ackermann.mRearWidth =
		wheelCentreOffsets[PxVehicleDrive4W::eREAR_RIGHT_WHEEL].x -
		wheelCentreOffsets[PxVehicleDrive4W::eREAR_LEFT_WHEEL].x;

	driveData.setAckermannGeometryData(ackermann);
}

std::shared_ptr<neb::actor::vehicle>	Create_Vehicle() {

	PxVehicleWheelsSimData* wheelsSimData=PxVehicleWheelsSimData::allocate(4);
	PxVehicleDriveSimData4W driveSimData;

	PxVehicleChassisData chassisData;
	createVehicle4WSimulationData
		(chassisMass,chassisConvexMesh,
		 20.0f,wheelConvexMeshes4,wheelCentreOffsets4,
		 *wheelsSimData,driveSimData,chassisData);

PxRigidDynamic* vehActor=createVehicleActor4W(chassisData,wheelConvexMeshes4,chassisConvexMesh,scene,physics,material);

PxVehicleDrive4W* car = PxVehicleDrive4W::allocate(4);
car->setup(&physics,vehActor,*wheelsSimData,driveSimData,0);

//Set up the mapping between wheel and actor shape.
car->setWheelShapeMapping(0,0);
car->setWheelShapeMapping(1,1);
car->setWheelShapeMapping(2,2);
car->setWheelShapeMapping(3,3);

//Set up the scene query filter data for each suspension line.
PxFilterData vehQryFilterData;
SampleVehicleSetupVehicleShapeQueryFilterData(&vehQryFilterData);
car->setSceneQueryFilterData(0, vehQryFilterData);
car->setSceneQueryFilterData(1, vehQryFilterData);
car->setSceneQueryFilterData(2, vehQryFilterData);
car->setSceneQueryFilterData(3, vehQryFilterData);







}
void							neb::scene::step(double time){
	printf("%s\n",__PRETTY_FUNCTION__);

	switch(user_type_)
	{
		case neb::scene::LOCAL:
			step_local(time);
			break;
		case neb::scene::REMOTE:
			step_remote(time);
			break;
		default:
			printf("invlaid scene user type\n");
			exit(0);
	}
}
void							neb::scene::step_local(double time){
	printf("%s\n",__PRETTY_FUNCTION__);

	double dt = time - last_;
	last_ = time;

	//physx::PxU32 nbPxactor = px_scene_->getNbActors(physx::PxActorTypeSelectionFlag::eRIGID_DYNAMIC);

	// forces
	actors_.foreach<neb::actor::Base>(std::bind(&neb::actor::Base::add_force, std::placeholders::_1));

	// PxScene
	px_scene_->simulate(dt);
	px_scene_->fetchResults(true);

	// retrieve array of actors that moved
	physx::PxU32 nb_active_transforms;
	physx::PxActiveTransform* active_transforms = px_scene_->getActiveTransforms(nb_active_transforms);

	//printf( "count PxRigidActor:%i count active transform:%i\n", nbPxactor, nb_active_transforms );

	//physx::PxTransform pose;
	math::transform pose;

	// update each render object with the new transform
	for ( physx::PxU32 i = 0; i < nb_active_transforms; ++i )
	{
		//physx::PxActor* px_actor = active_transforms[i].actor;

		//printf( "actor type = %i\n", px_actor->getType() );

		physx::PxActor* pxactor = active_transforms[i].actor;

		neb::actor::Actor* actor = static_cast<neb::actor::Actor*>( active_transforms[i].userData );

		//neb_ASSERT( act );
		if(actor != NULL)
		{
			pose = active_transforms[i].actor2World;
			actor->set_pose(pose);


			physx::PxRigidBody* pxrigidbody = pxactor->isRigidBody();
			if(pxrigidbody != NULL)
			{
				neb::actor::Rigid_Body* rigidbody = dynamic_cast<neb::actor::Rigid_Body*>(actor);

				rigidbody->velocity_ = pxrigidbody->getLinearVelocity();
			}
		}
		//printf("transform.p.y=%16f\n",activeTransforms[i].actor2World.p.y);
	}

	assert(simulation_callback_);

	auto it = simulation_callback_->actors_to_delete_.begin();
	while(it != simulation_callback_->actors_to_delete_.end())
	{
		int i = *it;

		remove_actor(i);

		simulation_callback_->actors_to_delete_.erase(it);
	}
}
void							neb::scene::step_remote(double time){
	printf("%s\n",__PRETTY_FUNCTION__);

	// send
	actors_.foreach<neb::actor::Base>(std::bind(
				&neb::actor::Base::step_remote,
				std::placeholders::_1,
				time));
	//neb::packet p;

	//p.af.i = ;

	// receive
}
int	neb::scene::send() {

	auto app = get_app();

	assert(app->server_);
	assert(app->server_->clients_.size() > 0);

	auto client = app->server_->clients_.at(0);
	assert(client);


	neb::packet::packet p;
	p.type = neb::packet::type::SCENE;

	int i = 0;
	for(auto it = actors_.map_.begin(); it != actors_.map_.end(); ++it)
	{
		auto actor = std::dynamic_pointer_cast<neb::actor::Base>(it->second);

		p.scene.desc[i] = actor->get_desc();
	}	



	return 0;
}
int	neb::scene::recv(neb::packet::packet p) {


	return 0;
}





