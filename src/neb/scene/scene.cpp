#include <math/free.h>

#include <neb/config.h>
#include <neb/app.h>
#include <glutpp/actor/desc.h>
#include <neb/packet/packet.h>
#include <neb/physics.h>
#include <neb/scene/scene.h>
#include <neb/simulation_callback.h>
#include <neb/actor/free.h>
#include <neb/actor/Base.h>
#include <neb/actor/Rigid_Dynamic.h>
#include <neb/actor/Rigid_Static.h>
#include <neb/actor/Controller.h>
#include <neb/actor/vehicle.h>
#include <neb/actor/empty.h>
#include <neb/shape.h>



neb::scene::scene::scene(): px_filter_shader_(NULL), px_scene_(NULL) {

	NEBULA_DEBUG_0_FUNCTION;
}
void neb::scene::scene::init() {
	
	NEBULA_DEBUG_0_FUNCTION;
	
	create_actors();
}
std::shared_ptr<neb::app> neb::scene::scene::get_app() {

	assert(!app_.expired());

	return app_.lock();
}
void neb::scene::scene::create_actors() {

	NEBULA_DEBUG_0_FUNCTION;
	
	assert(desc_);
	
	for(auto it = desc_->actors_.begin(); it != desc_->actors_.end(); ++it)
	{
		create_actor(*it);
	}
}
neb::actor::Base_shared neb::scene::scene::create_actor(glutpp::actor::desc* ad) {

	NEBULA_DEBUG_0_FUNCTION;
	
	auto me = std::dynamic_pointer_cast<neb::scene::scene>(shared_from_this());
	
	std::shared_ptr<neb::actor::Base> actor;
	
	switch(ad->raw_.type_)
	{
		case glutpp::actor::RIGID_DYNAMIC:
			actor.reset(new neb::actor::Rigid_Dynamic(ad, me));
			// = Create_Rigid_Dynamic(ad);
			break;
		case glutpp::actor::RIGID_STATIC:
			actor.reset(new neb::actor::Rigid_Static(ad, me));
			// = Create_Rigid_Static(ad);
			break;
		case glutpp::actor::PLANE:
			//actor = Create_Rigid_Static_Plane(ad);
			printf("not implemented\n");
			abort();
			break;
		case glutpp::actor::CONTROLLER:
			printf("not implemented\n");
			abort();
			//actor = Create_Controller(ad);
			break;
		case glutpp::actor::EMPTY:
			actor.reset(new neb::actor::empty(ad, me));
			break;
		default:
			abort();
	}
	
	actor->init();
	
	actors_.push(actor);
	
	return actor;	
}
/*

*/
/*
neb::scene::scene::rigid_static_t neb::scene::scene::Create_Rigid_Static_Plane(
		glutpp::actor::desc* ad,
		neb::scene::scene::base_t) {

	printf("%s\n", __PRETTY_FUNCTION__);

	// create
	std::shared_ptr<neb::actor::Rigid_Static> actor(new neb::actor::Rigid_Static);
	
	// PxMaterial
	physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);


	actor->pose_ = ad->raw_.pose_.to_math();

	physx::PxPlane p(
			ad->raw_.n_.to_math(),
			ad->raw_.d_);

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

neb::scene::scene::controller_t neb::scene::scene::Create_Controller(neb::actor::desc* ad) {
	printf("%s\n",__FUNCTION__);

	//jess::scoped_ostream( &jess::clog, neb_FUNCSIG );
	// create
	std::shared_ptr<neb::actor::Controller> actor(new neb::actor::Controller);

	physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);

	// description
	math::vec3 p = ad->raw_.pose_.p.to_math();

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
neb::scene::scene::vehicle_t neb::scene::scene::create_vehicle() {

	neb::actor::desc* desc = new neb::actor::desc;
	//desc.raw_.reset();

	glutpp::shape::desc* sd = NULL;

	sd = new glutpp::shape::desc;
	sd->raw_.box(math::vec3(3,1,6));
	desc->shapes_.push_back(sd);

	sd = new glutpp::shape::desc;
	sd->raw_.box(math::vec3(0.5,1,1));
	desc->shapes_.push_back(sd);

	sd = new glutpp::shape::desc;
	sd->raw_.box(math::vec3(0.5,1,1));
	desc->shapes_.push_back(sd);

	sd = new glutpp::shape::desc;
	sd->raw_.box(math::vec3(0.5,1,1));
	desc->shapes_.push_back(sd);

	sd = new glutpp::shape::desc;
	sd->raw_.box(math::vec3(0.5,1,1));
	desc->shapes_.push_back(sd);


	neb::scene::scene::vehicle_t vehicle;

	vehicle = vehicle_manager_.create_vehicle(
			neb::__physics.px_physics_,
			px_scene_,
			desc);


	add_actor(vehicle);

	return vehicle;
}
*/
void neb::scene::scene::step(double time) {

	NEBULA_DEBUG_1_FUNCTION;

	switch(user_type_)
	{
		case neb::scene::scene::LOCAL:
			step_local(time);
			break;
		case neb::scene::scene::REMOTE:
			step_remote(time);
			break;
		default:
			printf("invlaid scene user type\n");
			exit(0);
	}
	
	// cleanup
	auto it = actors_.map_.begin();
	while(it != actors_.map_.end())
	{
		std::shared_ptr<glutpp::actor::actor> actor = it->second;
		
		assert(actor);
		
		actor->cleanup();
		
		
		if(actor->any(glutpp::light::light::flag::SHOULD_DELETE))
		{
			actor->release();
			
			actors_.map_.erase(it);
		}
		else
		{
			++it;
		}
	}
}
void							neb::scene::scene::step_local(double time){
	NEBULA_DEBUG_1_FUNCTION;

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
				neb::actor::Rigid_Body* rigidbody =
					dynamic_cast<neb::actor::Rigid_Body*>(actor);

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
	/*
	assert(simulation_callback_);
	auto it = simulation_callback_->actors_to_delete_.begin();
	while(it != simulation_callback_->actors_to_delete_.end())
	{
		int i = *it;

		remove_actor(i);

		simulation_callback_->actors_to_delete_.erase(it);
	}
	*/
}
void							neb::scene::scene::step_remote(double time){
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
gal::network::message::shared_t neb::scene::scene::serialize() {

	NEBULA_DEBUG_0_FUNCTION;

	gal::network::message::shared_t msg(new gal::network::message);

	int i = 0;
	for(auto it = actors_.map_.begin(); it != actors_.map_.end(); ++it)
	{
		printf("actor %i\n", i);

		assert(it->second);
		auto actor = std::dynamic_pointer_cast<neb::actor::Base>(it->second);
		assert(actor);

		printf("actor %i\n", i);

		neb::scene::desc sd;

		sd.actors_.push_back(actor->get_desc());

		printf("actor %i\n", i);

		i++;
	}	

	NEBULA_DEBUG_0_FUNCTION;

	return msg;
}
int	neb::scene::scene::recv(neb::packet::packet p) {


	return 0;
}





