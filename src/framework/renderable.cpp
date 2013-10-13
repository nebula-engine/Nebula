#include <jess/ostream.hpp>
#include <jess/free.hpp>

#include <nebula/define.hpp>
#include <nebula/ns.hpp>

#include <nebula/framework/app.hpp>
#include <nebula/platform/renderer/base.hpp>

#include <nebula/framework/renderable.hpp>

n10000::renderable::renderable():
	count_(0),
	interval_(1),
	fps_(0),
	timer_fps_( &n10000::renderable::update_fps, this )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
n10000::renderable::~renderable()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n10000::renderable::init()
{
}
void	n10000::renderable::update_fps()
{
	while(1)
	{
		std::this_thread::sleep_for( std::chrono::seconds(1) );

		fps_ = (float)count_;
		count_ = 0;
	}
}
void	n10000::renderable::render()
{
	count_++;
}
