#ifndef __NEBULA_FRAMEWORK_TIME_TIMER_MANAGER_HPP__
#define __NEBULA_FRAMEWORK_TIME_TIMER_MANAGER_HPP__

#include <nebula/ns.hpp>

namespace nebula
{
namespace framework
{
namespace time
{
class timer_manager
{
public:
void				insert( n11000::timer );
private:
/// parent
std::weak_ptr<n10000::app>	parent_;
/// timers
std::set<n11000::timer>		timers_;
};
}
}
}

#endif
