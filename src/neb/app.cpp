#include <algorithm>

#include <glutpp/renderable.h>


#include <neb/app.h>
#include <neb/window.h>
#include <neb/view.h>
#include <neb/physics.h>

neb::app::app()
{
}
void	neb::app::init() {
}
int	neb::app::create_window(int name, int w, int h, int x, int y, char const * title) {

	windows_[name] = glutpp::__master.create_window<neb::window>(w,h,x,y,title);
	
	windows_[name]->app_ = shared_from_this();

	return 0;
}
int	neb::app::load_scene(int name, char const * filename)
{
	tinyxml2::XMLDocument document;
	if(document.LoadFile(filename))
	{
		printf ("XML file not found\n");
		exit(0);
	}
	
	tinyxml2::XMLElement* el_scene = document.FirstChildElement("scene");
	
	
	// scene
	auto scene = neb::__physics.Create_Scene(el_scene);
	scene->user_type_ = neb::scene::LOCAL;
	
	scenes_[name] = scene;

	return 0;
}
int	neb::app::load_layout(int name, char const * filename) {

	tinyxml2::XMLDocument document;
	if(document.LoadFile(filename))
	{
		printf ("XML file not found\n");
		exit(0);
	}
	
	tinyxml2::XMLElement* element = document.FirstChildElement("layout");
	
	std::shared_ptr<glutpp::gui::layout> layout(new glutpp::gui::layout);
	layout->load_xml(element);
	
	layouts_[name] = layout;
	
	return 0;
}
int	neb::app::activate_scene(int name_window, int name_scene)
{	
	printf("%s\n", __PRETTY_FUNCTION__);
	
	auto w = windows_[name_window];
	auto s = scenes_[name_scene];
	
	assert(w);
	assert(s);
	
	w->set_scene(s);
	
	return 0;
}
int	neb::app::activate_layout(int name_window, int name_layout)
{
	printf("%s\n", __PRETTY_FUNCTION__);

	auto w = windows_[name_window];
	auto l = layouts_[name_layout];

	assert(w);
	assert(l);
	
	w->set_layout(l);
	
	return 0;
}
void    neb::app::step(double time)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	
	std::shared_ptr<neb::scene> scene;
	
	for(auto it = scenes_.begin(); it != scenes_.end(); ++it)
	{
		scene = it->second;
		
		assert(scene);
		
		scene->step(time);
	}

}
int	neb::app::prepare() {
	
	for(auto it = windows_.begin(); it = windows_.end(); ++it)
	{
		if(it->second) it->second->prepare();
	}
	
	return 0;
}
int	neb::app::loop() {

	while(1)
	{

		time = glfwGetTime();
		
		
		auto it = windows_.begin();
		while(it != windows_.end())
		{
			assert(it->second);
			if(it->second->step(time))
			{
				windows_.erase(it);
			}
			else
			{
				++it;
			}
		}

		glfwPollEvents();

	}

	return 0;
}





