#include <neb/core/shape/Util/Types.hh>
#include <neb/core/shape/Util/Cast.hh>
#include <neb/core/shape/Base.hh>


sp::shared_ptr<neb::core::shape::base>			neb::core::shape::util::cast::isShapeBase() {
        return sp::dynamic_pointer_cast<neb::core::shape::base>(shared_from_this());
}


