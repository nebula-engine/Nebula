#include <Nebula/Util/Shared.hh>


Neb::Util::Registry::Registry(): next_(0) {
}
void						Neb::Util::Registry::reg(Neb::Util::Shared_s s) {
	if(s->i_ == -1) s->i_ = next_++;
	
	map_.emplace_back(s->i_, s);
}
Neb::Util::Shared_s				Neb::Util::Registry::get(Neb::Util::index_type i) {
	auto it = map_.find(i);

	if(it == map.cend()) return Neb::Util::Shared_s;

	return it->second.lock();
}




