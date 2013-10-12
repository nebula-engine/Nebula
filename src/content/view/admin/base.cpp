#include <jess/ostream.hpp>
#include <jess/free.hpp>

#include <nebula/define.hpp>
#include <nebula/platform/window/base.hpp>
#include <nebula/platform/renderer/base.hpp>
#include <nebula/content/camera.hpp>
#include <nebula/content/scene/admin/base.hpp>
#include <nebula/ui/layout/base.hpp>

#include <nebula/content/view/admin/base.hpp>

n33100::base::base()
{
	
}
n33100::base::~base()
{

}
void	n33100::base::init( jess::shared_ptr<n32100::base> parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	parent_ = parent;
}
void	n33100::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n33100::base::update()
{

}
void	n33100::base::render()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	jess::shared_ptr<n23000::base> rnd = window_->renderer_;


	
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

	
	rnd->end_2d();
	rnd->end_render();

}
void	n33100::base::create_camera()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	camera_.reset( new n30000::camera );
}


