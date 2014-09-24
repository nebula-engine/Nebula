#ifndef __GLUTPP_SHAPE_H__
#define __GLUTPP_SHAPE_H__

#include <map>

//#include <GL/glew.h>
//#include <GLFW/glfw3.h>

#include <boost/serialization/map.hpp>

#include <gal/etc/timestep.hpp>

#include <gal/stl/child.hpp>

#include <neb/core/itf/serializable.hpp>
#include <neb/core/util/log.hpp>
#include <neb/core/core/shape/util/parent.hpp>
#include <neb/core/core/shape/util/flag.hpp>
#include <neb/core/core/light/util/decl.hpp>
#include <neb/core/core/light/util/parent.hpp>
#include <neb/core/core/light/util/light_count.hpp>

namespace neb { namespace core { namespace core { namespace shape {
	class base:
		virtual public neb::itf::shared,
		virtual public neb::serializable,
		virtual public neb::core::core::shape::util::parent,
		virtual public neb::core::core::light::util::parent,
		virtual public gal::stl::child<neb::core::core::shape::util::parent>
	{
		public:
			typedef neb::core::core::shape::util::parent parent_t;
			base();
			virtual ~base();
			virtual void		init(parent_t * const &);
			void			release();
			void			step(gal::etc::timestep const & ts);
			virtual void		callbackPose(neb::core::pose const & pose_global) = 0;
			virtual void		__callbackPose(neb::core::pose const & pose_global);
			/** @name Accessors @{ */


			bool							hasScene();
			neb::core::core::scene::base*				getScene();


			neb::core::pose						getPose() const;
			neb::core::pose						getPoseGlobal() const;
			/** @} */
			virtual weak_ptr<neb::core::core::light::base>		createLightPoint() = 0;
			virtual weak_ptr<neb::core::core::light::base>		createLightSpot(glm::vec3) = 0;
			virtual weak_ptr<neb::core::core::light::base>		createLightDirectional(glm::vec3) = 0;
		public:
/*			virtual void	load(ba::binary_iarchive & ar, unsigned int const &) {}
			virtual void	save(ba::binary_oarchive & ar, unsigned int const &) const {}
			virtual void	load(ba::xml_iarchive & ar, unsigned int const &) {}
			virtual void	save(ba::xml_oarchive & ar, unsigned int const &) const {}*/
			virtual void	load(ba::polymorphic_iarchive & ar, unsigned int const &);
			virtual void	save(ba::polymorphic_oarchive & ar, unsigned int const &) const;
			BOOST_SERIALIZATION_SPLIT_MEMBER();
		protected:
			template<class Archive>	void				__serialize(
					Archive & ar, unsigned int const & version)
			{
				LOG(lg, neb::core::core::shape::sl, debug) << __PRETTY_FUNCTION__;
	
				ar & boost::serialization::make_nvp("flag",flag_);
				ar & boost::serialization::make_nvp("pose",pose_);
				ar & boost::serialization::make_nvp("scale",scale_);
				ar & boost::serialization::make_nvp("image",image_);
				ar & boost::serialization::make_nvp("normal",normal_);

				//ar & BOOST::SERIALIZATION::make_NVP("lights", neb::core::core::light::util::parent::map_);

				ar & boost::serialization::make_nvp(
						"shapes",
						neb::core::core::shape::util::parent::map_
						);
				ar & boost::serialization::make_nvp(
						"lights",
						neb::core::core::light::util::parent::map_
						);

			}

		public:
			neb::core::core::shape::util::flag		flag_;
			/** @brief pose */
			neb::core::pose					pose_;
			/** @brief scale */
			glm::vec3					scale_;
			/** @brief Name of image file */
			string						image_;
			/** @brief Name of normal map file */
			string						normal_;
		public:


	};
}}}}

#endif

