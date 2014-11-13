#ifndef PHYSX_SHAPE_HEIGHT_FIELD_HH
#define PHYSX_SHAPE_HEIGHT_FIELD_HH

#include <neb/core/core/shape/HeightField/desc.hpp>
#include <neb/gfx/core/shape/base.hpp>
#include <neb/phx/core/shape/base.hpp>

namespace neb { namespace math {
	struct HeightField;
}}

namespace neb { namespace phx { namespace core { namespace shape {


	class HeightField:
		virtual public neb::phx::core::shape::base,
		virtual public neb::gfx::core::shape::base
	{
		public:
			typedef neb::core::core::shape::util::parent parent_t;

			HeightField();
			
			virtual void				init(parent_t * const & p);

			virtual void				release();
			virtual void				step(gal::etc::timestep  const & ts);
			virtual void				create_physics();

			// dont render normally. function is empty
			virtual void				draw(
							neb::gfx::glsl::program::base const * const & p,
							neb::core::pose const & pose);
			virtual void				drawHF(
							neb::gfx::glsl::program::base const * const & p,
							neb::core::pose const & pose);


			virtual void	load(ba::polymorphic_iarchive & ar, unsigned int const &);
			virtual void	save(ba::polymorphic_oarchive & ar, unsigned int const &) const;


			virtual physx::PxGeometry*		to_geo();

			void					mesh_from_heightfield(neb::math::HeightField*, float, float);

			physx::PxReal				min_y_;
			physx::PxReal				max_y_;

			neb::core::core::shape::HeightField::desc	desc_;
	};



}}}}

#endif
