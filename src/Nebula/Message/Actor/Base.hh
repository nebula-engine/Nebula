#ifndef NEBULA_MESSAGE_ACTOR_BASE_HPP
#define NEBULA_MESSAGE_ACTOR_BASE_HPP

#include <Nebula/Util/Typed.hh>

#include <Nebula/Message/Base.hh>

namespace Neb {
	namespace Message {
		namespace Actor {
			class Base: public Neb::Message::Base {
				public:
					template<class Archive> void		serialize(Archive & ar, unsigned int const & version) {
						ar & addr_;
						serializeDerived(ar, version);
					}
				public:
					Neb::Actor::Util::Address			addr_;
			};
			class IBase: public Neb::Message::Actor::Base {
				public:
					template<class Archive> void		serialize(Archive & ar, unsigned int const & version) {
						ar & addr_;
						serializeDerived(ar, version);
					}

					virtual void		serializeDerived(
							boost::archive::polymorphic_iarchive & ar,
							unsigned int const & version) = 0;
			};
			class OBase: public Neb::Message::Actor::Base {
				public:
					template<class Archive> void		serialize(Archive & ar, unsigned int const & version) {
						ar & addr_;
						serializeDerived(ar, version);
					}

					virtual void		serializeDerived(
							boost::archive::polymorphic_oarchive & ar,
							unsigned int const & version) = 0;
			};
		}
	}
}

#endif






