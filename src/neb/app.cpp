#include <algorithm>

#include <glutpp/renderable.h>


#include <neb/app.h>
#include <neb/window.h>
#include <neb/view.h>
#include <neb/physics.h>

neb::app::app()
{
}
void	neb::app::init()
{
	window_.reset(new neb::window(600, 600, 200, 100, "First Window"));
	
	window_->app_ = shared_from_this();
	
	window_->init();
}
void	neb::app::load_scene(int name, char const * filename)
{
	TiXmlDocument document(filename);
	if ( !document.LoadFile() )
	{
		printf ("XML file not found\n");
		exit(0);
	}
	
	TiXmlElement* el_scene = document.FirstChildElement("scene");
	
	
	// scene
	auto scene = neb::__physics.Create_Scene(el_scene);
	scene->user_type_ = neb::scene::LOCAL;
	
	scenes_[name] = scene;
	
	// view
/*	view_.reset(new neb::view);
	

	view_->scene_ = scene_;
	scene_->view_ = view_;
	
	
	view_->set_window(window_);
*/
}
int	neb::app::activate_scene(int name)
{
	assert(window_);

	auto it = scenes_.find(name);
	if(it == scenes_.end())
	{
		printf("scene '%i' not found\n", name);
		exit(0);
	}
	
	window_->set_scene(it->second);
	
	return 0;
}
void    neb::app::step(double time)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	
	
	for(auto it = scenes_.begin(); it != scenes_.end(); ++it)
	{
		it->second->step(time);
	}

}





