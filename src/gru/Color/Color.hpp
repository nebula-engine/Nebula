#ifndef GRU_color_HPP
#define GRU_color_HPP

#include <cstdlib>
#include <cstdio>
#include <cmath>

namespace gru {
	namespace Color {
		template <typename T> class color {
			public:
				struct type {
					enum e: char {
						CONST,
						SINE,
						SAW,
						SQUARE,
					};
				};

				/** @name Constructor
				 * @{
				 */
				color() {
					r = g = b = a = 0.0f;
					//fr = fg = fb = 0.0;
					//tr = tg = tb = type::e::CONST;
				}
				color(T newR, T newG, T newB, T newA) {
					r = newR;
					g = newG;
					b = newB;
					a = newA;
				}
				color(const color & rhs) {
					r = rhs.r;
					g = rhs.g;
					b = rhs.b;
					a = rhs.a;
				}
				/** @} */
				~color()
				{
				}
				void		set(T newR, T newG, T newB, T newA) {
					r=newR;
					g=newG;
					b=newB;
					a=newA;
				}
				color<T>	rand() {
					color ret;
					ret.r = (T)(::rand() % 1000) / 1000.0f;
					ret.g = (T)(::rand() % 1000) / 1000.0f;
					ret.b = (T)(::rand() % 1000) / 1000.0f;
					ret.a = 1.0;
					return ret;
				}
				void		setBlack() {
					r = g = b = a = 1.0f;
				}
				void		setWhite() {
					r = g = b = 0.0f;
					a = 1.0f;
				}
				void		setGrey(T shade) {
					r = g = b = shade;
					a = 1.0f;
				}
				color<T>		lerp(const color & c2, T factor) {
					return ((*this) * (1.0f - factor) + c2 * factor);
				}
				color<T>		operator+(const color & rhs) const {
					return color(r+rhs.r, g+rhs.g, b+rhs.b, a+rhs.a);
				}
				color<T>		operator-(const color & rhs) const {
					return color(r-rhs.r, g-rhs.g, b-rhs.b, a-rhs.a);
				}
				color<T>		operator*(const color & rhs) const {
					return color(r*rhs.r, g*rhs.g, b*rhs.b, a*rhs.a);
				}
				color<T>		operator/(const color & rhs) const {
					return color(r/rhs.r, g/rhs.g, b/rhs.b, a/rhs.a);
				}
				color<T>		operator*(const T rhs) const {
					return color(r*rhs, g*rhs, b*rhs, a*rhs);
				}
				color<T>		operator/(const T rhs) const {
					return color(r/rhs, g/rhs, b/rhs, a/rhs);
				}
				bool			operator ==(color<T> const & rhs) const {
					if(r != rhs.r) return false;
					if(g != rhs.g) return false;
					if(b != rhs.b) return false;
					if(a != rhs.a) return false;

					return true;
				}
				bool			operator!=(color<T> const & rhs) const {
					return !((*this)==rhs);
				}
				color<T>		operator+=(color<T> const & rhs) {
					r += rhs.r;
					g += rhs.g;
					b += rhs.b;
					a += rhs.a;

					return (*this);
				}
				color<T>		operator-=(color<T> const & rhs) {
					(*this)=(*this)-rhs;
					return (*this);
				}
				color<T>		operator*=(const color & rhs) {
					(*this)=(*this)*rhs;	return (*this);
				}
				color<T>		operator/=(const color & rhs) {
					(*this)=(*this)/rhs;	return (*this);
				}
				color<T>		operator*=(const T rhs) {
					(*this)=(*this)*rhs;	return (*this);
				}
				color<T>		operator/=(const T rhs) {
					(*this)=(*this)/rhs;
					return (*this);
				}
				color<T>		operator-() const {
					return color(-r,-g, -b, -a);
				}
				color<T>		operator+() const{
					return (*this);
				}
				void			clampTo01() {
					if(r>1.0f) r=1.0f;
					if(r<0.0f) r=0.0f;

					if(g>1.0f) g=1.0f;
					if(g<0.0f) g=0.0f;

					if(b>1.0f) b=1.0f;
					if(b<0.0f) b=0.0f;

					if(a>1.0f) a=1.0f;
					if(a<0.0f) a=0.0f;
				}
				void			print() {
					printf("%f %f %f %f\n",r,g,b,a);
				}

				T			saw(T t, T f) {
					T a = t*f;
					T y = a - floor(a);
					printf("saw: a = %f y = %f\n", a, y);
					return y;
				}
				/*
				void			step(T time) {
					//MATH_DEBUG_1_FUNCTION;
					
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
					}

				}
				*/

				color<T>		operator*(T f) {
					color<T> ret(*this);
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
				T	r;
				T	g;
				T	b;
				T	a;
				//T	fr;
				//T	fg;
				//T	fb;
				//char	tr;
				//char	tg;
				//char	tb;	
		};

		template<typename T> color<T> white() { return color<T>(		1.0, 1.0, 1.0, 1.0); }
		template<typename T> color<T> black() { return color<T>(		0.0, 0.0, 0.0, 1.0); }
		template<typename T> color<T> red() { return color<T>(		1.0, 0.0, 0.0, 1.0); }
		template<typename T> color<T> green() { return color<T>(		0.0, 1.0, 0.0, 1.0); }
		template<typename T> color<T> blue() { return color<T>(		0.0, 0.0, 1.0, 1.0); }
		template<typename T> color<T> cyan() { return color<T>(		0.0, 1.0, 1.0, 1.0); }
		template<typename T> color<T> magenta() { return color<T>(	1.0, 0.0, 1.0, 1.0); }
		template<typename T> color<T> yellow() { return color<T>(	1.0, 1.0, 0.0, 1.0); }
	}
}

#endif	//color_H
