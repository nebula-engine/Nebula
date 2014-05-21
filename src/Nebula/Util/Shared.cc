#include <Nebula/Util/Shared.hh>

Neb::Util::Shared::Shared() {
}
void            Neb::Util::Shared::init() {
        registry_.reg(shared_from_this());
}
