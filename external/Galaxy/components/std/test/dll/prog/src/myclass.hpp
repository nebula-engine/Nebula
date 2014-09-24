#ifndef __MYCLASS_H__
#define __MYCLASS_H__

#include <iostream>

class MyClass {
	public:
		MyClass() {}
		virtual ~MyClass() {}

		void	release() { std::cout << "release" << std::endl; }

		/* use virtual otherwise linker will try to perform static linkage */
		virtual void DoSomething() = 0;

	protected:
		int x;
};



#endif

