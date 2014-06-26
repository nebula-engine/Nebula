
#include <neb/core/free.hpp>

#include <PhysX/app/base.hpp>
#include <PhysX/free.hpp>

void	phx::init() {
	
	neb::init_log();
	
	auto app(sp::make_shared<phx::app::base>());
	
	neb::app::__base::g_app_ = app;

	app->init();

}


