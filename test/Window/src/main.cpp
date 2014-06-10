
#include <Nebula/App/Base.hh>
#include <Nebula/Actor/Base.hh>
#include <Nebula/Util/wrapper.hpp>
#include <Nebula/Graphics/Context/Window.hpp>
#include <Nebula/Graphics/GUI/Object/terminal.hh>
#include <Nebula/Scene/Local.hh>

int main() {
	
	Neb::init();
	
	auto app = Neb::App::Base::globalBase();

	// window	
	auto window = sp::make_shared<Neb::Graphics::Window::Base>();

	app->Neb::Graphics::Window::Util::Parent::insert(window);
	
	window->init();
	
	// context
	auto context = sp::make_shared<Neb::Graphics::Context::Window>(window);
	
	window->insert(context);
	
	context->init();

	// drawable
	// scene
	
	auto scene = sp::make_shared<Neb::Scene::Local>(app);
	
	// layout
	auto layout = sp::make_shared<Neb::Graphics::GUI::Layout::Base>();
	
	app->Neb::Graphics::GUI::Layout::Util::Parent::insert(layout);
	
	context->drawable_ = layout;

	layout->connect(window);
	
	// object
	auto term = sp::make_shared<Neb::Graphics::GUI::Object::terminal>();

	layout->insert(term);
	
	
	
	// loop
	
	app->loop();
	
}



