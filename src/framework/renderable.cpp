#include <chrono>

#include <jess/ostream.hpp>
#include <jess/free.hpp>

#include <nebula/define.hpp>
#include <nebula/ns.hpp>

#include <nebula/framework/app.hpp>
#include <nebula/platform/renderer/base.hpp>

#include <nebula/framework/renderable.hpp>

n10000::renderable::renderable():
	count_(0),
	total_count_(0),
	interval_(1),
	fps_(0),
	clock_(0),
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
	std::chrono::time_point<std::chrono::high_resolution_clock> next = std::chrono::high_resolution_clock::now();
	
	while(1)
	{
		std::this_thread::sleep_until( next );
		next += std::chrono::seconds(1);
		
		std::lock_guard<std::mutex> lg( mutex_ );
		
		fps_ = count_;
		count_ = 0;
		clock_++;
	}
}
void	n10000::renderable::render()
{
	std::lock_guard<std::mutex> lg( mutex_ );
	
	count_++;
	total_count_++;
}
