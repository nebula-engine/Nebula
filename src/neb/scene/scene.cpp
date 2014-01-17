#include <math/free.h>

#include <neb/config.h>
#include <neb/app.h>
#include <glutpp/actor/desc.h>
#include <neb/physics.h>
#include <neb/scene/scene.h>
#include <glutpp/scene/desc.h>
#include <neb/simulation_callback.h>
#include <neb/actor/free.h>
#include <neb/actor/Base.h>
#include <neb/actor/Rigid_Dynamic.h>
#include <neb/actor/Rigid_Static.h>
#include <neb/actor/Controller.h>
#include <neb/actor/vehicle.h>
#include <neb/actor/empty.h>
#include <neb/shape.h>

#include <glutpp/network/message.h>

neb::scene::scene::scene(neb::app_s app):
	app_(app),
	px_filter_shader_(NULL),
	px_scene_(NULL)
{
	NEBULA_DEBUG_0_FUNCTION;
	
	assert(app);
}
void neb::scene::scene::init(glutpp::scene::desc_s desc) {

	NEBULA_DEBUG_0_FUNCTION;
	
	create_physics();

	create_actors(desc);
}
std::shared_ptr<neb::app> neb::scene::scene::get_app() {

	assert(!app_.expired());

	return app_.lock();
}
neb::actor::Base_s neb::scene::scene::get_actor(int i) {
	auto it = actors_.find(i);
	neb::actor::Base_s a;
	if(it == actors_.end())
	{
		return a;
	}
	else
	{
		a = std::dynamic_pointer_cast<neb::actor::Base>(it->second);
		assert(a);
		return a;
	}
}
neb::actor::Base_s neb::scene::scene::get_actor(glutpp::actor::addr_s addr) {
	
	neb::actor::Base_s actor;
	
	auto vec = addr->get_vec();
	assert(vec);
	
	if(vec->vec_.empty()) return actor;
	
	int i = vec->vec_.front();
	vec->vec_.pop_front();
	
	actor = get_actor(i);
	
	if(!actor) return actor;
	
	
	if(!vec->vec_.empty())
	{
		return actor->get_actor(addr);
	}
	
	return actor;
}
void neb::scene::scene::create_actors(glutpp::scene::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;

	assert(desc);

	for(auto it = desc->get_actors()->vec_.begin(); it != desc->get_actors()->vec_.end(); ++it)
	{
		auto ad = std::get<0>(*it);

		switch(ad->get_raw()->mode_)
		{
			case glutpp::actor::mode::NOW:
				printf("NOW\n");
				create_actor_local(ad);
				break;
			case glutpp::actor::mode::DEFERRED:
				printf("DEFERRED\n");
				add_deferred(ad);
				break;
			default:
				printf("invalid mode\n");
				abort();
		}
	}
}
void neb::scene::scene::add_deferred(glutpp::actor::desc_s ad) {
	NEBULA_DEBUG_0_FUNCTION;


	assert(ad);

	char* n = ad->get_raw()->name_;
	assert(n);

	int len = strlen(n);

	char* name = new char[len + 1];

	memcpy(name, n, len);

	name[len] = 0;

	actors_deferred_[name] = ad;


}
neb::actor::Base_s neb::scene::scene::create_actor(glutpp::actor::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;

	auto me = std::dynamic_pointer_cast<neb::scene::scene>(shared_from_this());

	std::shared_ptr<neb::actor::Base> actor;

	switch(desc->get_raw()->type_)
	{
		case glutpp::actor::RIGID_DYNAMIC:
			actor.reset(new neb::actor::Rigid_Dynamic(me));
			// = Create_Rigid_Dynamic(ad);
			break;
		case glutpp::actor::RIGID_STATIC:
			actor.reset(new neb::actor::Rigid_Static(me));
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
			actor.reset(new neb::actor::empty(me));
			break;
		default:
			abort();
	}

	actor->init(desc);

	return actor;	
}
neb::actor::Base_s neb::scene::scene::create_actor_local(glutpp::actor::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;

	auto actor = create_actor(desc);

	actors_.push_back(actor);

	// network

	auto app = get_app();

	gal::network::message_s msg(new gal::network::message);

	int type = glutpp::network::type::ACTOR_CREATE;
	msg->write(&type, sizeof(int));

	std::shared_ptr<glutpp::network::actor::create> actor_create(new glutpp::network::actor::create);

	actor_create->load(actor);
	actor_create->write(msg);

	app->send_server(msg);

	return actor;	
}
neb::actor::Base_s neb::scene::scene::create_actor_remote(
		glutpp::actor::addr_s addr,
		glutpp::actor::desc_s desc)
{
	NEBULA_DEBUG_0_FUNCTION;

	auto actor = get_actor(addr);
	
	if(actor)
	{
		actor = actor->create_actor_remote(addr, desc);
	}
	else
	{
		int i = desc->get_id()->i_;
		actor = create_actor(desc);
		
		actors_[i] = actor;
	}

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
void neb::scene::scene::create_physics() {
	printf("%s\n",__PRETTY_FUNCTION__);

	auto pxphysics = neb::__physics.px_physics_;

	physx::PxSceneDesc scene_desc(pxphysics->getTolerancesScale());

	scene_desc.gravity = raw_.gravity_;

	scene_desc.flags |= physx::PxSceneFlag::eENABLE_ACTIVETRANSFORMS;

	int m_nbThreads = 1;

	// cpu dispatcher
	printf("cpu dispatcher\n");
	if( !scene_desc.cpuDispatcher )
	{
		physx::PxDefaultCpuDispatcher* cpuDispatcher =
			::physx::PxDefaultCpuDispatcherCreate( m_nbThreads );

		assert( cpuDispatcher );

		scene_desc.cpuDispatcher = cpuDispatcher;
	}

	// filter shader
	printf("filter shader\n");
	if(!scene_desc.filterShader)
	{
		if(px_filter_shader_)
		{
			scene_desc.filterShader = px_filter_shader_;
		}
		else
		{
			scene_desc.filterShader = DefaultFilterShader;
		}
	}

	// gpu dispatcher
	printf("gpu dispatcher\n");
#ifdef PX_WINDOWS
	if( !scene_desc.gpuDispatcher && m_cudaContextManager )
	{
		sceneDesc.gpuDispatcher = m_cudaContextManager->getGpuDispatcher();
	}
#endif
	assert( scene_desc.isValid() );

	px_scene_ = pxphysics->createScene(scene_desc);
	assert(px_scene_);

	// simulation callback
	neb::simulation_callback* sec = new neb::simulation_callback;
	simulation_callback_ = sec;
	px_scene_->setSimulationEventCallback(sec);
}
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

	// step actors
	actors_.foreach<neb::actor::Base>(std::bind(
				&neb::actor::Base::step,
				std::placeholders::_1,
				time));


	// cleanup
	auto it = actors_.map_.begin();
	while(it != actors_.map_.end())
	{
		std::shared_ptr<glutpp::actor::actor> actor = it->second;

		assert(actor);

		actor->cleanup();

		if(actor->any(glutpp::light::light::flag::SHOULD_DELETE)) {
			actor->release();

			it = actors_.map_.erase(it);
		}
		else {
			++it;
		}
	}

	// extras
	//printf("desc size = %i\n", (int)desc_size());

}
void neb::scene::scene::step_local(double time) {
	NEBULA_DEBUG_1_FUNCTION;

	auto app = get_app();

	double dt = time - last_;
	last_ = time;

	// timer
	timer_set_.step(time);

	//physx::PxU32 nbPxactor = px_scene_->getNbActors(physx::PxActorTypeSelectionFlag::eRIGID_DYNAMIC);



	// PxScene
	assert(px_scene_ != NULL);

	px_scene_->simulate(dt);
	px_scene_->fetchResults(true);

	// retrieve array of actors that moved
	physx::PxU32 nb_active_transforms;
	physx::PxActiveTransform* active_transforms = px_scene_->getActiveTransforms(nb_active_transforms);

	//printf( "count PxRigidActor:%i count active transform:%i\n", nbPxactor, nb_active_transforms );

	//physx::PxTransform pose;
	math::transform pose;

	// update each render object with the new transform
	for(physx::PxU32 i = 0; i < nb_active_transforms; ++i) {
		//physx::PxActor* px_actor = active_transforms[i].actor;

		//printf( "actor type = %i\n", px_actor->getType() );

		physx::PxActor* pxactor = active_transforms[i].actor;

		assert(pxactor);

		void* ud = active_transforms[i].userData;
		assert(ud);



		neb::actor::Actor* actor = dynamic_cast<neb::actor::Actor*>((glutpp::actor::actor*)ud);

		assert(actor);

		pose = active_transforms[i].actor2World;
		actor->set_pose(pose);

		physx::PxRigidBody* pxrigidbody = pxactor->isRigidBody();
		if(pxrigidbody != NULL)
		{
			neb::actor::rigid_body::rigid_body* rigidbody =
				dynamic_cast<neb::actor::rigid_body::rigid_body*>(actor);

			assert(rigidbody != NULL);

			math::vec3 v(pxrigidbody->getLinearVelocity());

			rigidbody->raw_.velocity_ = v;

			//v.print();
		}

		actor->set(glutpp::actor::flag::SHOULD_UPDATE);
	}

	// vehicle
	//physx::PxVec3 g(0,-0.25,0);
	//vehicle_manager_.vehicle_suspension_raycasts(px_scene_);
	//vehicle_manager_.update((float)dt, g);

	send_actor_update();
}
void neb::scene::scene::send_actor_update() {
	printf("DEBUG: message ACTOR_UPDATE sent\n");

	gal::network::message_s msg(new gal::network::message);

	int type = glutpp::network::type::ACTOR_UPDATE;
	msg->write(&type, sizeof(int));

	glutpp::network::actor::update actor_update;

	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		auto actor = it->second;

		actor_update.load(actor);
	}

	actor_update.write(msg);

	get_app()->send_server(msg);
}
void neb::scene::scene::step_remote(double time){
	NEBULA_DEBUG_1_FUNCTION;

	// send
	actors_.foreach<neb::actor::Base>(std::bind(
				&neb::actor::Base::step_remote,
				std::placeholders::_1,
				time));
	//neb::packet p;

	//p.af.i = ;

	// receive
}









