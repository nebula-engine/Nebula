#ifndef NEBULA_ACTOR_BASE_HH
#define NEBULA_ACTOR_BASE_HH

#include <memory>

#include <boost/signals2.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/serialization/map.hpp>

//#include <PxPhysicsAPI.h>

//#include <neb/config.hh> // Nebula/config.hpp.in
//#include <neb/core/actor/Util/desc.hh>

//#include <neb/math/Serialization.hh>

//#include <neb/Filter.hh>
#include <neb/math/Serialization/GLM.hpp>
//#include <neb/message/Actor/Update.hh>
//#include <neb/gfx/texture.hh>
//#include <neb/gfx/material.hh>

#include <neb/core/shape/Base.hh>
#include <neb/core/shape/Util/Parent.hh>
#include <neb/core/actor/__base.hpp>
#include <neb/core/actor/Util/Types.hh>
#include <neb/core/actor/Util/Flag.hh>
#include <neb/core/actor/Util/Parent.hh>
#include <neb/core/pose.hpp>


#include <neb/core/shape/Base.hh>
#include <neb/core/shape/Util/Parent.hh>

namespace neb { namespace gfx { namespace core { namespace actor {


	/** @brief %base
	 * 
	 * graphics data for actors.
	 * no need to derive this class for different actor types.
	*/
	class base:
		virtual public neb::core::actor::base
	{
		public:
			/** @brief default constructor */
			//base();
			/** @brief constructor */
			base(sp::shared_ptr<neb::core::actor::util::parent> parent);
			virtual ~base();
		public:
			virtual void					init();
			virtual void					release() = 0;
		public:
			virtual void					step(gal::std::timestep const & ts);
		public:
			void						draw(
					sp::shared_ptr<neb::gfx::context::base> context,
					sp::shared_ptr<neb::glsl::program> p,
					neb::core::pose const & pose);

			void						load_lights(neb::core::light::util::count& light_count, neb::core::pose const &);

		public:
			/** @brief Parent */
			sp::weak_ptr<neb::core::actor::base>		parent_;
	};

}}}

#endif








