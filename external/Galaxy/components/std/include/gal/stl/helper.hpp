#ifndef NEBULA_UTIL_HELPER_HH
#define NEBULA_UTIL_HELPER_HH

template <int...>
struct seq {};

template<int N, int... S>
struct gens: gens<N-1, N-1, S...> {};

template <int... S>
struct gens<0, S...> {
	typedef seq<S...> type;
};

template <typename... T>
void pass(T&&...) {}

template <typename... T>
void pass(T const &...) {}

#endif

