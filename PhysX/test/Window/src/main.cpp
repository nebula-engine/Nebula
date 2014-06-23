#include <glm/gtc/matrix_transform.hpp>

#include <Nebula/app/Base.hh>
#include <Nebula/core/actor/Base.hh>
#include <Nebula/util/wrapper.hpp>
#include <Nebula/gfx/Context/Window.hpp>
#include <Nebula/gfx/environ/two.hpp>
#include <Nebula/gfx/environ/three.hpp>
#include <Nebula/gfx/GUI/Object/terminal.hh>
#include <Nebula/core/light/Spot.hh>
#include <Nebula/core/scene/Local.hh>
#include <Nebula/core/shape/empty.hpp>
#include <Nebula/gfx/Camera/View/ridealong.hh>
#include <Nebula/core/actor/Empty/Empty.hpp>
#include <Nebula/game/map/base.hpp>
#include <Nebula/ext/maze/game/map/maze2.hpp>
#include <Nebula/util/command.hpp>
#include <Nebula/util/command_set.hpp>

#include <PhysX/free.hpp>
#include <PhysX/app/base.hpp>
#include <PhysX/core/scene/local.hpp>
#include <PhysX/core/shape/box.hpp>
#include <PhysX/core/actor/rigiddynamic/local.hpp>
#include <PhysX/core/actor/rigidstatic/local.hpp>
#include <PhysX/game/weapon/SimpleProjectile.hpp>
#include <PhysX/ext/maze/game/map/maze2.hpp>
#include <PhysX/core/actor/control/rigidbody/base.hpp>

sp::shared_ptr<neb::gfx::context::window>		create_context_two(sp::shared_ptr<neb::gfx::window::base> window) {

	auto context = sp::make_shared<neb::gfx::context::window>(window);
	
	window->insert(context);

	context->environ_ = sp::make_shared<neb::gfx::environ::two>(/*context*/);

	context->init();
	
	//auto context = window->cii< neb::gfx::context::window, sp::shared_ptr<neb::gfx::window::base> >(window);

	return context;
}
sp::shared_ptr<neb::gfx::context::window>		create_context_three(sp::shared_ptr<neb::gfx::window::base> window) {
	assert(window);
	
	auto context = sp::make_shared<neb::gfx::context::window>(window);
	assert(context);
	
	window->insert(context);
	
	auto environ = sp::make_shared<neb::gfx::environ::three>(/*context*/);
	environ->init();
	
	context->environ_ = environ;
	
	context->init();
	
	//auto context = window->cii< neb::gfx::context::window, sp::shared_ptr<neb::gfx::window::base> >(window);
	
	assert(environ->view_);
	
	environ->view_->connect(window);

	return context;
}

sp::shared_ptr<neb::gfx::gui::layout::base>	create_layout(
		sp::shared_ptr<neb::gfx::window::base> window,
		sp::shared_ptr<neb::gfx::context::window> context) {

	auto app = neb::app::base::global();
	
	//auto layout = app->neb::gfx::gui::layout::util::parent::cii<neb::gfx::gui::layout::base, neb::app::base>(app);

	auto layout = sp::make_shared<neb::gfx::gui::layout::base>(app);

	app->neb::gfx::gui::layout::util::parent::insert(layout);
	
	context->environ_->drawable_ = layout;

	layout->connect(window);

	// object
	auto term = sp::make_shared<neb::gfx::gui::object::terminal>();

	layout->insert(term);

	term->init();

	return layout;
}
sp::shared_ptr<phx::core::actor::rigiddynamic::local>		create_actor_dynamic(sp::shared_ptr<phx::core::scene::local> scene) {

	auto actor = sp::make_shared<phx::core::actor::rigiddynamic::local>(scene);
	
	scene->insert(actor);
	
	actor->simulation_.word0 = phx::filter::filter::type::DYNAMIC;
	actor->simulation_.word1 = phx::filter::filter::RIGID_AGAINST;

	actor->init();

	// shape	
	auto shape = sp::make_shared<phx::core::shape::box>(actor);
	
	actor->neb::core::shape::util::parent::insert(shape);
	
	shape->init();

	actor->setupFiltering();

	std::cout << "actor dynamic use count = " << actor.use_count() << std::endl;

	return actor;	
}
sp::weak_ptr<phx::core::actor::rigiddynamic::base>		create_actor_ai(sp::shared_ptr<phx::core::scene::local> scene) {








	auto actor = sp::make_shared<phx::core::actor::rigiddynamic::local>(scene);

	scene->insert(actor);
	
	actor->simulation_.word0 = phx::filter::filter::type::DYNAMIC;
	actor->simulation_.word1 = phx::filter::filter::RIGID_AGAINST;

	actor->init();

	// shape	
	auto shape = sp::make_shared<phx::core::shape::box>(actor);
	
	actor->neb::core::shape::util::parent::insert(shape);
	
	shape->init();

	actor->setupFiltering();

	std::cout << "actor dynamic use count = " << actor.use_count() << std::endl;


	actor->setGlobalPosition(vec3(0,0,5));
	
	auto pxrd = actor->px_actor_->isRigidDynamic();
	
	pxrd->setLinearDamping(5.0);
	pxrd->setAngularDamping(5.0);
	
	// control

	auto control(sp::make_shared<phx::core::actor::control::rigidbody::pd>());
	
	actor->control_ = control;

	control->actor_ = actor;//->isPxActorRigidBodyBase();

	// target
	control->p_target_ = vec3(0,0,5);
	
	control->q_target_ = glm::angleAxis(1.5f, vec3(0.0,1.0,0.0));
	
	return actor;	



}
sp::shared_ptr<phx::core::scene::local>			create_scene(
		sp::shared_ptr<neb::gfx::window::base> window,
		sp::shared_ptr<neb::gfx::context::window> context)
{

	std::cout << "4\n";

	auto app = neb::app::base::global();
	assert(app);
	
	std::cout << "5\n";

	auto scene = sp::make_shared<phx::core::scene::local>(app);
	assert(scene);

	std::cout << "6\n";

	app->neb::core::scene::util::parent::insert(scene);

	std::cout << "7\n";

	scene->init();
	
	std::cout << "8\n";

	// actors
	scene->createActorRigidStaticCube(neb::core::pose(vec3(-5, 0, 0)), 1.0);
	scene->createActorRigidStaticCube(neb::core::pose(vec3( 5, 0, 0)), 1.0);
	scene->createActorRigidStaticCube(neb::core::pose(vec3( 0,-5, 0)), 1.0);
	scene->createActorRigidStaticCube(neb::core::pose(vec3( 0, 5, 0)), 1.0);
	scene->createActorRigidStaticCube(neb::core::pose(vec3( 0, 0,-5)), 1.0);
	//scene->createActorRigidStaticCube(neb::core::pose(vec3( 0, 0, 5)), 1.0);

	// player's actor
	auto actor3 = create_actor_dynamic(scene);
	actor3->setGlobalPosition(vec3(0,0,0));
	
	// weapon
	auto weap = actor3->createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0);

	// lights
	scene->createActorLightPoint(vec3());
	scene->createActorLightPoint(vec3(10,0,0));
	
	context->environ_->drawable_ = scene;

	// connect actor
	
	actor3->create_control(window);

	auto cam = sp::make_shared<neb::gfx::Camera::View::Ridealong>(context->environ_);

	cam->actor_ = actor3;
	
	//auto e3 = sp::dynamic_pointer_cast<neb::gfx::environ::three>(context->environ_);
	auto e3 = context->environ_->isEnvironThree();
	assert(e3);

	e3->view_ = cam;

	// ai
	create_actor_ai(scene);
	
	return scene;
}
sp::shared_ptr<phx::game::map::base>			create_maze(
		sp::shared_ptr<neb::gfx::window::base> window,
		sp::shared_ptr<neb::gfx::context::window> context) {
	
	auto app = phx::app::base::global();
	
	auto map = sp::make_shared<phx::ext::maze::game::map::maze2>(app, ivec2(15,15));
	
	app->phx::core::scene::util::parent::insert(map);
	
	map->init();

	// player's actor
	auto actor3 = create_actor_dynamic(map);
	actor3->setGlobalPosition(vec3(0,0,0));
	
	// weapon
	auto weap = actor3->createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0);

	// lights
	map->createActorLightPoint(vec3());
	map->createActorLightPoint(vec3(10,0,0));
	
	// give scene to context
	
	context->environ_->drawable_ = map;


	// camera
	
	actor3->create_control(window);

	auto cam = sp::make_shared<neb::gfx::Camera::View::Ridealong>(context->environ_);

	cam->actor_ = actor3;
	
	auto e3 = sp::dynamic_pointer_cast<neb::gfx::environ::three>(context->environ_);
	assert(e3);

	e3->view_ = cam;


	return map;
}
int			main() {

	phx::init();

	auto app = phx::app::base::global();

	// window	
	auto window = sp::make_shared<neb::gfx::window::base>();

	app->neb::gfx::window::util::parent::insert(window);

	window->init();

	// context
	auto context1 = create_context_three(window);
	auto context2 = create_context_two(window);


	// will be map in a minute...
	sp::shared_ptr<phx::core::scene::local> map;
	
	// command
	// create scene
	auto cmd_create_scene = sp::make_shared<neb::util::command>();

	cmd_create_scene->func_ = [&] (sp::shared_ptr<neb::util::terminal> term, bpo::variables_map vm) {
		(*term) << "creating scene...";
		//map = create_maze(window, context1);
		map = create_scene(window, context1);
	};
	
	app->command_set_->map_["sc"] = cmd_create_scene;
	
	// create scene
	auto cmd_create_maze = sp::make_shared<neb::util::command>();

	cmd_create_maze->func_ = [&] (sp::shared_ptr<neb::util::terminal> term, bpo::variables_map vm) {
		(*term) << "creating maze...";
		map = create_maze(window, context1);
	};
	
	app->command_set_->map_["maze"] = cmd_create_maze;

	// destroy scene
	auto cmd_destroy_scene = sp::make_shared<neb::util::command>();
	
	cmd_destroy_scene->func_ = [&] (sp::shared_ptr<neb::util::terminal> term, bpo::variables_map vm) {
		(*term) << "destroying scene...";
		if(map) {
			map->parent_->erase(map->i_);
			map.reset();
		}
		std::stringstream ss;
		ss << "use count " << map.use_count();
		(*term) << ss.str();
	};
	
	app->command_set_->map_["sd"] = cmd_destroy_scene;

	std::cout << "1\n";

	// create drawables
	//auto scene = create_scene(window, context1);

	std::cout << "2\n";

	auto layout = create_layout(window, context2);

	std::cout << "3\n";

	// loop

	app->loop();

}



