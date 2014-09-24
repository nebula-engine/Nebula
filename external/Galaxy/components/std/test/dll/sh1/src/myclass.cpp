

#include <iostream>


#include "myclass.hpp"

using namespace std;



extern "C" MyClass* MyClass_create()
{
	  return new MyClass1;
}

extern "C" void MyClass_destroy( MyClass* object )
{
	  delete object;
}

MyClass1::MyClass1()
{
	  x = 40;
}

void MyClass1::DoSomething()
{
	  cout<< x <<endl;
}


