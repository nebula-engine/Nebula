#ifndef NEB_FINAL_GFX_PHX_CORE_ACTOR_BASE_HPP
#define NEB_FINAL_GFX_PHX_CORE_ACTOR_BASE_HPP

#include <neb/gfx/core/actor/base.hpp>
#include <neb/phx/core/actor/base.hpp>
#include <neb/fin/gfx_phx/core/actor/util/parent.hpp>
#include <neb/fin/gfx_phx/core/shape/util/parent.hpp>

namespace neb { namespace fin { namespace gfx_phx { namespace core { namespace actor {

	class base:
		virtual public neb::phx::core::actor::base,
		virtual public neb::gfx::core::actor::base
	{
		public:
			typedef neb::core::core::actor::util::parent parent_t;
			base();
			virtual void						init(parent_t * const &);
			virtual void						release();
			virtual void						step(gal::etc::timestep const & ts);

			virtual void	load(ba::polymorphic_iarchive & ar, unsigned int const &);
			virtual void	save(ba::polymorphic_oarchive & ar, unsigned int const &) const;

			virtual std::weak_ptr<neb::core::core::shape::base>		createShapeBase(
					neb::core::pose pose);
			virtual std::weak_ptr<neb::core::core::shape::base>		createShapeCuboid(
					neb::core::core::shape::cuboid::desc);
			virtual std::weak_ptr<neb::core::core::shape::base>		createShapeHeightField(
					neb::core::core::shape::HeightField::desc const &);

	};
}}}}}


#endif



