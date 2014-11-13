#include <iostream>
using namespace std;

#include <Galaxy-Standard/map.hpp>




class foo: public gal::itf::shared {
	public:
		virtual ~foo() {}
};

//template class gal::stl::factory<foo>;

//template std::shared_ptr< gal::stl::factory<foo> >	gal::stl::factory<foo>::default_factory_;

class bar: public foo {
	public:
		bar() {
			cout << "ctor " << this << endl;
		}
		virtual ~bar() {}
};

int main() {

	gal::stl::map<foo> m;

	try {
		auto b1 = std::make_shared<bar>();
		b1->init();
		m.insert(b1);
	} catch(...) {}

	auto b2 = std::make_shared<bar>();
	//b2->init();
	m.insert(b2);

	try {
		auto b3 = std::make_shared<bar>();
		b3->init();
		m.insert(b3);
	} catch(...) {}



	m.for_each<0>([] (gal::stl::map<foo>::iterator<0> it) {
			cout << it->ptr_->i_ << endl;
			});

}

