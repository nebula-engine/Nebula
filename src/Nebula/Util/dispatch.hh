#ifndef NEBULA_UTIL_DISPATCH_HH
#define NEBULA_UTIL_DISPATCH_HH

template<typename T> using shared_pointer = std::shared_ptr<T>;

struct poly_tuple_base {};

template< typename... Args > struct poly_tuple: poly_tuple_base {
	std::tuple<Args...>		tuple_;
};

struct dispatch
struct dispatch_init {
	template<class E> inline static void    visit(shared_pointer<E> e) {
		e->E::init();
	}
};
struct dispatch_release {
	template<class E> inline static void    visit(shared_pointer<E> e) {
		e->E::release();
	}
};
struct dispatch_step {
	template<class E> inline static void    visit(shared_pointer<E> e, double const & time, double const & dt) {
		e->E::step(time, dt);
	}
};



#endif





