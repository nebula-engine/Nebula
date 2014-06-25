#ifndef NEBULA_LIGHT_SPOT_HH
#define NEBULA_LIGHT_SPOT_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <neb/config.hh>
#include <neb/util/decl.hpp>
#include <neb/util/shared.hpp>

#include <neb/math/Serialization/GLM.hpp>

#include <neb/core/light/Util/Flag.hh>
#include <neb/core/light/Util/Types.hh>

#include <neb/gfx/texture.hh>
#include <neb/core/light/Base.hh>


//#include <math/color.hpp>

namespace neb { namespace gfx { namespace core { namespace Light {


        class Point:
                virtual public neb::gfx::core::light::base
        {
                public:
                        Point(sp::shared_ptr<neb::core::light::base> parent);
                        
                        virtual void	load(neb::core::light::util::count & light_count, neb::core::pose const & pose);
                        
                        
                        
                        float	atten_const_;
                        float	atten_linear_;
                        float	atten_quad_;
        
        
        };



}}}}

#endif
