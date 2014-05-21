#ifndef NEBULA_TYPED_HPP
#define NEBULA_TYPED_HPP

#include <typeindex>
#include <map>

#include <boost/function.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>


namespace Neb {
	namespace Util {
		/** @brief Typed */
		class Typed {
			public:
				typedef long int		hash_type;
				/** @brief Destructor */
				virtual ~Typed() {}
				/** @brief Hash Code */
				hash_type			hash_code() const;
				std::string			name() const;

				static hash_type		to_hash_code(std::string const & str) {
					auto it = map_string_hash_.find(str);
					if(it == map_string_hash_.cend()) throw 0;
					return it->second;
				}
				static std::string const &	to_string(hash_type const & hash) {
					auto it = map_hash_string_.find(hash);
					if(it == map_hash_string_.cend()) throw 0;
					return it->second;
				}
				/** @brief Register new type index.
				 * a type must be registered before the conversion functions will work.
				 */
				static void			register_type(std::type_index new_index) {
					map_hash_string_[new_index.hash_code()] = new_index.name();
					map_string_hash_[new_index.name()] = new_index.hash_code();
				}

				static std::map<hash_type,std::string>		map_hash_string_;
				static std::map<std::string,hash_type>		map_string_hash_;
		};
	}
}

#endif



