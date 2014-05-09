#ifndef GRU_FREE_HPP
#define GRU_FREE_HPP

#include <memory>

#include <Nebula/Graphics/Color/Color.hpp>

namespace Neb {
	void	draw_quad(float, float, float, float, Neb::Color::color<float>);
	void	draw_text(float, float, float, float, Neb::Color::color<float>, std::string);
}

void	checkerror(char const *);
bool	isGLError();

template<class A> A*	new_copy(std::shared_ptr<A> a) {
	if(a) {
		return new A(*a);
	}
       	return NULL;
}

#endif

