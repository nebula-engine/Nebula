#include <Nebula/Actor/Base.hpp>
#include <Nebula/shape/parent.hpp>

Neb::Shape::parent::parent(): shapes_(Neb::master::global()->factories_.shape_base_) {
}
Neb::Actor::Base_w			Neb::Shape::parent::isActor() {
	
	auto a = std::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());
	
	return a;
}
Neb::Shape::shape_w			 Neb::Shape::parent::isShape() {
	
	auto s = std::dynamic_pointer_cast<Neb::Shape::shape>(shared_from_this());
	
	return s;
}


