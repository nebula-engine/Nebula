
#include <assert.h>

#include <glutpp/window.h>
#include <glutpp/renderable.h>
#include <glutpp/scene.h>

#include <neb/scene.h>
#include <neb/view.h>
#include <neb/camera.h>

neb::view::view():
	scene_(NULL)
{
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	neb::view::set_window(std::shared_ptr<glutpp::window> window)
{	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	window_ = window;
	
	assert(window);
	assert(window->renderable_);
	assert(scene_);
	
	std::shared_ptr<glutpp::scene> scene = window->renderable_->scene_;
	
	assert(scene);
	
	for(auto it = scene_->actors_.map_.begin(); it != scene_->actors_.map_.end(); ++it)
	{
		printf("added object to window\n");
		
		std::shared_ptr<neb::actor::Actor> actor =
				std::dynamic_pointer_cast<neb::actor::Actor>((*it).second);
		
		assert(actor);
		
		std::shared_ptr<glutpp::object> object = actor->object_;
		
		assert(object);
		
		scene->add_object(actor->object_);
	}
}
void	neb::view::delete_scene()
{
	scene_.reset();
}



