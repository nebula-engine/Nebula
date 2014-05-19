#include <Nebula/Util/Shared.hh>

Neb::Util::Shared::Shared() {
	registerThis(shared_from_this());
}

