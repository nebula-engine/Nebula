
#include <neb/fin/app/base.hpp>
#include <neb/gfx/context/Window.hpp>
#include <neb/core/game/game/desc.hpp>

int main()
{

	auto app = neb::fin::app::base::s_init();

	auto window = app->createWindow().lock();

	//auto context1 = window->createContextThree().lock();
	auto context2 = window->createContextTwo().lock();

	auto layout = app->createLayout(window, context2).lock();

	//neb::fnd::game::game::desc gameDesc;
	//game = app->createGame(gameDesc);

	// scene

	/*
	scene = std::dynamic_pointer_cast<neb::fin::core::scene::base>(
			create_maze()
			);
	assert(scene);

	game->scene_ = scene;

	context1->setDrawable(std::dynamic_pointer_cast<neb::gfx::drawable::base>(scene));
*/

	app->loop();


}



