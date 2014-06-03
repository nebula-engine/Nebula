#ifndef NEBULA_MESSAGE_ACTOR_BASE_HPP
#define NEBULA_MESSAGE_ACTOR_BASE_HPP


#include <Nebula/Message/Base.hh>

namespace Neb {
	namespace Message {
		namespace Actor {
			class Base:
				virtual public Neb::Message::Base
			{
				public:
					/** @brief index
					 *
					 * index of actor
					 */
					gal::std::index_type			index_;
			};
			class IBase:
				virtual public Neb::Message::IBase,
				virtual public Neb::Message::Actor::Base
			{
				private:
					IBase&			operator=(IBase const &);
				public:
					virtual void		serialize(
							boost::archive::polymorphic_iarchive & ar,
							unsigned int const & version)
					{
						ar & index_;
					}
			};
			class OBase:
				virtual public Neb::Message::OBase,
				virtual public Neb::Message::Actor::Base
			{
				public:
					virtual void		serialize(
							boost::archive::polymorphic_oarchive & ar,
							unsigned int const & version)
					{
						ar & index_;
					}
			};
		}
	}
}

#endif






