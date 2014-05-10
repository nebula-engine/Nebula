#include <Nebula/Typed.hpp>

Neb::Typed::hash_type const &           Neb::Typed::hash_code() const {
        std::type_index type(typeid(*this));
        return type.hash_code();
}
std::string const &                     Neb::Typed::name() const {
        std::type_index type(typeid(*this));
        return type.name();
}

