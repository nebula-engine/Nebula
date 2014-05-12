#include <stdio.h>

#include <Nebula/Graphics/window/window.hpp>
#include <Nebula/renderable.hpp>
#include <Nebula/scene/desc.hpp>
#include <Nebula/scene/scene.hpp>
#include <Nebula/Actor/Base.hpp>

#include <Nebula/Graphics/light/light.hpp>
#include <Nebula/Graphics/glsl/program.hpp>
#include <Nebula/Graphics/Camera/Projection/Perspective.hpp>


Neb::Scene::scene::scene() {
	GLUTPP_DEBUG_0_FUNCTION;
}
Neb::Scene::scene::~scene() {
	GLUTPP_DEBUG_0_FUNCTION;
}
void Neb::Scene::scene::i(int ni) {
	GLUTPP_DEBUG_0_FUNCTION;

	//desc_->raw_.i_ = ni;
	//desc_->i_ = ni;
	i_ = ni;
}
int Neb::Scene::scene::i() {
	return i_;
}
unsigned int Neb::Scene::scene::f() {
	return raw_->flag_;
}
void Neb::Scene::scene::f(unsigned int flag) {
	raw_->flag_ = flag;
}
void Neb::Scene::scene::init(Neb::Scene::desc_s desc) {
	GLUTPP_DEBUG_0_FUNCTION;
	//renderable_ = renderable;
}
void Neb::Scene::scene::release() {
	GLUTPP_DEBUG_0_FUNCTION;	
}
physx::PxMat44		Neb::Scene::scene::get_pose() {
	return physx::PxMat44();
}
void Neb::Scene::scene::render(double time,
		std::shared_ptr<Neb::Camera::View::Base<float> > view,
		std::shared_ptr<Neb::Camera::Projection::Base> proj,
		Neb::window::window_s window) {

	GLUTPP_DEBUG_1_FUNCTION;

	assert(view);
	assert(proj);

	auto p = Neb::master::Global()->use_program(Neb::program_name::e::LIGHT);


	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	
	view->load();
	proj->load();

	int i = 0;
	for(auto it = actors_.map_.begin(); it != actors_.map_.end(); ++it)
	{
		it->second->load_lights(i, physx::PxMat44());
	}

	p->get_uniform_scalar("light_count")->load(i);

	//printf("%i\n",i);

	draw(window);
}
void Neb::Scene::scene::draw(Neb::window::window_s window) {

	GLUTPP_DEBUG_1_FUNCTION;

	for(auto it = actors_.map_.begin(); it != actors_.map_.end(); ++it)
	{
		it->second->draw(window, physx::PxMat44());
	}
}
void Neb::Scene::scene::resize(int w, int h) {
}




//#include <math/free.hpp>

#include <gru/actor/Type.hpp>
#include <gru/actor/addr.hpp>
#include <gru/actor/desc.hpp>
#include <gru/actor/event.hpp>
#include <gru/Message/Actor/Create.hpp>
#include <gru/Message/Actor/Update.hpp>
#include <gru/Message/Actor/Event.hpp>
#include <gru/scene/desc.hpp>
#include <gru/network/message.hpp>
#include <gru/Typed.hpp>
#include <gru/Memory/smart_ptr.hpp>

#include <nebula/config.hpp> // nebula/config.hpp.in
#include <nebula/app.hpp>
#include <nebula/physics.hpp>
#include <nebula/scene/scene.hpp>
#include <nebula/simulation_callback.hpp>
//#include <nebula/actor/free.hpp>
#include <nebula/actor/Base.hpp>
#include <nebula/actor/Rigid_Dynamic.hpp>
#include <nebula/actor/Rigid_Static.hpp>
#include <nebula/actor/Controller.hpp>
//#include <nebula/actor/vehicle.hpp>
#include <nebula/actor/empty.hpp>
#include <nebula/shape.hpp>
#include <nebula/timer/Types.hpp>
#include <nebula/timer/Actor/Release.hpp>



neb::scene::scene::scene(neb::app_s app):
	app_(app),
	user_type_(0),
	px_filter_shader_(NULL),
	simulation_callback_(NULL),
	px_scene_(NULL),
	last_(0)
{
	NEBULA_DEBUG_0_FUNCTION;
	
	assert(app);
}
void neb::scene::scene::init(boost::shared_ptr<glutpp::scene::desc> desc) {

	NEBULA_DEBUG_0_FUNCTION;
	
	create_physics();

	create_actors(desc);
}
Neb::weak_ptr<neb::app>			neb::scene::scene::get_app() {
	return app_;
}
physx::PxMat44				neb::scene::scene::getPose() {
	return physx::PxMat44();
}
physx::PxMat44		neb::scene::scene::getPoseGlobal() {
	return physx::PxMat44();
}
Neb::weak_ptr<neb::Actor::Base>		neb::scene::scene::get_actor(int i) {
	auto it = actors_.find(i);
	boost::shared_ptr<neb::Actor::Base> a;
	if(it == actors_.end())
	{
		return a;
	} else {
		a = boost::dynamic_pointer_cast<neb::Actor::Base>(it->second);
		assert(a);
		return a;
	}
}
Neb::weak_ptr<neb::Actor::Base>		neb::scene::scene::get_actor(boost::shared_ptr<glutpp::actor::addr> addr) {
	
	std::deque<int> vec = addr->vec_;
	assert(vec);
	
	assert(!vec.empty());
	//if(vec.empty()) return actor;
	
	int i = vec.front();
	vec.pop_front();
	
	auto actor = get_actor(i);
	
	//if(!actor) return actor;
	
	
	if(!vec.empty())
	{
		return actor->get_actor(addr);
	}
	
	return actor;
}
void neb::scene::scene::create_actors(boost::shared_ptr<glutpp::scene::desc> desc) {
	NEBULA_DEBUG_0_FUNCTION;
	
	assert(desc);
	
	for(auto it = desc->actors_.cbegin(); it != desc->actors_.cend(); ++it) {
		auto ad = *it;

		switch(ad->raw_wrapper_.ptr_->mode_create_) {
			case glutpp::actor::mode_create::NOW:
				printf("NOW\n");
				create_actor_local(ad);
				break;
			case glutpp::actor::mode_create::DEFERRED:
				printf("DEFERRED\n");
				add_deferred(ad);
				break;
			default:
				printf("invalid mode\n");
				abort();
		}
	}
}
void		neb::scene::scene::add_deferred(boost::shared_ptr<glutpp::actor::desc> ad) {
	NEBULA_DEBUG_0_FUNCTION;


	assert(ad);

	char* n = ad->raw_wrapper_.ptr_->name_;
	assert(n);

	int len = strlen(n);

	char* name = new char[len + 1];

	memcpy(name, n, len);

	name[len] = 0;

	actors_deferred_[name] = ad;
}
boost::shared_ptr<neb::Actor::Base>	neb::scene::scene::create_actor(boost::shared_ptr<glutpp::actor::desc> desc) {
	NEBULA_DEBUG_0_FUNCTION;
	
	auto me = boost::dynamic_pointer_cast<neb::scene::scene>(shared_from_this());

	long int hash_code = desc->raw_wrapper_.ptr_->type_.val_;
	Neb::unique_ptr<neb::Actor::Base> actor((neb::Actor::Base*)Neb::Factory<glutpp::actor::actor>::global()->alloc(hash_code));
	
	actor->init(desc);
	
	return boost::shared_ptr<neb::Actor::Base>();
}
Neb::weak_ptr<neb::Actor::Base>			neb::scene::scene::create_actor_local(boost::shared_ptr<glutpp::actor::desc> desc) {
	NEBULA_DEBUG_0_FUNCTION;

	auto actor = create_actor(desc);

	actors_.push_back(actor);

	// network
	
	auto app = get_app();

	boost::shared_ptr<gal::network::omessage> msg(new gal::network::omessage);

	int type = glutpp::network::type::ACTOR_CREATE;
	msg->write(&type, sizeof(int));
	
	//boost::shared_ptr<glutpp::network::actor::create> actor_create(new glutpp::network::actor::create);
	
	glutpp::network::actor::create actor_create;

	actor_create.load(actor);
	
	msg->ar_ << actor_create;
	
	//actor_create->write(msg);

	app->send_server(msg);

	return actor;	
}
Neb::weak_ptr<neb::Actor::Base>			neb::scene::scene::create_actor_remote(boost::shared_ptr<glutpp::actor::addr> addr, boost::shared_ptr<glutpp::actor::desc> desc) {
	NEBULA_DEBUG_0_FUNCTION;

	auto parent = get_actor(addr);

	Neb::weak_ptr<neb::Actor::Base> weak;
	
	if(parent) {
		weak = parent->create_actor_remote(addr, desc);
	} else {
		int i = desc->i_;
		//actor = create_actor(desc);


		auto me = boost::dynamic_pointer_cast<neb::scene::scene>(shared_from_this());

		long int hash_code = desc->raw_wrapper_.ptr_->type_.val_;

		Neb::unique_ptr<neb::Actor::Base> actor((neb::Actor::Base*)Neb::Factory<glutpp::actor::actor>::global()->alloc(hash_code));
		
		actor->init(desc);
		
		Neb::Map<glutpp::actor::actor>::value_type p;
		p.first = i;
		p.second.swap(actor);

		actors_.map_.insert(p);
		
		weak = actor;
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
std::shared_ptr<neb::Actor::Rigid_Static> actor(new neb::actor::Rigid_Static);

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

neb::scene::scene::controller_t neb::scene::scene::Create_Controller(neb::Actor::desc* ad) {
printf("%s\n",__FUNCTION__);

//jess::scoped_ostream( &jess::clog, neb_FUNCSIG );
// create
std::shared_ptr<neb::Actor::Controller> actor(new neb::actor::Controller);

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

	neb::Actor::desc* desc = new neb::actor::desc;
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

	scene_desc.gravity = raw_->gravity_;

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

	// cleanup
	/** @todo this will become obsolete if following procedure is used:
	 * when it is determined (inside or outside Actor) that an actor is to be destoryed, call
	 * @c parent.sig(i) when @c parent is the actor's parent and @c i is the actor's index
	 */
	auto it = actors_.map_.begin();
	while(it != actors_.map_.end()) {
		boost::shared_ptr<glutpp::actor::actor> actor = it->second;
		
		assert(actor);
		
		actor->cleanup();
		
		if(actor->any(glutpp::actor::actor::flag::e::SHOULD_RELEASE)) {
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
	//timer_set_.step(time);

	//physx::PxU32 nbPxactor = px_scene_->getNbActors(physx::PxActorTypeSelectionFlag::eRIGID_DYNAMIC);

	
	// step actors
	for(auto it = actors_.map_.cbegin(); it != actors_.map_.cend(); ++it) {
		it->second->step_local(time);
	}


	// PxScene
	assert(px_scene_ != NULL);

	px_scene_->simulate(dt);
	px_scene_->fetchResults(true);

	// retrieve array of actors that moved
	physx::PxU32 nb_active_transforms;
	physx::PxActiveTransform* active_transforms = px_scene_->getActiveTransforms(nb_active_transforms);

	//printf( "count PxRigidActor:%i count active transform:%i\n", nbPxactor, nb_active_transforms );

	//physx::PxTransform pose;
	physx::PxTransform pose;

	// update each render object with the new transform
	for(physx::PxU32 i = 0; i < nb_active_transforms; ++i) {
		//physx::PxActor* px_actor = active_transforms[i].actor;

		//printf( "actor type = %i\n", px_actor->getType() );

		physx::PxActor* pxactor = active_transforms[i].actor;
		assert(pxactor);
		physx::PxRigidBody* pxrigidbody = pxactor->isRigidBody();


		void* ud = active_transforms[i].userData;
		assert(ud);

		glutpp::actor::actor* gl_actor = static_cast<glutpp::actor::actor*>(ud);

		neb::Actor::Actor* actor = dynamic_cast<neb::Actor::Actor*>(gl_actor);
		if(actor != NULL)
		{
			pose = active_transforms[i].actor2World;
			actor->set_pose(pose);

			if(pxrigidbody != NULL) {
				neb::Actor::RigidBody::RigidBody* rigidbody =
					dynamic_cast<neb::Actor::RigidBody::RigidBody*>(actor);

				assert(rigidbody != NULL);

				physx::PxVec3 v(pxrigidbody->getLinearVelocity());

				rigidbody->raw_->velocity_ = v;

				//v.print();
			}

			actor->set(glutpp::actor::actor::flag::SHOULD_UPDATE);
		}
	}

	// vehicle
	//physx::PxVec3 g(0,-0.25,0);
	//vehicle_manager_.vehicle_suspension_raycasts(px_scene_);
	//vehicle_manager_.update((float)dt, g);

	send_actor_update();
}
void neb::scene::scene::step_remote(double time){
	NEBULA_DEBUG_1_FUNCTION;

	for(auto it = actors_.map_.cbegin(); it != actors_.map_.cend(); ++it) {
		it->second->step_remote(time);
	}

}
void neb::scene::scene::send_actor_update() {
	printf("DEBUG: message ACTOR_UPDATE sent\n");

	boost::shared_ptr<gal::network::omessage> msg(new gal::network::omessage);

	int type = glutpp::network::type::ACTOR_UPDATE;
	msg->write(&type, sizeof(int));

	glutpp::network::actor::update actor_update;

	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		auto actor = it->second;

		actor_update.load(actor);
	}

	msg->ar_ << actor_update;

	get_app()->send_server(msg);


}
void neb::scene::scene::fire(neb::Actor::Base_s actor) {

	switch(user_type_)
	{
		case LOCAL:
			fire_local(actor);
			break;
		case REMOTE:
			fire_remote(actor);
			break;
		default:
			abort();
	}

}
void neb::scene::scene::fire_local(neb::Actor::Base_s actor) {

	boost::shared_ptr<glutpp::actor::desc> desc = actor->get_projectile();

	//auto me = std::dynamic_pointer_cast<neb::Actor::Actor>(shared_from_this());

	auto a = create_actor_local(desc);

	/** @todo replace neb::timer::actor::type with inheritance */

	boost::shared_ptr<neb::Timer::Actor::Base> t(
			new neb::Timer::Actor::Release(glutpp::master::Global()->ios_, a, last_ + 5.0));


}
void neb::scene::scene::fire_remote(neb::Actor::Base_s actor) {

	boost::shared_ptr<gal::network::omessage> msg(new gal::network::omessage);


	Neb::Message::Actor::Event actor_event;

	actor_event.addr_.load_this(actor);

	//actor_event.event_.type_ = glutpp::actor::event::type::e::FIRE;
	
	//msg->write(glutpp::network::type::ACTOR_EVENT);
	
	msg->ar_ << actor_event;

	get_app()->send_client(msg);
}	









