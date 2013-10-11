#include <jess/ostream.hpp>
#include <jess/free.hpp>

#include <nebula/define.hpp>
#include <nebula/platform/window/base.hpp>
#include <nebula/platform/renderer/base.hpp>
#include <nebula/content/camera.hpp>
#include <nebula/content/scene/admin/base.hpp>
#include <nebula/ui/layout/base.hpp>

#include <nebula/content/view/admin/base.hpp>

ncva::base::base()
{
	
}
ncva::base::~base()
{

}
void	ncva::base::init( jess::shared_ptr<nc_sc_a::base> parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	parent_ = parent;

	n10000::renderable::init();
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
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n10000::renderable::render();
	
	jess::shared_ptr<npr::base> rnd = window_->renderer_;
	
	
	
	rnd->begin_render();
	rnd->begin_3d();
	
	camera_->render( rnd );

	rnd->light();
	
	// scene
	parent_.lock()->render( rnd );

	rnd->end_3d();
	rnd->begin_2d();

	if( layout_ )
	{
		layout_->render( rnd );
	}
	
	
	char str[16];
	sprintf( str, "%8.2f", fps_ );
	rnd->draw_text( 100, 200, str );
	
	
	rnd->end_2d();
	rnd->end_render();

}
void	ncva::base::create_camera()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	camera_.reset( new nc::camera );
}


