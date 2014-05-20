
#include <Neb/Grpahics/Light/Spot.hh>

Neb::Light::Spot::Spot():
	spot_direction_(physx::PxVec3(0.0, 0.0, -1.0)),
	spot_cutoff_(10.0),
	spot_exponent_(1.0),
	spot_light_cos_cutoff_(1.0)
{
}
void Neb::Light::Spot::load(int o, physx::PxMat44 space) {
	GLUTPP_DEBUG_1_FUNCTION;
	
	auto p = Neb::App::Base::globalBase()->current_program();

	physx::PxVec4 pos = pos_;

	pos += physx::PxVec4(space.getPosition(), 0);

	pos.w = pos_.w;

	physx::PxVec3 spot_direction = spot_direction_;
	
	if(raw_.spot_cutoff_ < (M_PI/2.0)) {
		//spot_direction.print();
	
		space.rotate(spot_direction);
	
		//spot_direction.print();
	}
	//pos.print();
	
	
	//if(any(Neb::light::flag::e::SHOULD_LOAD_POS))
	{
		p->get_uniform_vector("lights.position")->load(o, pos);
		
		//unset(Neb::light::flag::e::SHOULD_LOAD_POS);
	}	
	//if(any(Neb::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION))
	{
		p->get_uniform_vector("lights.spot_direction")->load(o, spot_direction);
		
		//unset(Neb::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION);
	}
	
	//if(any(Neb::light::flag::e::SHOULD_LOAD_OTHER))
	{
		p->get_uniform_vector("lights.ambient")->load(o, ambient_);
		p->get_uniform_vector("lights.diffuse")->load(o, diffuse_);
		p->get_uniform_vector("lights.specular")->load(o, specular_);
		p->get_uniform_vector("lights.spot_cutoff")->load(o, spot_cutoff_);
		p->get_uniform_vector("lights.spot_exponent")->load(o, spot_exponent_);
		p->get_uniform_vector("lights.spot_light_cos_cutoff")->load(o, spot_light_cos_cutoff_);
		p->get_uniform_vector("lights.atten_const")->load(o, atten_const_);
		p->get_uniform_vector("lights.atten_linear")->load(o, atten_linear_);
		p->get_uniform_vector("lights.atten_quad")->load(o, atten_quad_);

		//unset(Neb::light::flag::e::SHOULD_LOAD_OTHER);
	}
}








