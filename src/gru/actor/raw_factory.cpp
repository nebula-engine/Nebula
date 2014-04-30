
#include <gru/actor/raw.hpp>
#include <gru/actor/raw_factory.hpp>
#include <gru/config.hpp>

using namespace std;

void glutpp::actor::raw_factory::reset(boost::shared_ptr<glutpp::actor::raw> & raw, glutpp::actor::Type type) {
	
	switch(type.val_) {
		case glutpp::actor::Type::E::ACTOR:
			raw.reset(new glutpp::actor::raw);
			return;
		default:
			cout << "invalid actor type " << type.val_ << endl;
			abort();
	}
}




