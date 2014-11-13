#ifndef NEBULA_CORE_LIGHT___BASE_HPP
#define NEBULA_CORE_LIGHT___BASE_HPP

<<<<<<< HEAD
#include <neb/core/itf/shared.hpp>

namespace neb { namespace core { namespace light {

	class __base: virtual public neb::itf::shared {
	};

}}}
=======
#include <gal/stl/child.hpp>

#include <neb/core/itf/shared.hpp>
#include <neb/core/itf/serializable.hpp>

namespace neb { namespace core {

	namespace core { namespace light { namespace util {
		class parent;
	}}}

	class pose;

	namespace light {

		class __base:
			virtual public neb::itf::shared,
			virtual public neb::serializable,
			virtual public gal::stl::child<neb::core::core::light::util::parent>
		{
			public:
				virtual void		init(neb::core::core::light::util::parent * const & p) = 0;
				virtual void		callbackPose(neb::core::pose const &) = 0;

				virtual void		load(ba::polymorphic_iarchive & ar, unsigned int const &) = 0;
				virtual void		save(ba::polymorphic_oarchive & ar, unsigned int const &) const = 0;
				BOOST_SERIALIZATION_SPLIT_MEMBER();

		};

	}}
}
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

#endif
