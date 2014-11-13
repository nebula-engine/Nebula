#ifndef __MYCLASS1_H__
#define __MYCLASS1_H__

#include "../../prog/src/myclass.hpp"

class MyClass1: public MyClass {
	public:
		MyClass1();
		virtual ~MyClass1();

		/* use virtual otherwise linker will try to perform static linkage */
		virtual void DoSomething();

	private:
		int y;
};

#endif
