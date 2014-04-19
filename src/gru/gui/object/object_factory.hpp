#ifndef __GLUTPP_OBJECT_FACTORY__
#define __GLUTPP_OBJECT_FACTORY__

#include <memory>

#include <tinyxml2.h>

namespace glutpp
{
	namespace gui
	{
		namespace object
		{
			class object;
			class object_factory
			{
				public:
					typedef std::shared_ptr<glutpp::gui::object::object> object_t;

					virtual object_t	create(tinyxml2::XMLElement* element);


			};
		}
	}
}

#endif
