#ifndef __MATH_GEO_HEIGHT_MAP_HPP__
#define __MATH_GEO_HEIGHT_MAP_HPP__


namespace math {
	namespace geo {
		class vertex;
		class tri;

		class height_map {
			public:
				height_map(int,int);

				vertex*	vertices_;
				tri*	tris_;
		};
	}
}




#endif
