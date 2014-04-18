#include <glutpp/actor/raw.h>
#include <glutpp/actor/raw_factory.h>
#include <glutpp/config.h>

glutpp::actor::raw_s glutpp::actor::raw_factory::create(int type) {

	glutpp::actor::raw_s raw;

	switch(type)
	{
		case glutpp::actor::type::e::ACTOR:
			raw.reset(new glutpp::actor::raw);
			return raw;
		default:
			printf("invalid raw type %i\n", type);
			abort();
	}
}




