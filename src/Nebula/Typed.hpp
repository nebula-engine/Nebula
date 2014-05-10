#ifndef NEBULA_TYPED_HPP
#define NEBULA_TYPED_HPP

#include <map>

#include <boost/function.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>

#include <Nebula/Memory/smart_ptr.hpp>

namespace Neb {
	/** @brief Typed */
	class Typed {
		public:
			typedef hash_type		long int;
			/** @brief Destructor */
			virtual ~Typed() {}
			/** @brief Hash Code */
			hash_type const &		hash_code() const;
			std::string const &		name() const;
	};
}

#endif



