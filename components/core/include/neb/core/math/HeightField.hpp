#ifndef NEB_CORE_MATH_HEIGHT_FIELD_HPP
#define NEB_CORE_MATH_HEIGHT_FIELD_HPP

namespace neb { namespace math {
	struct HeightField
	{

		HeightField(unsigned int r, unsigned int c);
		void			alloc();
		void			createRandom();
		float const		min() const;
		float const		max() const;
		int			at(int i, int j) const;
		void			filterc(float factor);
		void			filter(unsigned int width);
		void			normalize(float a, float b);
		float const		get(int i, int j) const;
		float			get(int i, int j);
		void			operator+=(HeightField const & hf);
		
		HeightField*		mipmap(int down);

		void			slope(float dx, float dy);

		float*			_M_z;
		unsigned int		_M_r;
		unsigned int		_M_c;
		float*			_M_dzdx;
		float*			_M_dzdy;
	};

}}
#endif
