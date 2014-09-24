

#include <neb/core/app/__core.hpp>

weak_ptr<neb::app::__core>	neb::app::__core::global() {
	auto app(dynamic_pointer_cast<neb::app::__core>(g_app_));
	assert(app);
	return app;
}
void				neb::app::__core::__init() {
}
neb::core::pose			neb::app::__core::getPose() {
	return neb::core::pose();
}
neb::core::pose			neb::app::__core::getPoseGlobal() {
	return neb::core::pose();
}


