#ifndef NEBULA_ACTOR___BASE_HPP
#define NEBULA_ACTOR___BASE_HPP

#include <boost/thread.hpp>

#include <gal/stl/child.hpp>

#include <neb/core/itf/shared.hpp>
#include <neb/core/itf/serializable.hpp>

#include <neb/core/type_traits.hpp>

namespace neb { namespace core { namespace core { namespace actor {

	namespace util {
		class parent;
	}

	class __base:
		virtual public neb::itf::shared,
		virtual public neb::serializable,
		virtual public neb::type_traits<__base>::child_t
	{
		public:
			typedef type_traits<__base>::parent_t parent_t;

			virtual void		init(parent_t * const & p) = 0;

			virtual void	load(ba::polymorphic_iarchive & ar, unsigned int const &) = 0;
			virtual void	save(ba::polymorphic_oarchive & ar, unsigned int const &) const = 0;
			BOOST_SERIALIZATION_SPLIT_MEMBER();

	};
}}}}

#endif
