#ifndef NEBULA_MESSAGE_BASE_HPP
#define NEBULA_MESSAGE_BASE_HPP

#include <Nebula/network/message.hh>

#include <Nebula/Util/Shared.hh>

#include <Nebula/Message/Types.hh>

namespace Neb {
	namespace Message {
		/** \brief %Base
		 *
		 * 
		 */
		class Base:
			virtual public Neb::Util::Shared
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
				gal::network::omessage_s	msg_;
		};
		class IBase:
			virtual public Neb::Message::Base
		{
			public:
				IBase();
				virtual void			serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) = 0;
			public:
				gal::network::omessage_s	msg_;
		};
	}
}

#endif

/** \example Nebula/Message/example.cc
 * Example.
 */


