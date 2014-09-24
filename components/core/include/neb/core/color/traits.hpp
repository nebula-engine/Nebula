#ifndef GRU_color_TRAITS_HPP
#define GRU_color_TRAITS_HPP

<<<<<<< HEAD
=======
#include <iostream>
#include <iomanip>
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

namespace neb { namespace core { namespace color {

	template<int BITS> struct uchar;
	
	template<typename T> struct traits {};
<<<<<<< HEAD

	template<> struct traits< uchar<6> > {
=======
	
	template<int BITS> struct traits< uchar<BITS> >
	{
		typedef unsigned char		pod;
		static const unsigned int	p = pow(2,BITS);
		static const unsigned int	bits = BITS;
		static const unsigned char	min = 0;
		static const unsigned char	max = p - 1;
		static const unsigned char	rand() {
			return ::rand() % p;
		}

	};

	/*
	template<> struct traits< uchar<6> > {
		typedef unsigned char		pod;
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
		static const unsigned int	bits = 6;
		static const unsigned char	min = 0;
		static const unsigned char	max = 63;
	};

	template<> struct traits< uchar<8> > {
		static const unsigned int	bits = 8;
		static const unsigned char	min = 0;
		static const unsigned char	max = 255;
	};
<<<<<<< HEAD


	
	template<int BITS> struct uchar {
=======
*/

	
	template<int BITS> struct uchar {
		uchar() {}
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
		uchar(unsigned char nc) {
			if(nc > traits< uchar<BITS> >::max) {
				c = traits< uchar<BITS> >::max;
			} else {
				c = nc;
			}
		}
<<<<<<< HEAD
		unsigned char c;
	};

	struct uchar6: uchar<6> {
		uchar6(unsigned char nc): uchar<6>(c) {}
	};

	struct uchar8: uchar<8> {
		uchar8(unsigned char nc): uchar<8>(c) {}
	};


	template<> struct traits<uchar6> {
		static const unsigned int	bits = 6;
		static const unsigned char	min = 0;
		static const unsigned char	max = 63;
		static const unsigned char	rand() {
			return ::rand() % 64;
		}
	};

	template<> struct traits<uchar8> {
		static const unsigned int	bits = 8;
		static const unsigned char	min = 0;
		static const unsigned char	max = 255;
		static const unsigned char	rand() {
			return ::rand() % 256;
		}
	};
=======
		uchar(uchar<BITS> const & uc): c(uc.c) {}
		uchar<BITS>&	operator=(uchar<BITS> const & uc)
		{
			c = uc.c;
			return *this;
		}
		operator unsigned int() const
		{
			return (unsigned int)c;
		}
		operator unsigned char() const
		{
			return c;
		}
		unsigned int	operator<<(unsigned int s) const
		{
			return (unsigned int)c << s;
		}
		unsigned char	c;
	};

	typedef uchar<6> uchar6;
	typedef uchar<8> uchar8;
/*
	struct uchar6: uchar<6> {
		uchar6(): uchar<6>(0) {}
		uchar6(unsigned char nc): uchar<6>(c) {}
		uchar6&		operator=(uchar6 const & uc)
		{
			c = uc.c;
		}
	};

	struct uchar8: uchar<8> {
		uchar8(): uchar<8>(0) {}
		uchar8(unsigned char nc): uchar<8>(c) {}
		uchar8&		operator=(uchar8 const & uc)
		{
			c = uc.c;
		}
	};
*/
	/*
	template<> struct traits<uchar6> {
		typedef unsigned char		pod;
		static const unsigned int	bits = 6;
		static const pod		min = 0;
		static const pod		max = 63;
	};

	template<> struct traits<uchar8> {
		typedef unsigned char		pod;
		static const unsigned int	bits = 8;
		static const pod		min = 0;
		static const pod		max = 255;
		static const pod		rand() {
			int r = ::rand();
			int x = r % 256;
			std::cout
				<< __PRETTY_FUNCTION__
				<< std::setw(16) << r
				<< std::setw(16) << x
				<< std::endl;
				
			return x;
		}
	};
*/
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

	template<> struct traits<float> {
		static const unsigned int	bits = 32;
		static constexpr float		min = 0.0f;
		static constexpr float		max = 1.0f;
		static const float		rand() {
			return (float)(::rand() % 256) / 256.0f;
		}
	};

}}}

#endif

