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

#include <neb/core/shape/base.hpp>
#include <neb/core/shape/Util/Parent.hh>
#include <neb/core/actor/__base.hpp>
#include <neb/core/actor/Util/Types.hh>
#include <neb/core/actor/Util/Flag.hh>
#include <neb/core/actor/Util/Parent.hh>
#include <neb/core/pose.hpp>


#include <neb/core/shape/base.hpp>
#include <neb/core/shape/Util/Parent.hh>

namespace neb { 

	namespace gfx { namespace core { namespace actor {
		class base;
	}}}

	namespace core { namespace actor {


		/** @brief %Base */
		class base:
			virtual public neb::actor::__base,
			virtual public neb::core::actor::util::parent,
			virtual public neb::core::shape::util::parent
		{
			public:
				/** @brief default constructor */
				//base();
				/** @brief constructor */
				base(sp::shared_ptr<neb::core::actor::util::parent> parent);
				virtual ~base();
			public:
				virtual void						init();
				virtual void						release();
			public:
				virtual void						step(gal::std::timestep const & ts);

			public:

				virtual neb::core::pose					getPose();
				virtual neb::core::pose					getPoseGlobal();

				sp::shared_ptr<neb::core::actor::util::parent>		get_parent();
				/** @brief set pose
				 *
				 * virtual because actor::local will add self to active transform list
				 */
				virtual void						setPose(neb::core::pose const & pose);

				/** @todo move to derived class */
				// signal
				//			void							connect(sp::shared_ptr<neb::gfx::window::base>);

				//			int							key_fun(sp::shared_ptr<neb::gfx::window::base> window,int,int,int,int);
			public:

				virtual sp::weak_ptr<neb::core::shape::base>		createShapeBase() = 0;
				virtual sp::weak_ptr<neb::core::shape::base>		createShapeBox(vec3 size) = 0;
				virtual sp::weak_ptr<neb::core::shape::base>		createShapeCube(real size) = 0;

			public:

				/** @brief %Serialize
				 * @param ar archive
				 * @param version version
				 */
				template<class Archive> void				serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i", i_);

					serializeData(ar, version);

					ar & boost::serialization::make_nvp("actors", neb::core::actor::util::parent::map_);
					ar & boost::serialization::make_nvp("shapes", neb::core::shape::util::parent::map_);
				}
				virtual void						serializeData(
						boost::archive::polymorphic_oarchive & ar,
						unsigned int const & version) {
					ar & boost::serialization::make_nvp("flag",flag_);
					ar & boost::serialization::make_nvp("name",name_);
					ar & boost::serialization::make_nvp("pose",pose_);
					ar & boost::serialization::make_nvp("normal",n_);
					ar & boost::serialization::make_nvp("distance",d_);
					ar & boost::serialization::make_nvp("velocity",velocity_);
					ar & boost::serialization::make_nvp("density",density_);
				}
				virtual void						serializeData(
						boost::archive::polymorphic_iarchive & ar,
						unsigned int const & version) {
					ar & boost::serialization::make_nvp("flag",flag_);
					ar & boost::serialization::make_nvp("name",name_);
					ar & boost::serialization::make_nvp("pose",pose_);
					ar & boost::serialization::make_nvp("normal",n_);
					ar & boost::serialization::make_nvp("distance",d_);
					ar & boost::serialization::make_nvp("velocity",velocity_);
					ar & boost::serialization::make_nvp("density",density_);
				}





				neb::core::actor::util::flag				flag_;
				::std::string						name_;
				neb::core::pose						pose_;
				/** @brief Normal for planes. */
				vec3							n_;
				/** @brief Distance for planes. */
				float							d_;
				vec3							velocity_;
				float							density_;


				double							health_;


				sp::shared_ptr<neb::gfx::core::actor::base>		actor_gfx_;
			public:
				/** @brief Parent */
				sp::weak_ptr<neb::core::actor::util::parent>		parent_;
		};
	}}}

#endif








