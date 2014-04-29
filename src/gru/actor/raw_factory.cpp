
#include <gru/actor/raw.hpp>
#include <gru/actor/raw_factory.hpp>
#include <gru/config.hpp>

using namespace std;

boost::shared_ptr<glutpp::actor::raw> glutpp::actor::raw_factory::create(glutpp::actor::Type type) {

	boost::shared_ptr<glutpp::actor::raw> raw;
	
	switch(type.val_) {
		case glutpp::actor::Type::E::ACTOR:
			raw.reset(new glutpp::actor::raw);
			return raw;
		default:
			cout << "invalid actor type " << type.val_ << endl;
			abort();
	}
}




