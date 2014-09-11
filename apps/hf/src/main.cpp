



#include <glm/gtc/matrix_transform.hpp>

#include <gal/console/base.hpp>

#include <gal/etc/stopwatch.hpp>

#include <neb/core/util/cast.hpp>
#include <neb/core/app/__base.hpp>
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
#include <neb/gfx/Context/Window.hpp>
#include <neb/gfx/Context/fbo.hpp>
#include <neb/gfx/Context/fbo_multi.hpp>
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
#include <neb/phx/game/weapon/SimpleProjectile.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/phx/test.hpp>

//#include <neb/ext/maze/game/map/maze2.hpp>

#include <neb/fin/gfx_phx/app/base.hpp>
#include <neb/fin/gfx_phx/core/scene/base.hpp>
#include <neb/fin/gfx_phx/core/actor/rigiddynamic/base.hpp>
#include <neb/fin/gfx_phx/core/actor/rigidstatic/base.hpp>
#include <neb/fin/gfx_phx/core/shape/box.hpp>

template<typename B, typename D> void	makeDefaultFunc()
{

	gal::itf::shared::register_type(std::type_index(typeid(B)));
	gal::itf::shared::register_type(std::type_index(typeid(D)));


	std::function< std::shared_ptr<B>() > f(
			[]() { return std::shared_ptr<D>(new D(), gal::stl::deleter<D>()); }
			);

	gal::stl::factory<B>::default_factory_->add(typeid(D).hash_code(), f);
}
template<typename T> std::shared_ptr<T>		loadXML(std::string filename)
{
	std::ifstream ifs;
	ifs.open(filename);
	if(!ifs.is_open())
	{
		std::cout << "file error: " << filename << std::endl;
		abort();
	}

	gal::stl::wrapper<T> w;

	boost::archive::polymorphic_xml_iarchive ar(ifs);

	w.load(ar,0);

	return w.ptr_;
}

void	create_enemy();


typedef std::shared_ptr<neb::gfx::window::base> window_shared;
typedef neb::gfx::core::light::point		light_type;
typedef neb::game::game::base			game_t;

typedef neb::fin::gfx_phx::core::scene::base	map_type;
//typedef neb::ext::maze::game::map::maze2	map_type;

typedef std::shared_ptr<neb::fin::gfx_phx::core::scene::base>	scene_s;

typedef neb::fin::gfx_phx::core::actor::rigiddynamic::base actor_dyn_t;

std::shared_ptr<game_t>			game;

std::shared_ptr<neb::fin::gfx_phx::core::actor::base>	enemy;

std::shared_ptr<neb::fin::gfx_phx::app::base>		app;
window_shared						window0;
std::shared_ptr<neb::gfx::context::window>		context1;
std::shared_ptr<neb::gfx::environ::SceneDefault>	environ1;
std::shared_ptr<neb::gfx::context::window>		context2;

window_shared						window1;
std::shared_ptr<neb::gfx::context::window>		context1_0;


std::shared_ptr<neb::fin::gfx_phx::core::scene::base>			scene;
//std::shared_ptr<neb::core::core::scene::base>			scene;


std::shared_ptr<neb::fin::gfx_phx::core::actor::rigiddynamic::base>	actor_player;
//std::shared_ptr<neb::core::core::actor::base>	actor_player;
std::shared_ptr<neb::core::core::actor::base>				actor_light;

shared_ptr<neb::gfx::gui::layout::base>	create_layout()
{

	assert(window0);
	
	auto app = neb::fin::gfx_phx::app::base::global();
	
	auto layout = app->createLayout().lock();

	layout->connect(window0);

	layout->createObjectTerminal();

	return layout;
}
scene_s		create_maze()
{
	//assert(window0);
	//assert(context1);

	auto app = neb::fin::gfx_phx::app::base::global();

	// create map
	
	auto map = app->createSceneDll("../../components/ext/hf/libnebula_ext_hf_0_so_db.so").lock();
	
	scene = map;

	// player's actor
	actor_player = std::dynamic_pointer_cast<actor_dyn_t>(loadXML<neb::core::core::actor::base>("actor_player.xml"));
	scene->addActor(actor_player);


	// weapon
	if(window0)
	{
		auto weap = actor_player->createWeaponSimpleProjectile(window0, 0.2, 10.0, 5.0);

		// camera

		actor_player->createControlManual(window0);

		environ1 = neb::is<neb::gfx::environ::base, neb::gfx::environ::SceneDefault>(context1->environ_);

		environ1->createViewridealong(actor_player);
	}	
	//	light->initShadow(environ1);

	//create_enemy();


	return map;
}
int			main()
{
	makeDefaultFunc<neb::core::core::actor::desc, neb::core::core::actor::desc>();
	makeDefaultFunc<neb::core::core::actor::desc, neb::core::core::actor::rigidbody::desc>();
	makeDefaultFunc<neb::core::core::actor::base, neb::fin::gfx_phx::core::actor::rigiddynamic::base>();
	makeDefaultFunc<neb::core::core::shape::base, neb::fin::gfx_phx::core::shape::base>();
	makeDefaultFunc<neb::core::core::shape::base, neb::fin::gfx_phx::core::shape::box>();
	makeDefaultFunc<neb::core::light::__base, neb::gfx::core::light::spot>();




	app = neb::fin::gfx_phx::app::base::init();


	window0 = app->createWindow().lock();

	context1 = window0->createContextThree().lock();
	context2 = window0->createContextTwo().lock();

	auto layout = create_layout();

	context2->setDrawable(layout);

	neb::game::game::desc gameDesc;

	game = app->createGame(gameDesc);

	// scene

	//auto scene = create_scene(window, context, enemy);
	scene = std::dynamic_pointer_cast<neb::fin::gfx_phx::core::scene::base>(
			create_maze()
			);
	assert(scene);

	game->scene_ = scene;

	context1->setDrawable(scene);


	app->loop();


}





