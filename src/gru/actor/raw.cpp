

#include <gru/actor/actor.hpp>
#include <gru/actor/raw.hpp>
#include <gru/Xml/Xml.hpp>

glutpp::actor::raw::raw():
	type_(glutpp::actor::Type::NONE),
	mode_create_(glutpp::actor::mode_create::e::NOW),
	flag_(0),
	density_(200)
{
	memset(name_, 0, max_name_length + 1);
}
void glutpp::actor::raw::load(boost::shared_ptr<glutpp::actor::actor> actor) {
	operator=(*actor->raw_);
}
/*
unsigned int glutpp::actor::raw::parse_filter(tinyxml2::XMLElement* element, unsigned int i) {

	if(element == NULL) return i;

	char const * buf = element->GetText();

	if(strcmp(buf, "STATIC") == 0)
	{
		return glutpp::filter::type::STATIC;
	}
	else if(strcmp(buf, "DYNAMIC") == 0)
	{
		return glutpp::filter::type::DYNAMIC;
	}
	else if(strcmp(buf, "RIGID_AGAINST") == 0)
	{
		return glutpp::filter::RIGID_AGAINST;
	}
	else if(strcmp(buf, "PROJECTILE") == 0)
	{
		return glutpp::filter::type::PROJECTILE;
	}
	else if(strcmp(buf, "PROJECTILE_AGAINST") == 0)
	{
		return glutpp::filter::PROJECTILE_AGAINST;
	}
	abort();
}*/
/*
void glutpp::actor::raw::plane(tinyxml2::XMLElement* element) {

	printf("%s\n", __PRETTY_FUNCTION__);


	// xml
	math::vec3<float> n = math::Xml::parse_vec3<float>(element->FirstChildElement("n"), math::vec3<float>(0,1,0));
	n.Normalize();

	float d = math::Xml::parse_float<float>(element->FirstChildElement("d"), 0);


	math::quat<float> q(3.14f, math::vec3<float>(1,0,0));

	math::transform<float> pose(n * -1.0f * d, q);

	n_ = n;
	d_ = d;

	pose_ = pose;
}
void glutpp::actor::raw::controller(tinyxml2::XMLElement* element) {

	printf("%s\n",__FUNCTION__);

	pose_.p = math::Xml::parse_vec3<float>(element->FirstChildElement("p"), math::vec3<float>(0,0,0));
}
*/




