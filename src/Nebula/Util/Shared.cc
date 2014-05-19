#include <Nebula/Util/Shared.hh>

Neb::Util::Shared::Shared() {
}
void            Neb::Util::Shared::init() {
        register_.get(shared_from_this());
}
