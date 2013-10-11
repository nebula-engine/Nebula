#include <boost/chrono/system_clocks.hpp>
#include <boost/bind.hpp>

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
	fps_(0)
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
n10000::renderable::~renderable()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n10000::renderable::init()
{
	timer_fps_.reset( new boost::asio::basic_waitable_timer<boost::chrono::steady_clock>( n10000::g_io_ ) );

	//timer_fps_->expires_from_now( boost::chrono::duration<int, boost::chrono::seconds>( interval_ ) );
	timer_fps_->expires_from_now( boost::chrono::seconds( interval_ ) );

	timer_fps_->async_wait( boost::bind( &n10000::renderable::update_fps, this, boost::asio::placeholders::error ) );
}
void	n10000::renderable::update_fps( boost::system::error_code const & )
{
	fps_ = (float)count_;
	count_ = 0;
	
	timer_fps_->expires_at( timer_fps_->expires_at() + boost::chrono::seconds(1) );

	timer_fps_->async_wait( boost::bind( &n10000::renderable::update_fps, this, boost::asio::placeholders::error ) );
}
void	n10000::renderable::render()
{
	count_++;
}
