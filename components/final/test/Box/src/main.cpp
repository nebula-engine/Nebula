
#include <glm/gtc/matrix_transform.hpp>

#include <gal/console/base.hpp>

#include <neb/core/app/__base.hpp>
#include <neb/core/actor/base.hpp>
#include <neb/core/util/wrapper.hpp>
#include <neb/core/light/base.hpp>
#include <neb/core/scene/base.hpp>
#include <neb/core/shape/base.hpp>
#include <neb/core/actor/base.hpp>

#include <neb/gfx/Context/Window.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/GUI/Object/terminal.hh>
#include <neb/gfx/Camera/View/ridealong.hh>

#include <neb/core/game/map/base.hpp>
#include <neb/core/game/trigger/ActorEx1.hpp>

#include <neb/ext/maze/game/map/maze2.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/game/weapon/SimpleProjectile.hpp>
#include <neb/phx/game/game/base.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>

#include <neb/ext/maze/game/map/maze2.hpp>

#include <neb/fin/gfx_phx/app/base.hpp>
#include <neb/fin/gfx_phx/core/scene/base.hpp>
#include <neb/fin/gfx_phx/core/actor/rigiddynamic/base.hpp>
#include <neb/fin/gfx_phx/core/actor/rigidstatic/base.hpp>
#include <neb/fin/gfx_phx/core/shape/box.hpp>

std::shared_ptr<neb::gfx::context::window>		create_context_two(std::shared_ptr<neb::gfx::window::base> window) {

	auto context = sp::make_shared<neb::gfx::context::window>(window);

	window->insert(context);

	context->environ_ = sp::make_shared<neb::gfx::environ::two>(/*context*/);

	context->init();

	//auto context = window->cii< neb::gfx::context::window, std::shared_ptr<neb::gfx::window::base> >(window);

	return context;
}
std::shared_ptr<neb::gfx::context::window>		create_context_three(std::shared_ptr<neb::gfx::window::base> window) {
	assert(window);

	auto context = sp::make_shared<neb::gfx::context::window>(window);
	assert(context);

	window->insert(context);

	auto environ = sp::make_shared<neb::gfx::environ::three>(/*context*/);
	environ->init();

	context->environ_ = environ;

	context->init();

	//auto context = window->cii< neb::gfx::context::window, std::shared_ptr<neb::gfx::window::base> >(window);

	assert(environ->view_);

	environ->view_->connect(window);

	return context;
}

std::shared_ptr<neb::gfx::gui::layout::base>	create_layout(
		std::shared_ptr<neb::gfx::window::base> window,
		std::shared_ptr<neb::gfx::context::window> context) {

	auto app = neb::fin::gfx_phx::app::base::global();

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
shared_ptr<neb::fin::gfx_phx::core::actor::rigiddynamic::base>		create_actor_dynamic(std::shared_ptr<neb::fin::gfx_phx::core::scene::base> scene) {

	auto actor = make_shared<neb::fin::gfx_phx::core::actor::rigiddynamic::base>(scene);

	scene->insert(actor);

	actor->flag_.set(neb::core::actor::util::flag::DESTRUCTIBLE);

	actor->simulation_.word0 = neb::phx::filter::filter::type::DYNAMIC;
	actor->simulation_.word1 = neb::phx::filter::filter::RIGID_AGAINST;
	actor->simulation_.word2 = neb::phx::filter::filter::type::DYNAMIC;
	actor->simulation_.word3 = neb::phx::filter::filter::type::PROJECTILE;


	/*std::cout << "neb base " << actor->isActorBase().get() << std::endl;
	  std::cout << "phx base " << actor->isPxActorBase().get() << std::endl;
	  std::cout << "phx rd   " << actor->isPxActorRigidDynamicBase().get() << std::endl;

	  exit(0);*/


	actor->init();

	// shape	
	auto shape = make_shared<neb::fin::gfx_phx::core::shape::box>(actor);

	actor->neb::core::shape::util::parent::insert(shape);

	shape->init();

	actor->setupFiltering();

	std::cout << "actor dynamic use count = " << actor.use_count() << std::endl;

	return actor;	
}
weak_ptr<neb::phx::core::actor::rigiddynamic::base>		create_actor_ai(std::shared_ptr<neb::fin::gfx_phx::core::scene::base> scene) {

	auto actor = sp::make_shared<neb::fin::gfx_phx::core::actor::rigiddynamic::base>(scene);

	scene->insert(actor);

	actor->flag_.set(neb::core::actor::util::flag::DESTRUCTIBLE);

	actor->simulation_.word0 = neb::phx::filter::filter::type::DYNAMIC;
	actor->simulation_.word1 = neb::phx::filter::filter::RIGID_AGAINST;
	actor->simulation_.word2 = neb::phx::filter::filter::type::DYNAMIC;
	actor->simulation_.word3 = neb::phx::filter::filter::type::PROJECTILE;

	// testing for multiple inheritance
	//auto test = actor->gal::itf::shared::name();
	//auto test = actor->shared_from_this();

	actor->init();

	// shape	
	auto shape = make_shared<neb::fin::gfx_phx::core::shape::box>(actor);

	actor->neb::core::shape::util::parent::insert(shape);

	shape->init();

	actor->setupFiltering();

	std::cout << "actor dynamic use count = " << actor.use_count() << std::endl;


	actor->setGlobalPosition(vec3(0,0,5));

	auto pxrd = actor->px_actor_->isRigidDynamic();

	pxrd->setLinearDamping(5.0);
	pxrd->setAngularDamping(3.0);

	// control

	auto control(make_shared<neb::phx::core::actor::control::rigidbody::pd>());

	actor->control_ = control;

	control->actor_ = actor;//->isPxActorRigidBodyBase();

	// target
	control->p_target_ = vec3(0,0,5);

	control->q_target_ = glm::angleAxis(1.5f, vec3(0.0,1.0,0.0));

	return actor;	



}
shared_ptr<neb::fin::gfx_phx::core::scene::base>			create_scene(
		shared_ptr<neb::gfx::window::base> window,
		shared_ptr<neb::gfx::context::window> context,
		shared_ptr<neb::phx::core::actor::base>& enemy)
{

	std::cout << "4\n";

	auto app = neb::fin::gfx_phx::app::base::global();
	assert(app);

	std::cout << "5\n";

	auto scene = make_shared<neb::fin::gfx_phx::core::scene::base>(app);
	assert(scene);

	std::cout << "6\n";

	app->neb::core::core::scene::util::parent::insert(scene);

	std::cout << "7\n";

	scene->init();

	std::cout << "8\n";

	// actors
	scene->createActorRigidStaticCube(neb::core::pose(vec3(-5, 0, 0)), 1.0);
	scene->createActorRigidStaticCube(neb::core::pose(vec3( 5, 0, 0)), 1.0);
	scene->createActorRigidStaticCube(neb::core::pose(vec3( 0,-5, 0)), 1.0);
	scene->createActorRigidStaticCube(neb::core::pose(vec3( 0, 5, 0)), 1.0);
	auto static_cube5 = scene->createActorRigidStaticCube(neb::core::pose(vec3( 0, 0,-5)), 1.0).lock();

	// testing for multiple inheritance
	auto test = static_cube5->gal::itf::shared::name();


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

	auto cam = make_shared<neb::gfx::Camera::View::Ridealong>(context->environ_);

	cam->actor_ = actor3;

	//auto e3 = std::dynamic_pointer_cast<neb::gfx::environ::three>(context->environ_);
	auto e3 = context->environ_->isEnvironThree();
	assert(e3);

	e3->view_ = cam;

	// game
	auto game(make_shared<neb::phx::game::game::base>());

	app->neb::phx::game::game::util::parent::insert(game);

	// ai
	enemy = create_actor_ai(scene).lock();

	// weapon
	enemy->createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0);

	auto ai(sp::make_shared<neb::phx::game::ai::base>());

	game->neb::phx::game::ai::util::parent::insert(ai);

	ai->actor_ = enemy;
	ai->target_ = actor3;

	return scene;
}
shared_ptr<neb::phx::game::map::base>			create_maze(
		shared_ptr<neb::gfx::window::base> window,
		shared_ptr<neb::gfx::context::window> context) {

	auto app = neb::fin::gfx_phx::app::base::global();

	auto map = make_shared<neb::ext::maze::game::map::maze2>(app, ivec2(15,15));

	app->neb::phx::core::scene::util::parent::insert(map);

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

	auto cam = make_shared<neb::gfx::Camera::View::Ridealong>(context->environ_);

	cam->actor_ = actor3;

	auto e3 = dynamic_pointer_cast<neb::gfx::environ::three>(context->environ_);
	assert(e3);

	e3->view_ = cam;


	return map;
}
weak_ptr<neb::phx::game::game::base>		create_game() {

	auto app(neb::phx::app::base::global());

	auto game(make_shared<neb::phx::game::game::base>());

	app->neb::game::game::util::parent::insert(game);


	return game;
}
void						setup_game(
		shared_ptr<neb::phx::game::game::base> game,
		shared_ptr<neb::gfx::window::base> window,
		shared_ptr<neb::gfx::context::window> context)
{
	// scene
	shared_ptr<neb::phx::core::actor::base> enemy;

	auto scene = create_scene(window, context, enemy);

	game->scene_ = scene;

	// trigger
	auto trig(make_shared<neb::game::trigger::ActorEx1>(game));

	game->neb::game::trigger::util::parent::insert(trig);

	trig->connect(enemy);

	cout << "game use count " << game.use_count() << endl;
}
int			main() {

	auto app = neb::fin::gfx_phx::app::base::init();

	// window	
	auto window = sp::make_shared<neb::gfx::window::base>();

	app->neb::gfx::window::util::parent::insert(window);

	window->init();

	// context
	auto context1 = create_context_three(window);
	auto context2 = create_context_two(window);


	// game
	auto game = create_game();

	// will be map in a minute...
	//std::shared_ptr<phx::core::scene::base> map;

	/*
	// command
	// create scene
	auto cmd_create_scene = sp::make_shared<gal::std::command>();

	cmd_create_scene->func_ = [&] (std::shared_ptr<gal::std::terminal> term, bpo::variables_map vm) {
		(*term) << "creating scene...";
		//map = create_maze(window, context1);
		//map = create_scene(window, context1);

		setup_game(game.lock(), window, context1);
	};

	app->command_set_->map_["sc"] = cmd_create_scene;

	// create scene
	auto cmd_create_maze = sp::make_shared<gal::std::command>();

	cmd_create_maze->func_ = [&] (std::shared_ptr<gal::std::terminal> term, bpo::variables_map vm) {
		(*term) << "creating maze...";
		game.lock()->scene_ = create_maze(window, context1);
	};

	app->command_set_->map_["maze"] = cmd_create_maze;

	// destroy scene
	auto cmd_destroy_scene = sp::make_shared<gal::std::command>();

	cmd_destroy_scene->func_ = [&] (std::shared_ptr<gal::std::terminal> term, bpo::variables_map vm) {
		(*term) << "destroying scene...";
		auto scene = game.lock()->scene_.lock();
		if(scene) {
			scene->parent_->erase(scene->i_);
		}
		std::stringstream ss;
		ss << "use count " << scene.use_count();
		(*term) << ss.str();
	};
	
	app->command_set_->map_["sd"] = cmd_destroy_scene;
	*/
	
	std::cout << "1\n";

	// create drawables
	//auto scene = create_scene(window, context1);

	std::cout << "2\n";

	auto layout = create_layout(window, context2);

	std::cout << "3\n";

	// loop

	app->loop();

}



