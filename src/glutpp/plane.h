#ifndef __GLUTPP_PLANE_H__
#define __GLUTPP_PLANE_H__

#include <math/mat44.h>
#include <math/plane.h>

namespace glutpp
{
class plane
{
        public:
                plane();
                void draw();
		
		
                int useTexture;


                math::mat44 pose_;
                math::plane plane_;
};
}

#endif



