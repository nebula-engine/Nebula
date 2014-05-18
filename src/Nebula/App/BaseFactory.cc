#include <Nebula/App/BaseFactory.hh>

std::shared_ptr<Neb::App::BaseFactory>		Neb::App::BaseFactory::g_app_;

Neb::App::BaseFactory_s				Neb::App::BaseFactory::global() {
	return g_app_;
}

