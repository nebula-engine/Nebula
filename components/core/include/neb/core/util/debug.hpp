#ifndef NEBULA_UTIL_DEBUG_HPP
#define NEBULA_UTIL_DEBUG_HPP

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/map.hpp>

using namespace std;

namespace neb { namespace util {

	class debug_options {
		public:
			template<typename Archive> void		serialize(Archive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("map",map_);
			}

			map<string, int> map_;
	};

}}


#endif
