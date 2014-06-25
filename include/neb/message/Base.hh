#ifndef NEBULA_MESSAGE_BASE_HPP
#define NEBULA_MESSAGE_BASE_HPP

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <Galaxy-Network/message.hpp>

#include <neb/util/shared.hpp>

#include <neb/message/Types.hh>

namespace neb {
	namespace message {
		/** \brief %Base
		 *
		 * 
		 */
		class base:
			virtual public neb::std::shared
		{
			protected:
				base();
				virtual ~base() {}
		};
		class OBase:
			virtual public neb::message::base
		{
			public:
				OBase();
				virtual void			serialize(
						boost::archive::polymorphic_oarchive & ar,
						unsigned int const & version) = 0;			
			public:
				sp::shared_ptr<gal::net::omessage>	msg_;
		};
		class IBase:
			virtual public neb::message::base
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

/** \example Nebula/message/example.cc
 * Example.
 */


