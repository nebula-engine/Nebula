

#include <nebula/actor/raw.hpp>
#include <nebula/actor/raw_factory.hpp>

glutpp::actor::raw_s neb::actor::raw_factory::create(int type) {

	glutpp::actor::raw_s raw;

	switch(type)
	{
		case glutpp::actor::type::e::RIGID_DYNAMIC:
			raw.reset(new neb::Actor::raw);
			break;
		case glutpp::actor::type::e::RIGID_STATIC:
			raw.reset(new neb::Actor::raw);
			break;
		case glutpp::actor::type::e::EMPTY:
			raw.reset(new neb::Actor::raw);
			break;
		default:
			raw = glutpp::actor::raw_factory::create(type);
			break;
	}

	return raw;

}


