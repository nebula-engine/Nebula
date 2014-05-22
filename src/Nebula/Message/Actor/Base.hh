#ifndef NEBULA_MESSAGE_ACTOR_BASE_HPP
#define NEBULA_MESSAGE_ACTOR_BASE_HPP

#include <Nebula/Util/Typed.hh>

#include <Nebula/Message/Base.hh>

namespace Neb {
	namespace Message {
		namespace Actor {
			class Base:
				virtual public Neb::Message::Base
			{
				public:
					virtual void		serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
						ar & i_;
					}
					
				public:
					Neb::Util::index_type			i_;
			};
			class IBase:
				virtual public Neb::Message::IBase,
				virtual public Neb::Message::Actor::Base
			{
				public:
					virtual void		serialize(
							boost::archive::polymorphic_iarchive & ar,
							unsigned int const & version) = 0;
			};
			class OBase:
				virtual public Neb::Message::OBase,
				virtual public Neb::Message::Actor::Base
			{
				public:
					virtual void		serialize(
							boost::archive::polymorphic_oarchive & ar,
							unsigned int const & version) = 0;
			};
		}
	}
}

#endif






