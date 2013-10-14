#include <jess/ostream.hpp>
#include <jess/free.hpp>

#include <nebula/define.hpp>
#include <nebula/platform/window/base.hpp>
#include <nebula/platform/renderer/base.hpp>
#include <nebula/content/camera.hpp>
#include <nebula/content/scene/admin/base.hpp>
#include <nebula/ui/layout/base.hpp>

#include <nebula/content/view/admin/base.hpp>

n33100::base::base() // invalid write stems from here
{
	
}
n33100::base::~base()
{

}
void	n33100::base::init( jess::shared_ptr<n32100::base> parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	parent_ = parent;

	n10000::renderable::init();
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


	n10000::renderable::render();
	
	
	
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
	
	// text
	char str[16];

	sprintf( str, "fps    %3i", fps_ );
	rnd->draw_text( 100, 200, str );
	
	sprintf( str, "frames %3i", total_count_ );
	rnd->draw_text( 100, 250, str );
	
	sprintf( str, "clock  %3i", clock_ );
	rnd->draw_text( 100, 300, str );

	
	
	rnd->end_2d();
	rnd->end_render();

}
void	n33100::base::create_camera()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	camera_.reset( new n30000::camera );
}


