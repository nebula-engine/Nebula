#ifndef HELPER_INFO_HPP
#define HELPER_INFO_HPP

#include <dlfcn.h>

#include <typeindex>
#include <memory>
#include <cassert>
#include <string>

#include <gal/itf/typedef.hpp>

#include <gal/dll/helper_info.hpp>

#include <boost/serialization/nvp.hpp>

namespace gal { namespace dll {

	//template<typename H> struct deleter;

	struct helper_info
	{
		public:
			helper_info();
		public:
			helper_info(std::string f, std::string o, std::type_index ti);

			helper_info(helper_info const & h);

			template<class Archive> void	serialize(Archive & ar, int v)
			{
				ar & BOOST_SERIALIZATION_NVP(file_name);
				ar & BOOST_SERIALIZATION_NVP(object_name);
				ar & BOOST_SERIALIZATION_NVP(hc);
				ar & BOOST_SERIALIZATION_NVP(name);
			}
		public:
			std::string		file_name;
			std::string		object_name;
			size_t			hc;
			std::string		name;
	};


}}

#endif

