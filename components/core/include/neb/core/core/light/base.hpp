#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <neb/core/color/Color.hh>
#include <neb/core/math/Serialization/glm.hpp>
#include <neb/core/pose.hpp>
#include <neb/core/core/light/__base.hpp>
<<<<<<< HEAD
=======
#include <neb/core/core/scene/util/decl.hpp>
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
#include <neb/core/core/light/util/decl.hpp>
#include <neb/core/core/light/util/Flag.hh>
#include <neb/core/core/light/util/light_count.hpp>
#include <neb/core/util/decl.hpp>

namespace neb { namespace core { namespace core { namespace light {
<<<<<<< HEAD
	class base: virtual public neb::core::light::__base {
		public:
			base(std::shared_ptr<neb::core::core::light::util::parent> parent);

			void				init();

			virtual void			release();
			virtual void			step(gal::etc::timestep const & ts);

			neb::core::pose			getPose();
			glm::vec4			getPos();
		private:
			template<class Archive> void		serializeTemplate(
					Archive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("i",i_);
				ar & boost::serialization::make_nvp("flag",flag_);
				ar & boost::serialization::make_nvp("pos",pos_);
=======
	class base: public neb::core::light::__base
	{
		public:
			base();

			virtual void			init(neb::core::core::light::util::parent * const & p) = 0;

			//virtual void			release();
			//virtual void			step(gal::etc::timestep const & ts);

			neb::core::pose			getPose();
			neb::core::pose			getPoseGlobal();
			glm::vec4			getPos();

			bool				hasScene() const;
			neb::core::core::scene::base*	getScene();
		private:
			template<class Archive> void		serializeTemplate(
					Archive & ar, unsigned int const & version) {
				//ar & boost::serialization::make_nvp("i",i_);
				ar & boost::serialization::make_nvp("flag",flag_);
				//ar & boost::serialization::make_nvp("pos",pos_);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
				/*
				   ar & boost::serialization::make_nvp("atten_const",atten_const_);
				   ar & boost::serialization::make_nvp("atten_linear",atten_linear_);
				   ar & boost::serialization::make_nvp("atten_quad",atten_quad_);*/
			}
		public:
<<<<<<< HEAD
			virtual void				serialize(
					boost::archive::polymorphic_iarchive & ar,
					unsigned int const & version) {
				serializeTemplate(ar, version);
			}
			virtual void				serialize(
					boost::archive::polymorphic_oarchive & ar,
					unsigned int const & version) {
				serializeTemplate(ar, version);
			}
		public:


			weak_ptr<neb::core::core::light::util::parent>		parent_;

			neb::core::core::light::util::flag			flag_;

			// position
			glm::vec3						pos_;
=======
			virtual void				load(
					boost::archive::polymorphic_iarchive & ar,
					unsigned int const & version);
			virtual void				save(
					boost::archive::polymorphic_oarchive & ar,
					unsigned int const & version) const;
			BOOST_SERIALIZATION_SPLIT_MEMBER();
		public:


			neb::core::core::light::util::flag			flag_;
			
			neb::core::pose						pose_;

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	};
}}}}

#endif

