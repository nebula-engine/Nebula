#ifndef __GLUTPP_GFX_CORE_SCENE_H__
#define __GLUTPP_GFX_CORE_SCENE_H__


namespace neb { namespace gfx { namespace core { namespace scene {


	/** 
	 * @ingroup group_core
	 * @brief Base
	 */
	class base:
		virtual public neb::core::scene::base,
		virtual public neb::gfx::drawable::base
	{
		public:
			base(sp::shared_ptr<neb::core::scene::util::parent>);
			virtual ~base();
			virtual void				init();
			virtual void				release();
			/** @name Main Loop @{ */
			/** @brief render */

			void				draw(sp::shared_ptr<neb::gfx::context::base> context, sp::shared_ptr<neb::glsl::program> p);
			virtual void			step(gal::std::timestep const & ts);
			/** @} */

	};

	class local:
		virtual public neb::core::scene::remote,
		virtual public neb::gfx::core::scene::base
	{
	};
	class remote:
		virtual public neb::core::scene::remote,
		virtual public neb::gfx::core::scene::base
	{
	};



}}}}

#endif





