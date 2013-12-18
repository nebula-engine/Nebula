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
int	neb::app::load_scene(int name, char const * filename)
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

	return 0;
}
int	neb::app::load_layout(int name, char const * filename) {

	TiXmlDocument document(filename);
	if ( !document.LoadFile() )
	{
		printf ("XML file not found\n");
		exit(0);
	}
	
	TiXmlElement* element = document.FirstChildElement("layout");
	
	std::shared_ptr<glutpp::gui::layout> layout(new glutpp::gui::layout);
	layout->load_xml(element);
	
	layouts_[name] = layout;
	
	return 0;
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
int	neb::app::activate_layout(int name)
{
	assert(window_);
	
	auto it = layouts_.find(name);
	if(it == layouts_.end())
	{
		printf("layout '%i' not found\n", name);
		exit(0);
	}
	
	window_->set_layout(it->second);
	
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





