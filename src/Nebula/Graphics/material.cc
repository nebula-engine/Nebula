#include <stdio.h>

//#include <math/xml.hpp>

#include <Nebula/App/Base.hh>
#include <Nebula/Graphics/material.hh>
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/glsl/Uniform/scalar.hpp>
#include <Nebula/Scene/Base.hh>

/*
gru::Color::color<float> operator<<(gru::Color::color<float> c, tinyxml2::XMLElement* element) {
	if(element != NULL) {
		char const * buf = element->GetText();
		
		sscanf(buf, "%f,%f,%f,%f", &c.r, &c.g, &c.b, &c.a);
	}
	
	return c;
}
float operator<<(float f, tinyxml2::XMLElement* element) {
	if(element != NULL) {
		char const * buf = element->GetText();
		
		sscanf(buf, "%f,%f,%f,%f", &c.r, &c.g, &c.b, &c.a);
	}
	
	return c;
}
*/

neb::material::raw::raw() {
	ambient_ = neb::Color::white<float>();
	diffuse_ = neb::Color::cyan<float>();
	specular_ = neb::Color::white<float>();
	emission_ = neb::Color::black<float>();
	shininess_ = 500;
}
/* implement through serialize(ar)
void	neb::material::raw::load(tinyxml2::XMLElement* element) {
	
	if(element == NULL)
	{
		printf("no element\n");
		return;
	}
	
	ambient_ << element->FirstChildElement("ambient");
	diffuse_  << element->FirstChildElement("diffuse");
	specular_ << element->FirstChildElement("specular");
	emission_ << element->FirstChildElement("emission");
	
	shininess_ << element->FirstChildElement("shininess");

	printf("diffuse = ");	
	diffuse_.print();
}
*/



neb::material::material::material()
{}
void	neb::material::material::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);
}

void	neb::material::material::load()
{
	auto p = neb::app::base::global()->current_program();

	p->get_uniform_scalar("front.ambient")->load(raw_.ambient_);
	p->get_uniform_scalar("front.diffuse")->load(raw_.diffuse_);
	p->get_uniform_scalar("front.specular")->load(raw_.specular_);
	p->get_uniform_scalar("front.emission")->load(raw_.emission_);
	p->get_uniform_scalar("front.shininess")->load(raw_.shininess_);
}
void		neb::material::material::step(neb::core::TimeStep const & ts) {
		
	//raw_.diffuse_.step(time);
}


