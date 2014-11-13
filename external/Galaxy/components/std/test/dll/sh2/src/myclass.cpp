#include <iostream>

#include "myclass.hpp"

// custom functionality and data

extern "C" MyClass* MyClass_create()
{
	  return new MyClass1;
}
extern "C" void MyClass_destroy( MyClass* object )
{
	MyClass1* c1 = (MyClass1*)object;
	delete c1;
}





MyClass1::~MyClass1() {
	std::cout << "MyClass1 destroy" << std::endl;
}



MyClass1::MyClass1()
{
	  y = 21;
}

void MyClass1::DoSomething()
{
	  std::cout << x << " " << y << std::endl;
}



