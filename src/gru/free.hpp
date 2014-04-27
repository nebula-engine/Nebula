#include <math/color.hpp>

namespace glutpp {
	void	draw_quad(float, float, float, float, math::Color::color<float>);
	void	draw_text(float, float, float, float, math::Color::color<float>, char const *);
}

void	checkerror(char const *);
bool	isGLError();

