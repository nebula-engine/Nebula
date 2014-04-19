#include <neb/timer/actor.h>
#include <neb/actor/Base.h>

neb::timer::actor::actor(neb::actor::Base_s actor, neb::timer::actor::type type, double time):
        gal::timer::timer(time),
        type_(type),
        actor_(actor)
{
        assert(actor);
}
void neb::timer::actor::activate() {
        
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

