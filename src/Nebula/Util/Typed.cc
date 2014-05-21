#include <Nebula/Util/Typed.hh>

Neb::Util::Typed::hash_type			Neb::Util::Typed::hash_code() const {
        std::type_index type(typeid(*this));
        return type.hash_code();
}
std::string					Neb::Util::Typed::name() const {
        std::type_index type(typeid(*this));
        return type.name();
}

