#ifndef __GRU_SHARED_HPP__
#define __GRU_SHARED_HPP__

/** @file shared.hpp
 */

#include <memory>
#include <map>
#include <typeindex>
#include <string>

#include <boost/thread.hpp>
#include <boost/serialization/nvp.hpp>

#include <gal/itf/release.hpp>
#include <gal/std/decl.hpp>
#include <gal/itf/typedef.hpp>

namespace gal {
	namespace itf {
		/** @brief %shared.
		 *
		 * Avoid multiple enabled_shared_from_this bases.
		 * Provide common base for working with factory and map.
		 * Supply type info.
		 *
		 */
		class shared:
			virtual public std::enable_shared_from_this<shared>,
			virtual public gal::itf::__release
		{
			public:
				/** */
				static hash_type				to_hash_code(std::string const & str);
				/** */
				static ::std::string const &			to_string(hash_type const & hash);
				/** @brief Register new type index.
				 *
				 * a type must be registered before the conversion functions will work.
				 */
				static void					register_type(std::type_index new_index);
				/** @brief static get index
				 *
				 * for boost multi_index indexing
				 */
				static index_type const &			static_get_index(std::shared_ptr<gal::itf::shared> ptr);
			public:
				static gal::itf::registry				registry_;
				static std::map< hash_type, std::string >		map_hash_string_;
				static std::map< std::string, hash_type >		map_string_hash_;
			public:
				shared();
				/** @brief destructor */
				virtual ~shared();
				/** @brief init */
				virtual void					__init();
				virtual void					release() = 0;
				/** @brief hash code */
				hash_type					hash_code() const;
				/** */
				std::string					name() const;
				/** */
				template<class A> void				serialize(A & ar, unsigned int const v)
				{
					ar & BOOST_SERIALIZATION_NVP(_M_index);
					ar & BOOST_SERIALIZATION_NVP(_M_name);
				}
			public:
				index_type					_M_index;
				std::string					_M_name;
				/** @brief general mutex
				 *
				 * for thread-safe erasure from gal::stl::map
				 */
				boost::recursive_mutex		mutex_;
		};
	}
}

#endif



