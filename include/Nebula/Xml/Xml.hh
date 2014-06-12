#ifndef GRU_XML_XML_HPP
#define GRU_XML_XML_HPP

#include <tinyxml2.h>

#include <PxPhysicsAPI.h>

#include <Nebula/Math/Typedef.hpp>

class XmlArchive {
	public:
		friend XmlArchive	operator>>(XmlArchive, float&);
		friend XmlArchive	operator>>(XmlArchive, neb::Math::Vec3&);

		XmlArchive(tinyxml2::XMLElement*);
	private:
		tinyxml2::XMLElement* element_;
};

XmlArchive	operator>>(XmlArchive ar, float& ret) {

	if(!ar.element_) return ar;
	
	char const * buf = ar.element_->GetText();
	
	int c = sscanf(buf, "%f", &ret);
	assert(c == 1);
	
	return ar;
}
XmlArchive	operator>>(XmlArchive ar, neb::Math::Vec3& ret) {

	if(!ar.element_) return ar;
	
	char const * buf = ar.element_->GetText();
	
	int c = sscanf(buf, "%f,%f,%f", &ret.x, &ret.y, &ret.z);
	assert(c == 3);
	
	return ar;
}



#endif


