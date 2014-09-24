#ifndef NEB_CORE_CORE_ACTOR_RIGIDBODY_DESC_HPP
#define NEB_CORE_CORE_ACTOR_RIGIDBODY_DESC_HPP

#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <gal/itf/shared.hpp>

#include <neb/core/pose.hpp>
#include <neb/core/core/shape/desc.hpp>
#include <neb/core/core/scene/util/decl.hpp>
#include <neb/core/core/actor/util/decl.hpp>

namespace ba = boost::archive;

namespace neb { namespace core { namespace core { namespace actor {

	struct desc: gal::itf::shared
	{
		desc() {}
		desc(neb::core::pose npose):
			pose(npose)
		{}

		virtual void	release();

		template<class Archive> void		serialize(Archive & ar, unsigned int const & version)
		{
			ar & BOOST_SERIALIZATION_NVP(pose);
		}
		virtual std::shared_ptr<neb::core::core::actor::base>		visit(
				neb::core::core::scene::base * const scene
				) const;


		neb::core::pose		pose;

	};
	namespace rigidbody {

		struct desc: neb::core::core::actor::desc {
			desc() {}
			desc(neb::core::pose npose):
				neb::core::core::actor::desc(npose)
			{}
			template<class Archive> void		serialize(Archive & ar, unsigned int const & version)
			{
				ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::core::core::actor::desc);
				ar & boost::serialization::make_nvp("foo",foo);
			}
			
			virtual std::shared_ptr<neb::core::core::actor::base>		visit(
					neb::core::core::scene::base * const scene
					) const;


			float					foo;

		};

	}

}}}}

#endif

