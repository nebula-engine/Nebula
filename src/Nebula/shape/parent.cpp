#include <Nebula/Actor/Base.hpp>
#include <Nebula/shape/parent.hpp>

Neb::weak_ptr<Neb::Actor::Base>			Neb::Shape::parent::isActor() {
	
	Neb::weak_ptr<Neb::Actor::Base> a = boost::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());
	
	return a;
}
Neb::weak_ptr<Neb::Shape::shape>		 Neb::Shape::parent::isShape() {
	
	Neb::weak_ptr<Neb::Shape::shape> s = boost::dynamic_pointer_cast<Neb::Shape::shape>(shared_from_this());
	
	return s;
}


