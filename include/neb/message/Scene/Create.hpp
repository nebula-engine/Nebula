#ifndef __GLUTPP_NETWORK_MESSAGE_H__
#define __GLUTPP_NETWORK_MESSAGE_H__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <neb/config.hh> // gru/config.hpp.in
//#include <Nebulahh>
#include <neb/core/scene/Util/Address.hh>
//#include <neb/core/actor/Util/Event.hh>
#include <neb/core/actor/Base.hh>
#include <neb/util/wrapper.hpp>

namespace neb {
	namespace message {
		namespace scene {
			class Create {
				public:
					Create();
					void load(sp::shared_ptr<neb::core::scene::base>scene);

					template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
						ar & scene_;
					}

					neb::std::wrapper				scene_;
			};
		}
	}
}

#endif



