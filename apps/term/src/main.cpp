
#include <glm/gtc/matrix_transform.hpp>

#include <gal/console/base.hpp>

#include <gal/etc/stopwatch.hpp>

#include <neb/fnd/context/Window.hpp>
#include <neb/fnd/environ/Two.hpp>

#include <neb/fnd1/app/Base00.hpp>

int			main(int ac, char ** av)
{
	auto app = neb::fnd1::app::Base00::s_init(ac, av);

	auto window = app->create_window().lock();

	auto context = window->createContextWindow().lock();
	
	auto environ = context->createEnvironTwo().lock();

	auto layout = app->create_layout(window, environ).lock();

	app->loop();
}


