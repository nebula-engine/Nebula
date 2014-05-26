#include <Nebula/Util/Shared.hh>

Neb::Util::Shared::Shared() {
}
void    				        Neb::Util::Shared::init() {
        registry_.reg(shared_from_this());
}
Neb::Util::Shared::hash_type			Neb::Util::Shared::hash_code() const {
        std::type_index type(typeid(*this));
        return type.hash_code();
}
std::string					Neb::Util::Shared::name() const {
        std::type_index type(typeid(*this));
        return type.name();
}


Neb::Util::Registry		Neb::Util::Shared::registry_;



