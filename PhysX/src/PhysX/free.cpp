#include <PhysX/app/base.hpp>
#include <PhysX/free.hpp>

void	phx::init() {

		phx::app::base::g_app_.reset(new phx::app::base());
		

	}
