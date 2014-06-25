#ifndef NEBULA_MESSAGE_ACTOR_BASE_HPP
#define NEBULA_MESSAGE_ACTOR_BASE_HPP


#include <neb/message/Base.hh>

namespace neb {
	namespace message {
		namespace actor {
			class base:
				virtual public neb::message::base
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
				virtual public neb::message::actor::base
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
				virtual public neb::message::actor::base
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






