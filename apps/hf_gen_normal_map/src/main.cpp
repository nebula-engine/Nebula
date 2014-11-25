
//#include <neb/core/rand.hpp>


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
#include <neb/core/core/shape/HeightField/desc.hpp>
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
#include <neb/gfx/environ/NormalMap.hpp>
#include <neb/gfx/environ/vis_depth.hpp>
#include <neb/gfx/gui/object/terminal.hh>
#include <neb/gfx/camera/view/manual.hpp>
#include <neb/gfx/camera/view/shadow/point.hpp>
#include <neb/gfx/camera/proj/ortho.hpp>

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
#include <neb/phx/core/shape/HeightField/Base.hpp>

#include <neb/core/free.hpp>

void	create_enemy();


typedef std::shared_ptr<neb::gfx::window::base> window_shared;
typedef neb::gfx::core::light::point		light_type;
typedef neb::core::game::game::base		game_t;

typedef neb::fin::core::scene::base	map_type;
//typedef neb::ext::maze::game::map::maze2	map_type;

typedef neb::core::core::scene::base	scene_t;
typedef std::shared_ptr<scene_t>	scene_s;

typedef neb::fin::core::actor::rigiddynamic::base actor_dyn_t;

std::shared_ptr<game_t>			game;

std::shared_ptr<neb::fin::core::actor::base>	enemy;

std::shared_ptr<neb::fin::app::base>		app;
std::shared_ptr<neb::gfx::environ::SceneDefault>	environ1;
std::shared_ptr<neb::gfx::context::window>		context2;

window_shared						window1;
std::shared_ptr<neb::gfx::context::window>		context1_0;


scene_s			scene;
//std::shared_ptr<neb::core::core::scene::base>			scene;


std::shared_ptr<neb::fin::core::actor::rigiddynamic::base>	actor_player;
//std::shared_ptr<neb::core::core::actor::base>	actor_player;
std::shared_ptr<neb::core::core::actor::base>				actor_light;

int			main(int ac, char ** av)
{


	makeDLLFunc<neb::core::core::scene::base, neb::fin::core::scene::base>();
	
	makeDefaultFunc<neb::core::core::actor::base, neb::fin::core::actor::rigiddynamic::base>();
	makeDefaultFunc<neb::core::core::actor::__base, neb::fin::core::actor::rigiddynamic::base>();
	makeDefaultFunc<neb::core::core::actor::__base, neb::fin::core::actor::base>();

//	makeDefaultFunc<neb::core::core::shape::base, neb::fin::core::shape::base>();
//	makeDefaultFunc<neb::core::core::shape::base, neb::fin::core::shape::box>();

	makeDefaultFunc<neb::core::core::light::__base, neb::gfx::core::light::spot>();
	makeDefaultFunc<neb::core::core::light::__base, neb::gfx::core::light::point>();




	app = neb::fin::app::base::s_init();

	//myrand();

	auto window = app->createWindow().lock();//neb::gfx::window::util::parent::create<neb::gfx::window::base>().lock();

	auto context = window->createContextNormalMap().lock();

	// scene
	
	auto scene = app->createScene().lock();

	auto actor = scene->createActorRigidStaticUninitialized().lock();

	actor->init(scene.get());
	
	neb::core::core::shape::HeightField::desc desc;
	desc.r = atoi(av[1]);
	desc.c = atoi(av[2]);

	desc.w = 50;
	desc.h = 50;
	desc.hs = 10;

	for(int i = 3; i < ac; i++)
		desc.fc.push_back(atof(av[i]));

	auto shape = std::dynamic_pointer_cast<neb::phx::core::shape::HeightField::Base>(
			actor->createShapeHeightField(desc).lock()
			);
	
	
	
	context->setDrawable(std::dynamic_pointer_cast<neb::gfx::drawable::base>(scene));
	
	auto environ = std::dynamic_pointer_cast<neb::gfx::environ::NormalMap>(context->environ_);
	assert(environ);
	
	
	//typedef neb::gfx::camera::proj::ortho Ortho;
	//std::shared_ptr<Ortho> proj(new Ortho(environ));
	
	auto proj = environ->createCameraOrtho()->isOrtho();
	
	environ->proj_ = proj;
	
	float w = 25;

	proj->set(-w,w,-w,w,-100,100);

	
	auto view = std::dynamic_pointer_cast<neb::gfx::camera::view::manual>(environ->view_);
	assert(view);
		
	view->eye_ = glm::vec3(w,-50,w);
	view->center_ = glm::vec3(w,0,w);
	view->up_ = glm::vec3(1,0,0);

	app->loop();

}





