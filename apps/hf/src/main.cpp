



#include <glm/gtc/matrix_transform.hpp>

#include <gal/console/base.hpp>

#include <gal/etc/stopwatch.hpp>

#include <neb/core/util/cast.hpp>
#include <neb/core/app/__base.hpp>
#include <neb/core/app/__core.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/util/wrapper.hpp>
#include <neb/core/core/light/base.hpp>
#include <neb/core/core/scene/base.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/shape/cuboid/desc.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/actor/rigidbody/desc.hpp>

#include <neb/gfx/core/light/util/decl.hpp>
#include <neb/gfx/core/light/directional.hpp>
#include <neb/gfx/core/light/point.hpp>
#include <neb/gfx/core/light/spot.hpp>
#include <neb/gfx/context/Window.hpp>
#include <neb/gfx/context/fbo.hpp>
#include <neb/gfx/context/fbo_multi.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/environ/SceneDefault.hpp>
#include <neb/gfx/environ/vis_depth.hpp>
#include <neb/gfx/gui/object/terminal.hh>
#include <neb/gfx/camera/view/ridealong.hh>
#include <neb/gfx/camera/view/shadow/point.hpp>
#include <neb/gfx/camera/proj/perspective.hpp>

#include <neb/core/game/map/base.hpp>
#include <neb/core/game/trigger/ActorEx1.hpp>
#include <neb/core/game/game/desc.hpp>
//#include <neb/ext/maze/game/map/maze2.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/core/scene/base.hpp>


#include <neb/core/game/weapon/SimpleProjectile.hpp>

#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/phx/test.hpp>

//#include <neb/ext/maze/game/map/maze2.hpp>

#include <neb/fin/app/base.hpp>
#include <neb/fin/core/scene/base.hpp>
#include <neb/fin/core/actor/rigiddynamic/base.hpp>
#include <neb/fin/core/actor/rigidstatic/base.hpp>
#include <neb/fin/core/shape/box.hpp>
#include <neb/fin/core/shape/HeightField.hpp>

#include <neb/core/free.hpp>

void	create_enemy();


typedef std::shared_ptr<neb::gfx::window::base> window_shared;
typedef neb::gfx::core::light::point		light_type;
typedef neb::core::game::game::base			game_t;

typedef neb::fin::core::scene::base	map_type;

typedef neb::core::core::scene::base	scene_t;
typedef std::shared_ptr<scene_t>	scene_s;

typedef neb::fin::core::actor::rigiddynamic::base actor_dyn_t;

std::shared_ptr<game_t>			game;

std::shared_ptr<neb::fin::core::actor::base>	enemy;

window_shared						window0;
std::shared_ptr<neb::gfx::context::window>		context1;
std::shared_ptr<neb::gfx::environ::SceneDefault>	environ1;
std::shared_ptr<neb::gfx::context::window>		context2;

window_shared						window1;
std::shared_ptr<neb::gfx::context::window>		context1_0;


scene_s			scene;


std::shared_ptr<neb::fin::core::actor::rigiddynamic::base>	actor_player;
std::shared_ptr<neb::core::core::actor::base>				actor_light;


scene_s		create_maze()
{
	//assert(window0);
	//assert(context1);

	auto app = neb::fin::app::base::global();

	// create map

	/*if(0)
	{
		scene = app->createSceneDll("../../components/ext/hf/libnebula_ext_hf_0.so").lock();

		// player's actor
		actor_player = std::dynamic_pointer_cast<actor_dyn_t>(loadXML<neb::core::core::actor::base>("actor_player.xml"));
		scene->addActor(actor_player);
	}
	else*/
	
	{
		scene = loadXML<scene_t>(NEB_SHARE_DIR"/media/scenes/scene.xml");
		app->neb::core::core::scene::util::parent::insert(scene);
		
		scene->init(app.get());

		actor_player = std::dynamic_pointer_cast<actor_dyn_t>(scene->neb::core::core::actor::util::parent::map_.find("player"));
	}
	
	assert(actor_player);
	
	// weapon
	if(window0 && actor_player)
	{
		auto weap = actor_player->createWeaponSimpleProjectile(window0, 0.2, 10.0, 5.0);

		// camera

		actor_player->createControlManual(window0);

		environ1 = neb::is<neb::gfx::environ::base, neb::gfx::environ::SceneDefault>(context1->environ_);

		environ1->createViewridealong(actor_player);
	}	
	//	light->initShadow(environ1);

	//create_enemy();


	return scene;
}
int			main()
{

	auto app = neb::fin::app::base::s_init();

	window0 = app->createWindow().lock();

	context1 = window0->createContextThree().lock();
	context2 = window0->createContextTwo().lock();

	auto layout = app->createLayout(window0, context2).lock();

	neb::core::game::game::desc gameDesc;

	game = app->createGame(gameDesc);

	// scene

	scene = std::dynamic_pointer_cast<neb::fin::core::scene::base>(
			create_maze()
			);
	assert(scene);

	game->scene_ = scene;

	context1->setDrawable(std::dynamic_pointer_cast<neb::gfx::drawable::base>(scene));


	app->loop();


}





