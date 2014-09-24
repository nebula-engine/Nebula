#ifndef __MYCLASS1_H__
#define __MYCLASS1_H__

#include <iostream>

#include "../../prog/src/myclass.hpp"

class MyClass1: public MyClass {
	public:
		MyClass1();
		virtual ~MyClass1() {}

		void	release() { std::cout << "release" << std::endl; }

		/* use virtual otherwise linker will try to perform static linkage */
		virtual void DoSomething();

	protected:
		int x;
};



#endif




