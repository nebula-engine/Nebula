
#include <neb/fnd1/app/Base00.hpp>

int			main(int ac, char ** av)
{
	auto app = neb::fnd1::app::Base00::s_init(ac, av);
	
//	int p = atoi(av[1]);
	
//	app->create_server(p);
	
	app->loop();
}



