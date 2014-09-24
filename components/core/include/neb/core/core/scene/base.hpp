#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <gal/etc/flag.hpp>
#include <gal/stl/map.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <neb/core/core/scene/util/flag.hpp>
#include <neb/core/core/scene/util/decl.hpp>
#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/core/actor/util/parent.hpp>

typedef weak_ptr<neb::core::core::actor::base> wbase;

namespace neb { namespace core { namespace core {
	namespace scene {
		/** 
		 * @ingroup group_core
		 * @brief Base
		 */
		class base:
			virtual public neb::core::core::actor::util::parent
		{
			public:
				base(std::shared_ptr<neb::core::core::scene::util::parent>);
				virtual ~base();
				virtual void			init();
				virtual void			release();
				/** @name Main Loop @{ */
				virtual void			step(gal::etc::timestep const & ts);
				/** @} */

				virtual  void			serialize(
						boost::archive::polymorphic_iarchive & ar,
						unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("flag",flag_);
				}
				virtual void			serialize(
						boost::archive::polymorphic_oarchive & ar,
						unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("flag",flag_);
				}
			public:
				neb::core::pose						getPose();
				neb::core::pose						getPoseGlobal();

				weak_ptr<neb::core::core::scene::util::parent>		getParent();
			public:
				void					add_deferred(
						shared_ptr<neb::core::core::actor::base>);
				/** @name convenience functions
				 * @{
				 */
				virtual wbase				createActorBase(
						neb::core::pose pose) = 0;
				/** @brief create empty actor with point light
				*/
				virtual wbase				createActorLightPoint(
						glm::vec3 p);

				/** @brief create rigidstatic cube
				 *
				 * @note typeof returned actor will be
				 * determined by final implementation of this
				 */
				wbase			createActorRigidStaticCube(
						neb::core::pose pose, double size);
				wbase			createActorRigidDynamicCube(
						neb::core::pose pose, double size);
				/** @brief create rigidstatic
				 *
				 * @note typeof returned actor will be
				 * determined by final implementation of this
				 *
				 * @warning return actor is not initialized
				 */
				virtual wbase		createActorRigidStaticUninitialized() = 0;
				virtual wbase		createActorRigidDynamicUninitialized() = 0;
				/** @} */
			public:
				/** @brief parent
				 *
				 * @note WEAK
				 */
				weak_ptr<neb::core::core::scene::util::parent>			parent_;
			public:
				neb::core::core::scene::util::flag				flag_;
				map< string, std::shared_ptr<neb::core::core::actor::base> >		actors_deferred_;
				float								last_;
		};
	}
}}}

#endif





