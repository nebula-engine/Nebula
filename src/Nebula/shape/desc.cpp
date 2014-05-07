
//#include <math/free.hpp>


#include <Nebula/config.hpp>
#include <Nebula/shape/desc.hpp>
#include <Nebula/shape/shape.hpp>
#include <Nebula/Graphics/light/desc.hpp>
#include <Nebula/Graphics/light/light.hpp>


glutpp::shape::desc::desc() {
	GLUTPP_DEBUG_0_FUNCTION;
}
glutpp::shape::desc &		glutpp::shape::desc::operator<<(Neb::unique_ptr<glutpp::shape::shape> const & shape) {

	/** @todo fill this out */

	return *this;	
}









