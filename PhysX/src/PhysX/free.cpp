

#include <PhysX/app/base.hpp>
#include <PhysX/free.hpp>

void	phx::init() {
	
	neb::init_log();
	
	auto app(sp::make_shared<phx::app::base>());
	
	phx::app::base::g_app_ = app;
	neb::app::base::g_app_ = app;

	app->init();

}


