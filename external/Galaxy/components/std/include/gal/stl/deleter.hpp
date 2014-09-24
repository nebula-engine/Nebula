#ifndef GAL_DELETER
#define GAL_DELETER

namespace gal { namespace stl {

	template<typename T> struct deleter
	{
		void	operator()(T* p)
		{
			p->release();
			delete p;
		}
	};
}}

#endif
