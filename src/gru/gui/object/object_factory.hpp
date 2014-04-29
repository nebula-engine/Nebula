#ifndef __GLUTPP_OBJECT_FACTORY__
#define __GLUTPP_OBJECT_FACTORY__

#include <memory>

#include <boost/archive/xml_iarchive.hpp>

namespace glutpp {
	namespace gui {
		namespace object {
			class object;

			class object_factory {
				public:
					typedef std::shared_ptr<glutpp::gui::object::object> object_t;

					virtual object_t	create(boost::archive::xml_iarchive& ar);
			};
		}
	}
}

#endif
