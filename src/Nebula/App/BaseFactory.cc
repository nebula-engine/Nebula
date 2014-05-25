#include <Nebula/App/BaseFactory.hh>

std::shared_ptr<Neb::App::BaseFactory>		Neb::App::BaseFactory::g_app_;

Neb::App::BaseFactory_s				Neb::App::BaseFactory::global() {
	return g_app_;
}

template<> std::shared_ptr< Neb::Factory<Neb::Graphics::Window::Base> >		Neb::App::BaseFactory::getFactoryDefault<Neb::Graphics::Window::Base>() {
	return factories_.window_base_;
}
template<> std::shared_ptr< Neb::Factory<Neb::Graphics::GUI::Object::Base> >	Neb::App::BaseFactory::getFactoryDefault<Neb::Graphics::GUI::Object::Base>() {
	return factories_.gui_object_base_;
}
template<> std::shared_ptr< Neb::Factory<Neb::Scene::Base> >			Neb::App::BaseFactory::getFactoryDefault<Neb::Scene::Base>() {
	return factories_.scene_base_;
}
template<> std::shared_ptr< Neb::Factory<Neb::Actor::Base> >			Neb::App::BaseFactory::getFactoryDefault<Neb::Actor::Base>() {
	return factories_.actor_base_;
}
template<> std::shared_ptr< Neb::Factory<Neb::Shape::Base> >			Neb::App::BaseFactory::getFactoryDefault<Neb::Shape::Base>() {
	return factories_.shape_base_;
}
template<> std::shared_ptr< Neb::Factory<Neb::Light::Base> >			Neb::App::BaseFactory::getFactoryDefault<Neb::Light::Base>() {
	return factories_.light_base_;
}




