#ifndef NEB_CORE_UTIL_CAST_HPP
#define NEB_CORE_UTIL_CAST_HPP

#include <memory>
#include <cassert>

namespace neb {
	
/*	// when you know that U is base of object t
	template<typename T, typename U> U*			is(T* const & t) { return 0; }
	template<typename T, typename U> std::shared_ptr<U>	is(std::shared_ptr<T> const & t) { return 0; }

	// when you are testing if U is base of object t
	template<typename T, typename U> U*			could_be(T* const & t) { return 0; }
	template<typename T, typename U> std::shared_ptr<U>	could_be(std::shared_ptr<T> const & t) { return 0; }
*/	
	
	template<typename T, typename U> U*			is(T* const & t)
	{
#if defined _DEBUG
		U* u = dynamic_cast<U*>(t);
		assert(u);
		return u;
#elif defined NDEBUG
		return static_cast<U*>(t);
#endif
	}
	template<typename T, typename U> std::shared_ptr<U>	is(std::shared_ptr<T> const & t)
	{
#if defined _DEBUG
		std::shared_ptr<U> u = std::dynamic_pointer_cast<U>(t);
		assert(u);
		return u;
#elif defined NDEBUG
		return std::static_pointer_cast<U>(t);
#endif
	}
	template<typename T, typename U> U*			could_be(T* const & t)
	{
		return  dynamic_cast<U*>(t);
	}
	template<typename T, typename U> std::shared_ptr<U>	could_be(std::shared_ptr<T> const & t)
	{
		return  std::dynamic_pointer_cast<U>(t);
	}


}

#endif

