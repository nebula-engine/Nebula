
#include <gal/stl/map.hpp>

class A: virtual public gal::itf::shared {
	public:
		virtual ~A() {}
};
class B: virtual public gal::itf::shared {
	public:
		virtual ~B() {}
};


class foo: virtual public A, virtual public B {
	public:
		virtual ~foo() {}
		virtual void	release() {}
};

gal::stl::map<foo> m;

std::weak_ptr<foo>	bar() {
	auto p = std::make_shared<foo>();
	m.insert(p);
	return p;
}

int main() {


	auto w = bar();

	if(w.expired()) {
		std::cout << "expired" << std::endl;
	} else {
		std::cout << "not expired" << std::endl;
	}

}


