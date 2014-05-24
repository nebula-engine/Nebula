#include <Nebula/App/BaseFactory.hh>

std::shared_ptr<Neb::App::BaseFactory>		Neb::App::BaseFactory::g_app_;

Neb::App::BaseFactory_s				Neb::App::BaseFactory::global() {
	return g_app_;
}


template<> std::shared_ptr< Neb::Factory< Neb::Actor::Base > >		Neb::App::BaseFactory::getFactoryDefault<Neb::Actor::Base>() {
	return factories_.actor_base_;
}




