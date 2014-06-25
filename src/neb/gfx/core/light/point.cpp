#include <Galaxy-Log/log.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <neb/debug.hh>
#include <neb/app/Base.hh>
#include <neb/core/light/Spot.hh>
#include <neb/gfx/glsl/Uniform/vector.hpp>

neb::Light::Point::Point(sp::shared_ptr<neb::Light::util::parent> parent):
        neb::Light::base(parent, "lights_point"),
        atten_const_(1.0),
        atten_linear_(0.0),
        atten_quad_(0.0)
{}
void	neb::Light::Point::load(neb::core::light::util::count & light_count, neb::core::pose const & pose) {

        if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;
        
        neb::Light::base::load(light_count.point, pose);
        
        auto p = neb::app::base::global()->current_program();
        
        
        p->get_uniform_vector("lights_point.atten_const")->load(light_count.point, atten_const_);
        p->get_uniform_vector("lights_point.atten_linear")->load(light_count.point, atten_linear_);
        p->get_uniform_vector("lights_point.atten_quad")->load(light_count.point, atten_quad_);
        light_count.point++;
}

