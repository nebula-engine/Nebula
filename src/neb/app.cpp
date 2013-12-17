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

	window_->renderable_->scene_->set(glutpp::scene::SHADER);
	window_->renderable_->scene_->set(glutpp::scene::LIGHTING);

	window_->renderable_->scene_->shaders();
	window_->renderable_->scene_->uniforms();



	//w.set(glutpp::scene::SHADOW);


}
void	neb::app::load(char const * filename)
{
	TiXmlDocument document(filename);
	if ( !document.LoadFile() )
	{
		printf ("XML file not found\n");
		exit(0);
	}

	TiXmlElement* el_scene = document.FirstChildElement("scene");



	scene_ = neb::__physics.Create_Scene(el_scene);
	scene_->user_type_ = neb::scene::LOCAL;
	
	
	view_.reset(new neb::view);
	
	view_->scene_ = scene_;
	scene_->view_ = view_;
	
	
	view_->set_window(window_);
	
}
void    neb::app::step(double time)
{
	printf("%s\n", __PRETTY_FUNCTION__);

	assert(scene_);

	scene_->step(time);
}





