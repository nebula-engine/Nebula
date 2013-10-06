#include <jess/ostream.hpp>
#include <jess/free.hpp>

#include <nebula/define.hpp>
#include <nebula/platform/window/base.hpp>
#include <nebula/platform/renderer/base.hpp>
#include <nebula/content/camera.hpp>
#include <nebula/content/scene/admin/base.hpp>
#include <nebula/content/view/admin/base.hpp>

ncva::base::base()
{
	
}
ncva::base::~base()
{

}
void	ncva::base::init( jess::shared_ptr<nc_sc_a::base>& parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	parent_ = parent;
}
void	ncva::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	ncva::base::update()
{

}
void	ncva::base::render()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	jess::shared_ptr<npr::base> rnd = window_->renderer_;
	
	rnd->begin_render();

	camera_->render( rnd );
	
	rnd->light();
	
	parent_.lock()->render( rnd );
	
	rnd->end_render();

}
void	ncva::base::create_camera()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	camera_.reset( new nc::camera );
}


