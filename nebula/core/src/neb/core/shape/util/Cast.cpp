#include <neb/core/shape/util/Types.hh>
#include <neb/core/shape/util/Cast.hh>
#include <neb/core/shape/base.hpp>


sp::shared_ptr<neb::core::shape::base>			neb::core::shape::util::cast::isShapeBase() {
        return sp::dynamic_pointer_cast<neb::core::shape::base>(shared_from_this());
}


