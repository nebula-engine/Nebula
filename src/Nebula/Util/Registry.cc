#include <Nebula/Util/Shared.hh>


Neb::Util::Registry::Registry(): next_(0) {
}
void						Neb::Util::Registry::reg(
		Neb::Util::Shared_s s)
{
	Neb::Util::index_type i = next_++;
	s->i_ = i;
	map_.emplace_back(i, s);
}
void						Neb::Util::Registry::registerExisting(
		Neb::Util::Shared_s s)
{
	map_.emplace_back(s->i_, s);
}
std::shared_ptr<Neb::Util::Shared>		Neb::Util::Registry::get(Neb::Util::index_type i) {
	auto it = map_.find(i);

	if(it == map.cend()) return Neb::Util::Shared_s;

	return it->second.lock();
}




