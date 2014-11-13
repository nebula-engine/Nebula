#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <gal/etc/flag.hpp>
<<<<<<< HEAD
#include <gal/stl/map.hpp>
=======
//#include <gal/stl/map.hpp>
#include <gal/stl/child.hpp>
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <neb/core/core/scene/util/flag.hpp>
#include <neb/core/core/scene/util/decl.hpp>
#include <neb/core/core/actor/util/decl.hpp>
<<<<<<< HEAD
#include <neb/core/core/actor/util/parent.hpp>

typedef weak_ptr<neb::core::core::actor::base> wbase;

namespace neb { namespace core { namespace core {
=======
#include <neb/core/core/shape/util/decl.hpp>
#include <neb/core/core/actor/util/parent.hpp>

//#include <neb/core/core/actor/rigidbody/desc.hpp>
//#include <neb/core/core/shape/cuboid/desc.hpp>



typedef weak_ptr<neb::core::core::actor::base> wbase;

namespace neb { namespace core { namespace core {

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	namespace scene {
		/** 
		 * @ingroup group_core
		 * @brief Base
		 */
		class base:
<<<<<<< HEAD
			virtual public neb::core::core::actor::util::parent
		{
			public:
				base(std::shared_ptr<neb::core::core::scene::util::parent>);
				virtual ~base();
				virtual void			init();
=======
			virtual public gal::stl::child<neb::core::core::scene::util::parent>,
			virtual public neb::core::core::actor::util::parent
		{
			public:
				typedef neb::core::core::scene::util::parent parent_t;
				typedef neb::util::parent<neb::core::core::actor::__base, neb::core::core::actor::util::parent>		actors;

				base();
				virtual ~base();
				virtual void			init(parent_t * const & p);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
				virtual void			release();
				/** @name Main Loop @{ */
				virtual void			step(gal::etc::timestep const & ts);
				/** @} */

<<<<<<< HEAD
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
=======
				virtual void				load(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
				virtual void				save(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) const;
				BOOST_SERIALIZATION_SPLIT_MEMBER();

			public:
				neb::core::pose						getPose() const;
				neb::core::pose						getPoseGlobal() const;

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
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
<<<<<<< HEAD
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
=======
				
				wbase					createActor(
						neb::core::core::actor::desc const * const &
						);
				void					addActor(
						std::shared_ptr<neb::core::core::actor::base> const &
						);

				virtual wbase				createActorRigidDynamic(
						neb::core::core::actor::rigiddynamic::desc const * const &
						) = 0;


				virtual wbase				createActorLightPoint(
						glm::vec3 p);
				virtual wbase				createActorLightDirectional(
						glm::vec3 p);

				wbase			createActorRigidStaticCuboid(
						neb::core::pose,
						glm::vec3);
				wbase			createActorRigidStaticCube(
						neb::core::pose pose,
						double size);
				wbase			createActorRigidDynamicCuboid(
						neb::core::core::actor::rigidbody::desc const &,
						neb::core::core::shape::cuboid::desc const &);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
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
<<<<<<< HEAD
				/** @brief parent
				 *
				 * @note WEAK
				 */
				weak_ptr<neb::core::core::scene::util::parent>			parent_;
			public:
				neb::core::core::scene::util::flag				flag_;
				map< string, std::shared_ptr<neb::core::core::actor::base> >		actors_deferred_;
				float								last_;
=======
				neb::core::core::scene::util::flag					flag_;
				std::map< string, std::shared_ptr<neb::core::core::actor::base> >	actors_deferred_;
				float									last_;
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
		};
	}
}}}

#endif





