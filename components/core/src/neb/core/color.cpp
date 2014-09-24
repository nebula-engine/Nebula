

#include <neb/core/color/Color.hh>
#include <neb/core/color/traits.hpp>




namespace neb { namespace core { namespace color {



	//const unsigned int	struct traits<float>::bits = 32;
	
	constexpr float		traits<float>::min;
	constexpr float		traits<float>::max;

	//const unsigned char	template<> struct traits<float>::rand() {
	//	return (float)(::rand() % 1024) / 1024.0f;
	//}




	template<> uchar6			convert(float f) {
		f = clamp(f, 0.0f, 1.0f);
		return uchar6((unsigned char)(f * 64.0f));
	}

	template<> uchar8			convert(float f) {
		f = clamp(f, 0.0f, 1.0f);
		return uchar8((unsigned char)(f * 255.0f));
	}

	template<> float			convert(double f) {
		f = clamp(f, 0.0, 1.0);
		return (float)f;
	}

}}}

