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


sp::shared_ptr<neb::gfx::context::window>		create_context(sp::shared_ptr<neb::gfx::window::base> window) {

	auto context = sp::make_shared<neb::gfx::context::window>(window);
	
	window->insert(context);
	
	context->init();

	return context;
}
sp::shared_ptr<neb::gfx::gui::layout::base>	create_layout(
		sp::shared_ptr<neb::gfx::window::base> window,
		sp::shared_ptr<neb::gfx::context::window> context) {

	auto app = neb::App::base::global();
	
	auto layout = sp::make_shared<neb::gfx::gui::layout::base>(app);

	app->neb::gfx::gui::layout::util::parent::insert(layout);

	context->drawable_ = layout;

	layout->connect(window);

	// object
	auto term = sp::make_shared<neb::gfx::gui::object::terminal>();

	layout->insert(term);

	term->init();

	return layout;
}
sp::shared_ptr<neb::core::actor::rigiddynamic::local>		create_actor(sp::shared_ptr<neb::Scene::local> scene) {
	auto actor = sp::make_shared<neb::core::actor::rigiddynamic::local>(scene);
	
	scene->insert(actor);

	actor->init();
	
	// shape	
	auto shape = sp::make_shared<neb::core::shape::Box>(actor);
	
	
	actor->neb::core::shape::util::parent::insert(shape);
	//actor->insert(shape);
	
	
	shape->init();
	
	return actor;	
}
sp::shared_ptr<neb::core::actor::rigiddynamic::local>		create_actor2(sp::shared_ptr<neb::Scene::local> scene) {
	auto actor = sp::make_shared<neb::core::actor::rigiddynamic::local>(scene);
	
	scene->insert(actor);
	
	actor->init();
	
	// shape	
	auto shape = sp::make_shared<neb::core::shape::empty>(actor);
	
	actor->neb::core::shape::util::parent::insert(shape);
	
	shape->init();
	
	// light
	auto light = sp::make_shared<neb::Light::Point>(shape);
	
	shape->neb::Light::util::parent::insert(light);
	
	light->init();

	return actor;	
}
sp::shared_ptr<neb::Scene::local>			create_scene(
		sp::shared_ptr<neb::gfx::context::window> context) {
	
	auto app = neb::App::base::global();
	
	auto scene = sp::make_shared<neb::Scene::local>(app);
	
	app->neb::Scene::util::parent::insert(scene);

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

	neb::init();

	auto app = neb::App::base::global();

	// window	
	auto window = sp::make_shared<neb::gfx::window::base>();

	app->neb::gfx::window::util::parent::insert(window);

	window->init();

	// context
	auto context1 = create_context(window);
	auto context2 = create_context(window);

	// drawable
	// scene
	
	context1->view_->connect(window);

	

	auto scene = create_scene(context1);


	auto layout = create_layout(window, context2);

	// loop

	app->loop();

}



