#ifndef __NEBULA_SHARED_PTR_HPP__
#define __NEBULA_SHARED_PTR_HPP__

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace nebula
{
	template <class T> class shared_ptr
	{
	public:
		
		/// create
		template <class U> void							create(boost::function<void(boost::shared_ptr<U>)>);
		
		
		
		/// boost shared_ptr
		boost::shared_ptr<T>							pointer_;
	};
}


#endif

