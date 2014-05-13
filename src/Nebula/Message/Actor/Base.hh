#ifndef NEBULA_MESSAGE_ACTOR_BASE_HPP
#define NEBULA_MESSAGE_ACTOR_BASE_HPP

#include <Nebula/Typed.hpp>

namespace Neb {
	namespace Message {
		namespace Actor {
			class Base: public Neb::Typed {
				public:
					template<class Archive> void		serialize(Archive & ar, unsigned int const & version) {
						ar & addr_;
						serializeDerived(ar, version);
					}

					//virtual void		serialize(boost::archive::binary_oarchive & ar, unsigned int const & version) = 0;
					//virtual void		serialize(boost::archive::binary_oarchive & ar, unsigned int const & version) = 0;
					virtual void		serializeDerived(boost::archive::binary_oarchive & ar, unsigned int const & version) = 0;
					virtual void		serializeDerived(boost::archive::binary_iarchive & ar, unsigned int const & version) = 0;
				public:
					Neb::Actor::addr				addr_;
			};
		}
	}
}

#endif






