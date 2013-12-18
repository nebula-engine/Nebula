#ifndef __GLUTPP_OBJECT_FACTORY__
#define __GLUTPP_OBJECT_FACTORY__

#include <tinyxml/tinyxml.h>

namespace glutpp
{
namespace gui
{
namespace object
{
class object_factory
{
public:
std::shared_ptr<glutpp::gui::object::object>    create(TiXmlElement* element);


};
}
}
}

#endif
