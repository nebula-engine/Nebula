
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <memory>

#include <gal/dll/helper.hpp>

#include "myclass.hpp"


using namespace std;

//MyClass*	(*create)();
//void		(*destroy)(MyClass*);

/*
void load(void*& handle,char const * filename) {
	handle = dlopen(filename, RTLD_LAZY);
	if(handle == NULL) {
		cerr << dlerror() << endl;
		exit(0);
	}

	create = (MyClass* (*)())dlsym(handle, "create_object");
	destroy = (void (*)(MyClass*))dlsym(handle, "destroy_object");

	MyClass::create_ = (MyClass* (*)())dlsym(handle, "create_object");

}
*/
int main(int argc, char **argv) {
	
	typedef gal::dll::helper<MyClass> H;

	std::shared_ptr<MyClass> c1;

	{
		std::shared_ptr<H> h1(new H("test/dll/sh1/libtest_dll_sh1_0_so_db.so", "MyClass"));
		h1->open();

		//c1.reset(h1->create(), gal::dll::deleter<H>(h1));
		c1 = h1->make_shared();
	}


	gal::dll::helper<MyClass> h2("test/dll/sh2/libtest_dll_sh2_0_so_db.so","MyClass");;
	h2.open();

	//MyClass* c1 = h1.create();
	
	
	//MyClass* c2 = h2.create();
	
	c1->DoSomething();
	//c2->DoSomething();

	//h1.destroy(c1);
	//h2.destroy(c2);

}


