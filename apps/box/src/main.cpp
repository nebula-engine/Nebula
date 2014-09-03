
#include <glm/gtc/matrix_transform.hpp>

#include <gal/console/base.hpp>

#include <neb/core/app/__base.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/util/wrapper.hpp>
#include <neb/core/core/light/base.hpp>
#include <neb/core/core/scene/base.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/actor/base.hpp>

#include <neb/gfx/core/light/util/decl.hpp>
#include <neb/gfx/core/light/directional.hpp>
#include <neb/gfx/core/light/point.hpp>
#include <neb/gfx/Context/Window.hpp>
#include <neb/gfx/Context/fbo.hpp>
#include <neb/gfx/Context/fbo_multi.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/environ/vis_depth.hpp>
#include <neb/gfx/gui/object/terminal.hh>
#include <neb/gfx/camera/view/ridealong.hh>

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

typedef std::shared_ptr<neb::gfx::window::base> window_shared;


std::shared_ptr<neb::fin::gfx_phx::app::base>		app;

window_shared						window0;
std::shared_ptr<neb::gfx::context::window>		context1;
std::shared_ptr<neb::gfx::context::window>		context2;

window_shared						window1;
std::shared_ptr<neb::gfx::context::window>		context1_0;


std::shared_ptr<neb::fin::gfx_phx::core::scene::base>	scene;

shared_ptr<neb::gfx::gui::layout::base>	create_layout() {

	assert(window0);
	
	auto app = neb::fin::gfx_phx::app::base::global();
	
	auto layout = app->createLayout().lock();

	layout->connect(window0);

	layout->createObjectTerminal();

	return layout;
}

weak_ptr<neb::fin::gfx_phx::core::actor::rigiddynamic::base>		create_actor_ai(
		std::shared_ptr<neb::fin::gfx_phx::core::scene::base> scene) {
	
	auto actor = dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::rigiddynamic::base>(
			scene->createActorRigidDynamicUninitialized().lock()
			);

	actor->flag_.set(neb::core::core::actor::util::flag::DESTRUCTIBLE);

	actor->init();

	// shape	
	auto shape = actor->createShapeCube(neb::core::pose(), 1.0);

	actor->setupFiltering();

	actor->setGlobalPosition(vec3(0,0,5));

	auto pxrd = actor->px_actor_->isRigidDynamic();

	pxrd->setLinearDamping(5.0);
	pxrd->setAngularDamping(3.0);



	actor->createControlPD();
	
	return actor;	
}
shared_ptr<neb::fin::gfx_phx::core::scene::base>			create_scene(
		shared_ptr<neb::gfx::window::base> window,
		shared_ptr<neb::gfx::context::window> context,
		shared_ptr<neb::fin::gfx_phx::core::actor::base>& enemy)
{

	auto app = neb::fin::gfx_phx::app::base::global();
	assert(app);
	

	scene = app->createScene().lock();

	// actors

	auto actor1 = scene->createActorRigidDynamicCuboid(
			neb::core::core::actor::rigidbody::desc(neb::core::pose(glm::vec3(-5, 0, 0))),
			neb::core::core::shape::cuboid::desc(glm::vec3(1.0))
			).lock();

	auto shape1 = std::dynamic_pointer_cast<neb::fin::gfx_phx::core::shape::box>(actor1->neb::core::core::shape::util::parent::map_.front());
	if(shape1) {
		auto mesh1 = shape1->mesh_;
		if(mesh1) {
			mesh1->texture_ = neb::gfx::texture::makePNG("crab.png");
			mesh1->material_front_.raw_.diffuse_ = neb::core::color::color(1,1,1,1);
		}
	}

	auto actor2 = scene->createActorRigidDynamicCuboid(
			neb::core::core::actor::rigidbody::desc(neb::core::pose(glm::vec3(5, 0, 0))),
			neb::core::core::shape::cuboid::desc(glm::vec3(1.0))
			).lock();
	auto shape2 = std::dynamic_pointer_cast<neb::fin::gfx_phx::core::shape::box>(actor2->neb::core::core::shape::util::parent::map_.front());
	if(shape2) if(shape2->mesh_) shape2->mesh_->normal_map_ = neb::gfx::texture::makePNG("norm.png");

	scene->createActorRigidDynamicCuboid(
			neb::core::core::actor::rigidbody::desc(neb::core::pose(glm::vec3(0, -5, 0))),
			neb::core::core::shape::cuboid::desc(glm::vec3(1.0))
			);
	scene->createActorRigidDynamicCuboid(
			neb::core::core::actor::rigidbody::desc(neb::core::pose(glm::vec3(0, 5, 0))),
			neb::core::core::shape::cuboid::desc(glm::vec3(1.0))
			);

	auto static_cube5 = scene->createActorRigidStaticCube(neb::core::pose(vec3( 0, 0,-5)), 1.0).lock();


	//scene->createActorRigidStaticCube(neb::core::pose(vec3( 0, 0, 5)), 1.0);

	// player's actor
	auto actor3 = std::dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::rigiddynamic::base>(
			scene->createActorRigidDynamicCuboid(
				neb::core::core::actor::rigidbody::desc(),
				neb::core::core::shape::cuboid::desc(glm::vec3(1.0))
				).lock()
			);


	// weapon
	auto weap = actor3->createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0);

	// lights
	scene->createActorLightPoint(vec3());
	//scene->createActorLightPoint(vec3(10,0,0));

	context->setDrawable(scene);

	// connect actor

	actor3->createControlManual(window);

	context->environ_->isEnvironThree()->createViewridealong(actor3);

	// game
	auto game(make_shared<neb::phx::game::game::base>());

	app->neb::phx::game::game::util::parent::insert(game);

	// ai
	enemy = dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::base>(create_actor_ai(scene).lock());

	// weapon
	enemy->createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0);

	auto ai(sp::make_shared<neb::phx::game::ai::base>());

	game->neb::phx::game::ai::util::parent::insert(ai);

	ai->actor_ = enemy;
	ai->target_ = actor3;

	return scene;
}
shared_ptr<neb::phx::game::map::base>			create_maze()
{
	assert(window0);
	assert(context1);

	auto app = neb::fin::gfx_phx::app::base::global();

	auto map = make_shared<neb::ext::maze::game::map::maze2>(app, ivec2(15,15));
	app->neb::phx::core::scene::util::parent::insert(map);
	map->init();

	// player's actor
	auto actor3 = std::dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::rigiddynamic::base>(
			map->createActorRigidDynamicCuboid(
				neb::core::core::actor::rigidbody::desc(),
				neb::core::core::shape::cuboid::desc(glm::vec3(1.0))
				).lock()
			);

	// weapon
	auto weap = actor3->createWeaponSimpleProjectile(window0, 0.2, 10.0, 5.0);

	// lights
	//auto actor4 = map->createActorLightDirectional(glm::vec3(0,1,-1)).lock();
	auto actor4 = map->createActorLightPoint(glm::vec3(0,0,-10)).lock();

	//auto shape4 = actor4->neb::core::core::shape::util::parent::map_.front();
	//assert(shape4);
	//light0 = std::dynamic_pointer_cast<light_type>(shape4->neb::core::core::light::util::parent::map_.front());
	//assert(light0);

	// give scene to context


	// camera

	actor3->createControlManual(window0);

	context1->environ_->isEnvironThree()->createViewridealong(actor3);

	return map;
}
weak_ptr<neb::phx::game::game::base>		create_game() {

	auto app(neb::phx::app::base::global());

	auto game(make_shared<neb::phx::game::game::base>());

	app->neb::game::game::util::parent::insert(game);


	return game;
}
void		setup_game()
{

	auto game = create_game().lock();

	// scene
	shared_ptr<neb::fin::gfx_phx::core::actor::base> enemy;

	//auto scene = create_scene(window, context, enemy);
	scene = std::dynamic_pointer_cast<neb::fin::gfx_phx::core::scene::base>(create_maze());
	assert(scene);

	game->scene_ = scene;

	// trigger
	if(enemy) {
		auto trig(make_shared<neb::game::trigger::ActorEx1>(game));
		game->neb::game::trigger::util::parent::insert(trig);
		trig->connect(enemy);
	}

}
void				createWindowTexVis(std::shared_ptr<neb::gfx::texture> tex)
{
	auto window1 = app->createWindow().lock();
	auto context4 = window1->createContextTwo().lock();
	context4->setDrawable(tex);
}
void				createWindow0() {

	assert(app);
	
	window0 = app->createWindow().lock();
	
	context1 = window0->createContextThree().lock();
	context2 = window0->createContextTwo().lock();
	
	auto layout = create_layout();

	context2->setDrawable(layout);
	
}
/*void				createWindow1()
{
	assert(app);
	assert(scene);
	
	window1 = app->createWindow().lock();
	
	context1_0 = window1->createContextWindow().lock();
	
	auto environ = context1_0->createEnvironVisDepth().lock();

	environ->light_ = light0;

	context1_0->setDrawable(scene);
}*/
void				setupWindow0() {
	assert(scene);
	assert(context1);
	context1->setDrawable(scene);
}
int			main() {

	app = neb::fin::gfx_phx::app::base::init();

	createWindow0();

	// game

	// create drawables
	//shared_ptr<neb::fin::gfx_phx::core::actor::base> enemy;

	//auto scene = create_scene(window, context1, enemy);

	setup_game();

	setupWindow0();
	
	//createWindow1();

	createWindowTexVis(scene->tex_shadow_map_);

	app->loop();
}





