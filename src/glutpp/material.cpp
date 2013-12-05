#include <glutpp/material.h>

glutpp::material::material(window* window, math::color ambient, math::color diffuse, math::color specular, math::color emission, float shininess):
	window_(window),
	ambient_(ambient),
	diffuse_(diffuse),
	specular_(specular),
	emission_(emission),
	shininess_(shininess),
	uniform_ambient_(window,"front.ambient"),
	uniform_diffuse_(window,"front.diffuse"),
	uniform_specular_(window,"front.specular"),
	uniform_emission_(window,"front.emission"),
	uniform_shininess_(window,"front.shininess")
{
	
}
void	glutpp::material::load()
{
	uniform_ambient_.load_4fv(ambient_);
	uniform_diffuse_.load_4fv(diffuse_);
	uniform_specular_.load_4fv(specular_);
	uniform_emission_.load_4fv(emission_);
	uniform_shininess_.load_1f(shininess_);
}

