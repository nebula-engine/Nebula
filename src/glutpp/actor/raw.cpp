#include <math/free.h>

#include <glutpp/actor/desc.h>

void glutpp::actor::raw::load(tinyxml2::XMLElement* element) {
	
	printf("%s\n", __PRETTY_FUNCTION__);

	// xml
	assert(element);
	
	// type
	const char* buf = element->Attribute("type");
	assert(buf);
	
	if( strcmp(buf, "rigid_dynamic") == 0)
	{
		type_ = glutpp::actor::RIGID_DYNAMIC;
	}
	else if( strcmp(buf, "rigid_static") == 0)
	{
		type_ = glutpp::actor::RIGID_STATIC;
	}	
	else if( strcmp(buf, "plane") == 0)
	{
		type_ = glutpp::actor::PLANE;
	}	
	else if(strcmp(buf, "controller") == 0)
	{
		type_ = glutpp::actor::CONTROLLER;
	}
	else if(strcmp(buf, "empty") == 0)
	{
		type_ = glutpp::actor::EMPTY;
	}
	else
	{
		printf("unknown actor type\n");
		abort();
	}
	
	math::vec3 p = math::xml_parse_vec3(element->FirstChildElement("p"), math::vec3(0,0,0));
	math::quat q = math::xml_parse_quat(element->FirstChildElement("q"));
	
	pose_.p.from_math(p);
	pose_.q.from_math(q);

	p.print();
	q.print();	

	// filtering
	filter_data_.simulation_.word0 = glutpp::filter::type::STATIC;
	filter_data_.simulation_.word1 = glutpp::filter::RIGID_AGAINST;
	filter_data_.simulation_.word2 = glutpp::filter::type::STATIC;
	filter_data_.simulation_.word3 = glutpp::filter::type::PROJECTILE;

	filter_data_.scene_query_.word3 = glutpp::filter::DRIVABLE_SURFACE;
}
void glutpp::actor::raw::plane(tinyxml2::XMLElement* element) {
	
	printf("%s\n", __PRETTY_FUNCTION__);
	
	
	// xml
	math::vec3 n = math::xml_parse_vec3(element->FirstChildElement("n"), math::vec3(0,1,0));
	n.normalize();
	
	float d = math::xml_parse_float(element->FirstChildElement("d"));
	
	
	math::quat q(3.14f, math::vec3(1,0,0));
	
	math::transform pose(n * -1.0f * d, q);
	
	n_.from_math(n);
	d_ = d;
	

	pose_.from_math(pose);

}
void glutpp::actor::raw::controller(tinyxml2::XMLElement* element) {

	printf("%s\n",__FUNCTION__);
	
	pose_.p.from_math(math::xml_parse_vec3(element->FirstChildElement("p"), math::vec3(0,0,0)));
}


void glutpp::actor::raw::write(gal::network::message_shared msg) {
	msg->write(this, sizeof(glutpp::actor::raw));
}



