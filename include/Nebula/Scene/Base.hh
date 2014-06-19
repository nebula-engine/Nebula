#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <Galaxy-Standard/flag.hpp>
#include <Galaxy-Standard/map.hpp>


#include <Nebula/Types.hh>
#include <Nebula/Util/typedef.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <Nebula/Scene/Util/Flag.hh>
#include <Nebula/Scene/Util/Types.hh>

//#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/Graphics/glsl/program.hh>


//#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Parent.hh>

//#include <Nebula/Graphics/Camera/View/Base.hh>
#include <Nebula/Graphics/Drawable/Base.hpp>


#define LIGHT_MAX 20

namespace neb { namespace core { namespace scene {


	/** 
	 * @ingroup group_core
	 * @brief Base
	 */
	class base:
		virtual public neb::gfx::drawable::base,
		virtual public neb::core::actor::util::parent
	{
		public:
			base(sp::shared_ptr<neb::core::scene::util::parent>);
			virtual ~base();
			virtual void				init();
			virtual void				release();
			/** @name Main Loop @{ */
			/** @brief render */

			void				draw(sp::shared_ptr<neb::gfx::context::base> context, sp::shared_ptr<neb::glsl::program> p);
			void				resize(int w, int h);
			virtual void			step(neb::core::TimeStep const & ts);
			/** @} */

			virtual  void			serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("i",i_);
				ar & boost::serialization::make_nvp("flag",flag_);
			}
			virtual void			serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("i",i_);
				ar & boost::serialization::make_nvp("flag",flag_);
			}
		public:
			neb::core::pose						getPose();
			neb::core::pose						getPoseGlobal();
		public:
			void							add_deferred(sp::shared_ptr<neb::core::actor::base>);


			/** @name convenience functions
			 * @{
			 */
			/** @brief create rigidstatic cube
			 *
			 * @note typeof returned actor will be determined by final implementation of this
			 */
			sp::weak_ptr<neb::core::actor::rigidstatic::base>		createActorRigidStaticCube(neb::core::pose const & pose, real size);
			/** @brief create rigidstatic
			 *
			 * @note typeof returned actor will be determined by final implementation of this
			 *
			 * @warning return actor is not initialized
			 */
			virtual sp::weak_ptr<neb::core::actor::rigidstatic::base>	createActorRigidStaticUninitialized() = 0;
			/** @} */
		public:
			/** @brief parent
			 *
			 * @note WEAK
			 */
			sp::shared_ptr<neb::core::scene::util::parent>		parent_;

		public:
			neb::core::scene::util::Flag					flag_;

			::std::map< ::std::string, sp::shared_ptr<neb::core::actor::base> >		actors_deferred_;

			float		last_;
	};



}}}

#endif





