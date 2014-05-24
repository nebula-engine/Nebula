#ifndef __GRU_SHARED_HPP__
#define __GRU_SHARED_HPP__

#include <memory>
#include <map>
#include <typeindex>

#include <Nebula/Types.hh>

namespace Neb {
	namespace Util {
		
		
		
		class Shared;
		class Registry {
			public:
				typedef std::shared_ptr<Neb::Util::Shared>	shared;
				typedef std::weak_ptr<Neb::Util::Shared>	weak;

				Registry();
				void					reg(shared s);
				shared					get(Neb::Util::index_type i);
			private:
				std::map<index_type, weak>		map_;
				Neb::Util::index_type			next_;

		};
		/** @brief %Shared.
		 * avoid multiple enabled_shared_from_this bases
		 */
		class Shared:
			virtual public std::enable_shared_from_this<Shared>
		{
			public:
				typedef long int		hash_type;
			public:
				Shared();
				/** @brief Destructor */
				virtual ~Shared() {}
				virtual void				init();
			public:
				/** @brief Hash Code */
				hash_type					hash_code() const;
				/** */
				std::string					name() const;
				/** */
				static hash_type				to_hash_code(std::string const & str) {
					auto it = map_string_hash_.find(str);
					if(it == map_string_hash_.cend()) throw 0;
					return it->second;
				}
				/** */
				static std::string const &			to_string(hash_type const & hash) {
					auto it = map_hash_string_.find(hash);
					if(it == map_hash_string_.cend()) throw 0;
					return it->second;
				}
				/** @brief Register new type index.
				 * a type must be registered before the conversion functions will work.
				 */
				static void					register_type(std::type_index new_index) {
					map_hash_string_[new_index.hash_code()] = new_index.name();
					map_string_hash_[new_index.name()] = new_index.hash_code();
				}
			public:
				Neb::Util::index_type				i_;
			public:
				static Registry					registry_;
				static std::map<hash_type,std::string>		map_hash_string_;
				static std::map<std::string,hash_type>		map_string_hash_;

		};
	}
}

#endif

