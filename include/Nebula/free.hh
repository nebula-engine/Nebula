#ifndef GRU_FREE_HPP
#define GRU_FREE_HPP

#include <memory>

#include <Nebula/Graphics/Color/Color.hh>

namespace neb {
	void	init();
}

namespace neb {
	void	draw_quad(float, float, float, float, neb::Color::color<float>);
	void	draw_text(float, float, float, float, neb::Color::color<float>, std::string);
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

