#include <gal/itf/registry.hpp>
#include <gal/itf/shared.hpp>


gal::itf::registry::registry(): next_(0) {
}
void                                            gal::itf::registry::reg(std::shared_ptr<gal::itf::shared> s) {
	std::cout << __PRETTY_FUNCTION__ << " s=" << s.get() << std::endl;

	if(s->_M_index == -1) s->_M_index = next_++;

	map_[s->_M_index] = s;
}
std::shared_ptr<gal::itf::shared>		gal::itf::registry::get(gal::itf::index_type i) {
	auto it = map_.find(i);

	if(it == map_.cend()) return std::shared_ptr<gal::itf::shared>();

	return it->second.lock();
}





