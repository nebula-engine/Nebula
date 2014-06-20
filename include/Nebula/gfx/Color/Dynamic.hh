#ifndef color_DYNAMIC_HPP__
#define color_DYNAMIC_HPP__

#include <stdlib.h>

#include <math/color.hpp>

namespace math {
	namespace Color {
		template <typename T, class R, class G, class B> class Dynamic: math::Color::color<T> {
			public:
			/*	struct type {
					enum e: char {
						CONST,
						SINE,
						SAW,
						SQUARE,
					};
				};*/
				
				Dynamic() {
					//fr = fg = fb = 0.0;
					//tr = tg = tb = type::e::CONST;
				}
				Dynamic(T nr, T ng, T nb, T na): color<T>(nr,ng,nb,na) {}
				Dynamic(T newr, T newg, T newb, T newA, char newtr, char newtg, char newtb) {
					/*
					tr = newtr;
					tg = newtg;
					tb = newtb;

					switch(tr)
					{
						case type::e::SINE:
							r = 0.0;
							fr = newr;
							break;
						case type::e::SAW:
							r = 0.0;
							fr = newr;
							break;
						case type::e::CONST:
						default:
							r = newr;
							fr = 0.0;
							break;

					}
					switch(tb)
					{
						case type::e::SINE:
							b = 0.0;
							fb = newb;
							break;
						case type::e::SAW:
							b = 0.0;
							fb = newb;
							break;
						case type::e::CONST:
						default:

							b = newb;
							fb = 0.0;
							break;

					}
					switch(tr)
					{
						case type::e::SINE:
							g = 0.0;
							fg = newg;
							break;
						case type::e::SAW:
							g = 0.0;
							fg = newg;
							break;
						case type::e::CONST:
						default:
							g = newg;
							fg = 0.0;
							break;

					}

					a = newA;
					*/
				}
				Dynamic(const color<T> & rhs): color<T>(rhs) {

				/*	fr = rhs.fr;
					fg = rhs.fg;
					fb = rhs.fb;
					tr = rhs.tr;
					tg = rhs.tg;
					tb = rhs.tb;*/
				}


				~Dynamic() {}
			
				void			step(T time) {
					//MATH_DEBUG_1_FUNCTION;
					
					color<T>::r = r_.step(time);
					color<T>::g = g_.step(time);
					color<T>::b = b_.step(time);
					/*
					switch(tr) {
						case type::e::CONST:
							break;
						case type::e::SINE:
							r = 0.5 * sin(2.0 * M_PI * fr * time) + 0.5;
							printf("sine r = %f\n", r);
							break;
						case type::e::SAW:
							r = saw(time, fr);
							break;

					}
					switch(tg) {
						case type::e::CONST:
							break;
						case type::e::SINE:
							g = 0.5 * sin(2.0 * M_PI * fg * time) + 0.5;
							printf("g = %f\n", g);
							break;
						case type::e::SAW:
							g = saw(time, fg);
							break;
					}
					switch(tb) {
						case type::e::CONST:
							break;
						case type::e::SINE:
							b = 0.5 * sin(2.0 * M_PI * fb * time) + 0.5;
							break;
						case type::e::SAW:
							b = saw(time, fb);
							break;
					}*/

				}
				math::Color::color<T>		operator*(T f) {
					math::Color::color<T> ret(*this);
					ret *= f;
					return ret;
				}
				operator T* () const {
					return (T*)this;
				}
				operator T const * () const {
					return (T*)this;
				}

				//constructors
			public:
				R	r_;
				G	g_;
				B	b_;

				/*
				T	fr;
				T	fg;
				T	fb;
				char	tr;
				char	tg;
				char	tb;	*/
		};
	}
}

#endif


