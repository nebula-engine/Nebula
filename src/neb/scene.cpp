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
#include <neb/actor/vehicle.h>
#include <neb/shape.h>




neb::scene::scene(): px_filter_shader_(NULL), px_scene_(NULL) {
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


	// PxActor
	physx::PxRigidDynamic* px_rigid_dynamic =
		neb::__physics.px_physics_->createRigidDynamic( actor->pose_ );
	
	if (!px_rigid_dynamic)
	{
		printf("create shape failed!");
		exit(1);
	}
	
	actor->px_actor_ = px_rigid_dynamic;

	// PxShape
	actor->create_shapes();
	
	
	px_rigid_dynamic->setLinearVelocity(actor->velocity_, true);


	physx::PxRigidBodyExt::updateMassAndInertia(*px_rigid_dynamic, desc.density);

	// userData
	px_rigid_dynamic->userData = actor.get();

	//printf("box=%p\n",box);

	// add PxActor to PxScene
	px_scene_->addActor(*px_rigid_dynamic);

	// init actor
	actor->scene_ = shared_from_this();
	actor->init();

	actor->setupFiltering();

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

	// PxActor
	physx::PxRigidStatic* px_rigid_static =
		neb::__physics.px_physics_->createRigidStatic( actor->pose_ );

	if(px_rigid_static == NULL)
	{
		printf("create actor failed!");
		exit(1);
	}
	
	actor->px_actor_ = px_rigid_static;

	// PxShape
	actor->create_shapes();
	
	// userData
	px_rigid_static->userData = actor.get();

	//printf("box=%p\n",box);

	// add PxActor to PxScene
	assert(px_scene_ != NULL);
	printf("add actor\n");
	px_scene_->addActor(*px_rigid_static);
	printf("add actor\n");

	// init actor
	actor->init();

	printf("setup filtering\n");
	actor->setupFiltering();

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
neb::scene::vehicle_t neb::scene::create_vehicle() {
	
	neb::actor::desc desc;
	desc.reset();
	
	glutpp::shape_desc sd;
	
	sd.box(math::vec3(3,1,6));
	desc.add_shape(sd);
	
	sd.box(math::vec3(0.5,1,1));
	desc.add_shape(sd);
	desc.add_shape(sd);
	desc.add_shape(sd);
	desc.add_shape(sd);
	
	
	neb::scene::vehicle_t vehicle;
	
	vehicle = vehicle_manager_.create_vehicle(
		neb::__physics.px_physics_,
		px_scene_,
		desc);
	

	add_actor(vehicle);
	
	return vehicle;
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

	// vehicle
	//physx::PxVec3 g(0,-0.25,0);
	//vehicle_manager_.vehicle_suspension_raycasts(px_scene_);
	//vehicle_manager_.update((float)dt, g);
	
	// delete actors
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





