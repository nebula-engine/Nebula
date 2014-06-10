
#include <Nebula/App/Base.hh>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Util/wrapper.hpp>

int main() {
	
	Neb::init();
	
	auto app = Neb::App::Base::globalBase();
	
	auto window = sp::make_shared<Neb::Graphics::Window::Base>();
	
	app->Neb::Graphics::Window::Util::Parent::insert(window);
	
	window->init();

	app->loop();
	
}



