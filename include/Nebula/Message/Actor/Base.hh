#ifndef NEBULA_MESSAGE_ACTOR_BASE_HPP
#define NEBULA_MESSAGE_ACTOR_BASE_HPP


#include <Nebula/Message/Base.hh>

namespace neb {
	namespace message {
		namespace actor {
			class Base:
				virtual public neb::message::Base
			{
				public:
					/** @brief index
					 *
					 * index of actor
					 */
					gal::std::index_type			index_;
			};
			class IBase:
				virtual public neb::message::IBase,
				virtual public neb::message::actor::Base
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
				virtual public neb::message::OBase,
				virtual public neb::message::actor::Base
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






