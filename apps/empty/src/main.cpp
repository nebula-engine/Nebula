



#include <glm/gtc/matrix_transform.hpp>

#include <gal/console/base.hpp>

#include <gal/etc/stopwatch.hpp>

#include <neb/fnd/free.hpp>
#include <neb/fnd/util/cast.hpp>
#include <neb/fnd/app/Base.hpp>
#include <neb/fnd/core/actor/Base.hpp>
#include <neb/fnd/util/wrapper.hpp>
#include <neb/fnd/core/light/base.hpp>
#include <neb/fnd/core/scene/Base.hpp>
#include <neb/fnd/core/shape/base.hpp>
#include <neb/fnd/core/shape/cuboid/desc.hpp>
#include <neb/fnd/core/actor/Base.hpp>
#include <neb/fnd/core/actor/rigidbody/desc.hpp>
#include <neb/fnd/game/map/base.hpp>
#include <neb/fnd/game/trigger/ActorEx1.hpp>
#include <neb/fnd/game/game/desc.hpp>
#include <neb/fnd/game/weapon/SimpleProjectile.hpp>
#include <neb/fnd/context/Window.hpp>
#include <neb/fnd/environ/Two.hpp>

/*
#include <neb/gfx/core/light/util/decl.hpp>
#include <neb/gfx/core/light/directional.hpp>
#include <neb/gfx/core/light/point.hpp>
#include <neb/gfx/core/light/spot.hpp>
#include <neb/gfx/context/fbo.hpp>
#include <neb/gfx/context/fbo_multi.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/environ/SceneDefault.hpp>
#include <neb/gfx/environ/vis_depth.hpp>
#include <neb/gfx/gui/object/terminal.hpp>
#include <neb/gfx/camera/view/Ridealong.hpp>
#include <neb/gfx/camera/view/shadow/point.hpp>
#include <neb/gfx/camera/proj/perspective.hpp>
*/

//#include <neb/ext/maze/game/map/maze2.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/phx/test.hpp>

//#include <neb/ext/maze/game/map/maze2.hpp>

#include <neb/fin/app/base.hpp>
#include <neb/fin/core/scene/base.hpp>
#include <neb/fin/core/actor/rigiddynamic/base.hpp>
#include <neb/fin/core/actor/rigidstatic/base.hpp>
//#include <neb/fin/core/shape/box.hpp>
//#include <neb/fin/core/shape/HeightField.hpp>

/*
typedef std::shared_ptr<neb::fnd::window::Base> window_shared;
typedef neb::gfx::core::light::point		light_type;
typedef neb::fnd::game::game::base			game_t;

typedef neb::fin::core::scene::base	map_type;

typedef neb::fnd::core::scene::base	scene_t;
typedef std::shared_ptr<scene_t>	scene_s;

typedef neb::fin::core::actor::rigiddynamic::base actor_dyn_t;

std::shared_ptr<game_t>			game;

std::shared_ptr<neb::fin::core::actor::base>	enemy;

window_shared						window0;
std::shared_ptr<neb::gfx::context::window>		context1;
std::shared_ptr<neb::gfx::environ::SceneDefault>	environ1;
std::shared_ptr<neb::fnd::context::Window>		context2;

window_shared						window1;
std::shared_ptr<neb::gfx::context::window>		context1_0;


scene_s			scene;


std::shared_ptr<neb::fin::core::actor::rigiddynamic::base>	actor_player;
std::shared_ptr<neb::fnd::core::actor::base>				actor_light;
*/

int			main(int ac, char ** av)
{
	auto app = neb::fin::app::base::s_init(ac, av);

	auto window = app->createWindow().lock();

//	context1 = window0->createContextThree().lock();
	auto context = window->createContextWindow().lock();
	
	auto environ = context->createEnvironTwo().lock();

	// context->init()

	auto layout = app->createLayout(window, environ).lock();
/*
	neb::fnd::game::game::desc gameDesc;

	game = app->createGame(gameDesc);
*/
	// scene

	/*
	scene = std::dynamic_pointer_cast<neb::fin::core::scene::base>(
			create_maze()
			);
	assert(scene);

	game->scene_ = scene;

	context1->setDrawable(std::dynamic_pointer_cast<neb::gfx::drawable::base>(scene));
*/

	//auto scene = app->createScene();

	app->loop();
}



