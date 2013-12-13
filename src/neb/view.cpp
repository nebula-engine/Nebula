
#include <assert.h>

#include <glutpp/window.h>

#include <neb/scene.h>
#include <neb/view.h>
#include <neb/camera.h>

neb::view::view():
	scene_(NULL),
	layout_(NULL),
	window_(NULL)
{
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	neb::view::set_window(glutpp::window* window)
{	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	window_ = window;
	
	assert(window_);
	assert(scene_);
	
	for(auto it = scene_->actors_.map_.begin(); it != scene_->actors_.map_.end(); ++it)
	{
		printf("added object to window\n");
		
		neb::actor::Actor* actor = (neb::actor::Actor*)((*it).second);
		assert(actor);
		
		glutpp::object* object = actor->object_;
		
		if(object == NULL)
		{
			printf("object is NULL");
			continue;
		}
		
		window_->add_object(actor->object_);
	}
}
void	neb::view::delete_scene()
{
	delete scene_;
}

