#include <gal/log/log.hpp>

gal::log::base::base(std::ostream& ss): ss_(ss) {
}
gal::log::base::base(gal::log::base&& base):
	ss_(base.ss_)
{}
gal::log::base::~base() {
	ss_ << std::endl;
}

std::ostream& lg = std::cout;



