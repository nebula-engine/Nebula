//#include <math/xml.hpp>

#include <Nebula/Graphics/light/raw.hpp>

Neb::light::raw::raw():
	i_(-1),
	flag_(0),
	pos_(physx::PxVec4(0.0, 0.0, 0.0, 1.0)),
	ambient_(Neb::Color::black<float>()),
	diffuse_(Neb::Color::white<float>()),
	specular_(Neb::Color::white<float>()),
	spot_direction_(physx::PxVec3(0.0, 0.0, -1.0)),
	spot_cutoff_(10.0),
	spot_exponent_(1.0),
	spot_light_cos_cutoff_(1.0),
	atten_const_(1.0),
	atten_linear_(0.0),
	atten_quad_(0.0)
{
	//GLUTPP_DEBUG_0_FUNCTION;
}

void	Neb::light::raw::print() {

	//pos_.print();
	printf("pos_                   = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			pos_.x, pos_.y, pos_.z, pos_.w);
	printf("ambient_               = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			ambient_.r, ambient_.g, ambient_.b, ambient_.a);
	printf("diffuse_               = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			diffuse_.r, diffuse_.g, diffuse_.b, diffuse_.a);
	printf("specular_              = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			specular_.r, specular_.g, specular_.b, specular_.a);
	//spot_direction_.print();
	printf("spot_cutoff_           = % 2.1f\n", spot_cutoff_);
	printf("spot_exponent_         = % 2.1f\n", spot_exponent_);
	printf("spot_light_cos_cutoff_ = % 2.1f\n", spot_light_cos_cutoff_);
	printf("atten_const_           = % 2.1f\n", atten_const_);
	printf("atten_linear_          = % 2.1f\n", atten_linear_);
	printf("atten_quad_            = % 2.1f\n", atten_quad_);
}

