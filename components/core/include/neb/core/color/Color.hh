#ifndef GRU_color_HPP
#define GRU_color_HPP

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>

#include <boost/serialization/nvp.hpp>

#include <glm/glm.hpp>

#include <neb/core/color/traits.hpp>

template<typename T> T clamp(T a, T b, T c) {
	if(a > c) {
		return c;
	} else if(a < b) {
		return b;
	}
	return a;
}

namespace neb { namespace core { namespace color {


	template<typename F, typename T> T	convert(F f);



	template <typename R_, typename G_, typename B_, typename A_, typename C> class color_rgba_base {
		public:
			typedef C D;
			typedef R_ R;
			typedef G_ G;
			typedef B_ B;
			typedef A_ A;
			/** @name Constructor
			 * @{
			 */
			color_rgba_base() {
				setBlack();
			}
			color_rgba_base(R const & nR, G const & nG, B const & nB, A const & nA): r(nR), g(nG), b(nB), a(nA) {}
			color_rgba_base(R&& nR, G&& nG, B&& nB, A&& nA): r(nR), g(nG), b(nB), a(nA) {}
			color_rgba_base(const C & rhs): r(rhs.r), g(rhs.g), b(rhs.b), a(rhs.a) {}
			/** @} */
			~color_rgba_base()
			{
			}
			template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("r",r);
				ar & boost::serialization::make_nvp("g",g);
				ar & boost::serialization::make_nvp("b",b);
				ar & boost::serialization::make_nvp("a",a);
			}
			void		set(R newR, G newG, B newB, A newA) {
				r=newR;
				g=newG;
				b=newB;
				a=newA;
			}
			template<typename T> C		lerp(const C & c2, T factor) {
				return ((*this) * (1.0f - factor) + c2 * factor);
			}
			C					operator+(const C & rhs) const {
				return color_rgba(r+rhs.r, g+rhs.g, b+rhs.b, a+rhs.a);
			}
			C					operator-(const C & rhs) const {
				return color_rgba(r-rhs.r, g-rhs.g, b-rhs.b, a-rhs.a);
			}
			C					operator*(const C & rhs) const {
				return color_rgba(r*rhs.r, g*rhs.g, b*rhs.b, a*rhs.a);
			}
			C					operator/(const C & rhs) const {
				return color_rgba(r/rhs.r, g/rhs.g, b/rhs.b, a/rhs.a);
			}
			template<typename T> C		operator*(const T rhs) const {
				return color_rgba(
						r*convert<T,R>(rhs),
						g*convert<T,R>(rhs),
						b*convert<T,R>(rhs),
						a*convert<T,R>(rhs));
			}
			template<typename T> C		operator/(const T rhs) const {
				return color_rgba(
						r/convert<T,R>(rhs),
						g/convert<T,R>(rhs),
						b/convert<T,R>(rhs),
						a/convert<T,R>(rhs));
			}
			bool				operator ==(C const & rhs) const {
				if(r != rhs.r) return false;
				if(g != rhs.g) return false;
				if(b != rhs.b) return false;
				if(a != rhs.a) return false;

				return true;
			}
			bool				operator!=(C const & rhs) const {
				return !((*this)==rhs);
			}
			C				operator+=(C const & rhs) {
				r += rhs.r;
				g += rhs.g;
				b += rhs.b;
				a += rhs.a;

				return (*this);
			}
			C				operator-=(C const & rhs) {
				(*this)=(*this)-rhs;
				return (*this);
			}
			C				operator*=(const C & rhs) {
				(*this)=(*this)*rhs;	return (*this);
			}
			C				operator/=(const C & rhs) {
				(*this)=(*this)/rhs;	return (*this);
			}
			template<typename T> C		operator*=(const T rhs) {
				(*this)=(*this)*rhs;
				return (*this);
			}
			template<typename T> C		operator/=(const T rhs) {
				(*this)=(*this)/rhs;
				return (*this);
			}
			C		operator-() const {
				return color_rgba(-r,-g, -b, -a);
			}
			C		operator+() const {
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

			/*			T			saw(T t, T f) {
						T a = t*f;
						T y = a - floor(a);
						printf("saw: a = %f y = %f\n", a, y);
						return y;
						}*/
			void					setRand() {
				std::cout << __PRETTY_FUNCTION__ << std::endl;
				r = traits<R>::rand();
				g = traits<G>::rand();
				b = traits<B>::rand();
				a = traits<A>::max;
			}
			void					setBlack() {
				r = traits<R>::min;
				g = traits<G>::min;
				b = traits<B>::min;
				a = traits<A>::max;
			}
			void					setWhite() {
				r = traits<R>::max;
				g = traits<G>::max;
				b = traits<B>::max;
				a = traits<A>::max;
			}
			static C				black() {
				C c;
				c.setBlack();
				return c;
			}
			static C				white() {
				C c;
				c.setWhite();
				return c;
			}

			template<typename T> static C		gray(T shade) {
				C c(
						convert<T,R>(shade),
						convert<T,G>(shade),
						convert<T,B>(shade),
						traits<A>::max);
				return c;
			}
			static C				rand() {
				C c;
				c.setRand();
				return c;
			}
			static C				red() {
				C c(
						traits<R>::max,
						traits<G>::min,
						traits<B>::min,
						traits<A>::max);
				return c;
			}
			static C				green() {
				C c(
						traits<R>::min,
						traits<G>::max,
						traits<B>::min,
						traits<A>::max);
				return c;
			}
			static C				blue() {
				C c(
						traits<R>::min,
						traits<G>::min,
						traits<B>::max,
						traits<A>::max);
				return c;
			}
			static C				cyan() {
				C c(
						traits<R>::min,
						traits<G>::max,
						traits<B>::max,
						traits<A>::max);
				return c;
			}
			static C				magenta() {
				C c(
						traits<R>::max,
						traits<G>::min,
						traits<B>::max,
						traits<A>::max);
				return c;
			}
			static C				yellow() {
				C c(
						traits<R>::max,
						traits<G>::max,
						traits<B>::min,
						traits<A>::max);
				return c;
			}


		public:
			R	r;
			G	g;
			B	b;
			A	a;
	};

	template <typename R, typename G, typename B, typename A> class color_rgba:
		public color_rgba_base<R, G, B, A, color_rgba<R, G, B, A> >
	{
		public:
			typedef color_rgba_base<R, G, B, A, color_rgba<R, G, B, A> > BASE;
			typedef typename BASE::D D;

			color_rgba(R const & nr, G const & ng, B const & nb, A const & na): BASE(nr, ng, nb, na) {}
			color_rgba(R nr, G ng, B nb, A na): BASE(nr, ng, nb, na) {}
			color_rgba(const D & rhs): BASE(rhs) {}

	};


	template<> class color_rgba<float, float, float, float>: public color_rgba_base<float, float, float, float, color_rgba<float, float, float, float> >
	{
		public:
			typedef color_rgba_base<float, float, float, float, color_rgba<float, float, float, float> > BASE;
			typedef typename BASE::D D;
			typedef typename BASE::R R;
			typedef typename BASE::G G;
			typedef typename BASE::B B;
			typedef typename BASE::A A;

			color_rgba(): BASE() {}
			color_rgba(R const & nr, G const & ng, B const & nb, A const & na): BASE(nr, ng, nb, na) {}
			//color_rgba(R nr, G ng, B nb, A na): BASE(nr, ng, nb, na) {}
			color_rgba(const D & rhs): BASE(rhs) {}

			operator float* () const {
				return (float*)this;
			}
			operator float const * () const {
				return (float*)this;
			}
			operator glm::vec4 () const {
				return glm::vec4(r,g,b,a);
			}
	};

	template<> class color_rgba<uchar8, uchar8, uchar8, uchar8>: public color_rgba_base<uchar8, uchar8, uchar8, uchar8, color_rgba<uchar8, uchar8, uchar8, uchar8> >
	{
		public:
			typedef color_rgba_base<uchar8, uchar8, uchar8, uchar8, color_rgba<uchar8, uchar8, uchar8, uchar8> > BASE;
			typedef typename BASE::D D;
			typedef typename BASE::R R;
			typedef typename BASE::G G;
			typedef typename BASE::B B;
			typedef typename BASE::A A;

			color_rgba(): BASE() {}
			color_rgba(R const & nr, G const & ng, B const & nb, A const & na): BASE(nr, ng, nb, na) {}
			//color_rgba(R nr, G ng, B nb, A na): BASE(nr, ng, nb, na) {}
			color_rgba(const D & rhs): BASE(rhs) {}
			D&	operator=(D const & d)
			{
				r = d.r;
				g = d.g;
				b = d.b;
				a = d.a;
				return *this;
			}

			/*operator uchar8* () const {
				return (uchar8*)this;
			}
			operator uchar8 const * () const {
				return (uchar8*)this;
			}*/
			operator unsigned int () const {
				return ((unsigned int)r << 24) + ((unsigned int)g << 16) + ((unsigned int)b << 8) + (unsigned int)a;
			}
	};
	
	typedef color_rgba<float, float, float, float>		fcolor;
	typedef color_rgba<uchar8, uchar8, uchar8, uchar8>	ucolor8888;

	typedef fcolor color;

}}}

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

#endif	//color_H
