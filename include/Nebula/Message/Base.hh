#ifndef NEBULA_MESSAGE_BASE_HPP
#define NEBULA_MESSAGE_BASE_HPP

#include <Galaxy-Network/message.hpp>

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/Message/Types.hh>

namespace Neb {
	namespace Message {
		/** \brief %Base
		 *
		 * 
		 */
		class Base:
			virtual public gal::std::shared
		{
			protected:
				Base();
		};
		class OBase:
			virtual public Neb::Message::Base
		{
			public:
				OBase();
				virtual void			serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) = 0;			
			public:
				sp::shared_ptr<gal::net::omessage>	msg_;
		};
		class IBase:
			virtual public Neb::Message::Base
		{
			public:
				IBase();
				virtual void			serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) = 0;
			public:
				sp::shared_ptr<gal::net::omessage>	msg_;
		};
	}
}

#endif

/** \example Nebula/Message/example.cc
 * Example.
 */


