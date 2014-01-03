#include <math/free.h>

#include <neb/physics.h>
#include <neb/scene/scene.h>
#include <neb/simulation_callback.h>
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




void glutpp::actor::desc::load(tinyxml2::XMLElement* element) {
	
	raw_.load(element);
	
	// shapes
	tinyxml2::XMLElement* element_shape = element->FirstChildElement("shape");
	glutpp::shape::desc* sd;
	
	while(element_shape != NULL)
	{
		sd = new glutpp::shape::desc;
		
		sd->load(element_shape);
		
		shapes_.push_back(sd);
		
		element_shape = element->NextSiblingElement("shape");
	}
	
	// filtering
	raw_.filter_data_.simulation_.word0 = neb::filter::type::STATIC;
	raw_.filter_data_.simulation_.word1 = neb::filter::RIGID_AGAINST;
	raw_.filter_data_.simulation_.word2 = neb::filter::type::STATIC;
	raw_.filter_data_.simulation_.word3 = neb::filter::type::PROJECTILE;


	
	raw_.filter_data_.scene_query_.word3 = neb::filter::DRIVABLE_SURFACE;
	
}






