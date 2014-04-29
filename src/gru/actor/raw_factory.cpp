
#include <gru/actor/raw.hpp>
#include <gru/actor/raw_factory.hpp>
#include <gru/config.hpp>

boost::shared_ptr<glutpp::actor::raw> glutpp::actor::raw_factory::create(int type) {

	boost::shared_ptr<glutpp::actor::raw> raw;

	switch(type) {
		case glutpp::actor::type::e::ACTOR:
			raw.reset(new glutpp::actor::raw);
			return raw;
		default:
			printf("invalid raw type %i\n", type);
			abort();
	}
}




