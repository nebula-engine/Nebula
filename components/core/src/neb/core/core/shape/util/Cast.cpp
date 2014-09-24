#include <neb/core/core/shape/util/decl.hpp>
#include <neb/core/core/shape/util/cast.hpp>
#include <neb/core/core/shape/base.hpp>

shared_ptr<neb::core::core::shape::base>		neb::core::core::shape::util::cast::isShapeBase() {
        return dynamic_pointer_cast<neb::core::core::shape::base>(shared_from_this());
}


