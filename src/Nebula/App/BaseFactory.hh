#ifndef NEBULA_APP_BASE_FACTORY_HH
#define NEBULA_APP_BASE_FACTORY_HH

#include <memory>

#include <Nebula/Util/Factory.hh>

namespace Neb {
	namespace App {
		class BaseFactory {
			public:
				template<class T> static std::shared_ptr< Neb::Factory<T> >		getFactoryDefault();
		};
	}
}

#endif



