#include <glm/gtc/matrix_transform.hpp>

#include <Nebula/App/Base.hh>
#include <Nebula/Actor/Base.hh>
#include <Nebula/Util/wrapper.hpp>
#include <Nebula/Graphics/Context/Window.hpp>
#include <Nebula/Graphics/GUI/Object/terminal.hh>
#include <Nebula/Graphics/Light/Spot.hh>
#include <Nebula/Scene/Local.hh>
#include <Nebula/Shape/Box.hh>
#include <Nebula/Shape/empty.hpp>
#include <Nebula/Actor/RigidDynamic/Local.hh>


sp::shared_ptr<Neb::Graphics::Context::Window>		create_context(sp::shared_ptr<Neb::Graphics::Window::Base> window) {

	auto context = sp::make_shared<Neb::Graphics::Context::Window>(window);
	
	window->insert(context);
	
	context->init();

	return context;
}
sp::shared_ptr<Neb::Graphics::GUI::Layout::Base>	create_layout(
		sp::shared_ptr<Neb::Graphics::Window::Base> window,
		sp::shared_ptr<Neb::Graphics::Context::Window> context) {

	auto app = Neb::App::Base::globalBase();
	
	auto layout = sp::make_shared<Neb::Graphics::GUI::Layout::Base>();

	app->Neb::Graphics::GUI::Layout::Util::Parent::insert(layout);

	context->drawable_ = layout;

	layout->connect(window);

	// object
	auto term = sp::make_shared<Neb::Graphics::GUI::Object::terminal>();

	layout->insert(term);

	return layout;
}
sp::shared_ptr<Neb::Actor::RigidDynamic::Local>		create_actor(sp::shared_ptr<Neb::Scene::Local> scene) {
	auto actor = sp::make_shared<Neb::Actor::RigidDynamic::Local>(scene);
	
	scene->insert(actor);

	actor->init();
	
	// shape	
	auto shape = sp::make_shared<Neb::Shape::Box>(actor);
	
	
	actor->Neb::Shape::Util::Parent::insert(shape);
	//actor->insert(shape);
	
	
	shape->init();
	
	return actor;	
}
sp::shared_ptr<Neb::Actor::RigidDynamic::Local>		create_actor2(sp::shared_ptr<Neb::Scene::Local> scene) {
	auto actor = sp::make_shared<Neb::Actor::RigidDynamic::Local>(scene);
	
	scene->insert(actor);
	
	actor->init();
	
	// shape	
	auto shape = sp::make_shared<Neb::Shape::Empty>(actor);
	
	actor->Neb::Shape::Util::Parent::insert(shape);
	
	shape->init();
	
	// light
	auto light = sp::make_shared<Neb::Light::Point>(shape);
	
	shape->Neb::Light::Util::Parent::insert(light);
	
	light->init();

	return actor;	
}
sp::shared_ptr<Neb::Scene::Local>			create_scene(
		sp::shared_ptr<Neb::Graphics::Context::Window> context) {
	
	auto app = Neb::App::Base::globalBase();
	
	auto scene = sp::make_shared<Neb::Scene::Local>(app);
	
	app->Neb::Scene::Util::Parent::insert(scene);

	// actors
	auto actor = create_actor(scene);
	actor->pose_ = glm::translate(actor->pose_, vec3(0,0,-5));
	
	actor = create_actor(scene);
	actor->pose_ = glm::translate(actor->pose_, vec3(0,0,5));
	
	actor = create_actor(scene);
	actor->pose_ = glm::translate(actor->pose_, vec3(0,-5,0));

	actor = create_actor(scene);
	actor->pose_ = glm::translate(actor->pose_, vec3(0,5,0));

	actor = create_actor(scene);
	actor->pose_ = glm::translate(actor->pose_, vec3(-5,0,0));

	actor = create_actor(scene);
	actor->pose_ = glm::translate(actor->pose_, vec3(5,0,0));



	auto actor2 = create_actor2(scene);




	
	context->drawable_ = scene;

	return scene;
}

int main() {

	Neb::init();

	auto app = Neb::App::Base::globalBase();

	// window	
	auto window = sp::make_shared<Neb::Graphics::Window::Base>();

	app->Neb::Graphics::Window::Util::Parent::insert(window);

	window->init();

	// context
	auto context1 = create_context(window);
	//auto context2 = create_context(window);

	// drawable
	// scene

	auto scene = create_scene(context1);


	//auto layout = create_layout(window, context2);

	// loop

	app->loop();

}



