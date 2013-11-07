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
	timer_fps_( &n10000::renderable::update_fps, this ),
	terminate_(false)
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
n10000::renderable::~renderable()
{
	NEB_LOG_FUNC;

	{
		std::lock_guard<std::mutex> lg( mutex_ );
		terminate_ = true;
	}

	timer_fps_.join();
}
void	n10000::renderable::init()
{
}
void	n10000::renderable::update_fps()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> next = std::chrono::high_resolution_clock::now();

	while(1)
	{
		//std::this_thread::sleep_until( next );
		next += std::chrono::seconds(1);

		std::lock_guard<std::mutex> lg( mutex_ );

		if( terminate_ )
		{
			break;
		}

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
