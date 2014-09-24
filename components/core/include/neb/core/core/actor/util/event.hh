#ifndef __GLUTPP_ACTOR_EVENT_H__
#define __GLUTPP_ACTOR_EVENT_H__

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <gru/config.hpp>
#include <gru/shape/desc.hpp>

namespace neb {
	namespace Event {
		namespace actor {
			class base {
				public:
					template<class Archive> void		serialize(Archive & ar, unsigned int const & version) {
						ar & hash_code_;
						serialize_derived(ar, version);
					}
					virtual void				serialize_derived(boost::archive::xml_oarchive & ar, unsigned int const & version) = 0;
					virtual void				serialize_derived(boost::archive::xml_iarchive & ar, unsigned int const & version) = 0;
					virtual void				serialize_derived(boost::archive::binary_oarchive & ar, unsigned int const & version) = 0;
					virtual void				serialize_derived(boost::archive::binary_iarchive & ar, unsigned int const & version) = 0;
					
					static int hash_code_;
			};
			class Fire {
				public:
					virtual void				serialize_derived(boost::archive::xml_oarchive & ar, unsigned int const & version) {}
					virtual void				serialize_derived(boost::archive::xml_iarchive & ar, unsigned int const & version) {}
					virtual void				serialize_derived(boost::archive::binary_oarchive & ar, unsigned int const & version) {}
					virtual void				serialize_derived(boost::archive::binary_iarchive & ar, unsigned int const & version) {}
			};
		}
	}
}

#endif



