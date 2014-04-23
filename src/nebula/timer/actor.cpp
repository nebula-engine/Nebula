
#include <nebula/timer/actor.hpp>
#include <nebula/actor/Base.hpp>

neb::Timer::Actor::Actor(neb::Actor::Base_s actor, neb::Timer::Actor::Type type, double time):
        gal::timer::timer(time),
        type_(type),
        actor_(actor)
{
        assert(actor);
}
void neb::Timer::Actor::activate() {
        
        if(actor_.expired()) return;
        
        auto a = actor_.lock();
        
        switch(type_)
        {
                case RELEASE:
                        a->set(glutpp::actor::actor::flag::SHOULD_RELEASE);
                        break;
		default:
			break;
        }
        
}

