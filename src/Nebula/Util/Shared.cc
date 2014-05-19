#include <Nebula/Util/Shared.hh>

Neb::Util::Shared::Shared() {
	registry_.reg(shared_from_this());
}
Neb::Util::Shared::Shared(Neb::Util::index_type) {
	registry_.reg(shared_from_this(), i);
}



