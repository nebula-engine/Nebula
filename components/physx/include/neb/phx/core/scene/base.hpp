#ifndef PHYSX_CORE_SCENE_BASE_HPP
#define PHYSX_CORE_SCENE_BASE_HPP

#include <vector>

#include <PxPhysicsAPI.h>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <gal/etc/flag.hpp>
#include <gal/stl/map.hpp>

#include <neb/core/util/decl.hpp>
#include <neb/core/util/typedef.hpp>
#include <neb/core/math/Serialization/glm.hpp>
#include <neb/core/core/actor/util/parent.hpp>
#include <neb/core/core/scene/base.hpp>

<<<<<<< HEAD
=======
#include <neb/gfx/drawable/base.hpp>
#include <neb/gfx/glsl/uniform/light_array.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
#include <neb/phx/core/actor/util/decl.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/simulation_callback.hh>

typedef weak_ptr<neb::core::core::actor::base> wbase;

<<<<<<< HEAD
namespace neb { namespace phx { namespace core { namespace scene {
=======
namespace neb {
	namespace gfx {
		class RenderDesc;
	}

	namespace phx { namespace core { namespace scene {
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

	/** 
	 * @ingroup group_core
	 * @brief base
	 */
	class base:
		virtual public neb::core::core::scene::base,
<<<<<<< HEAD
		virtual public phx::core::actor::util::parent
	{
		public:
			base(std::shared_ptr<neb::core::core::scene::util::parent> parent);
			virtual ~base();
			void					init();
			void					release();
			void					step(::gal::etc::timestep const & ts);
		public:
			void					create_physics();
			virtual  void				serialize(
					boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("gravity",gravity_);
			}
			virtual void				serialize(
					boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("gravity",gravity_);
			}
=======
		virtual public neb::gfx::drawable::base
	{
		public:
			base();
			virtual ~base();
			virtual void				init(parent_t * const & p);
			void					init_light();
			virtual void				release();
			void					step(::gal::etc::timestep const & ts);


			void					resize(int w, int h);

			void					draw(gfx::RenderDesc const &);
			void					drawMesh(gfx::RenderDesc const &);
			void					drawMeshHF(gfx::RenderDesc const &);
			void					drawMeshInst(gfx::RenderDesc const &);
			void					drawPhysxVisualization(gfx::RenderDesc const &);
			void					drawDebug(gfx::RenderDesc const &);


		public:
			void					create_physics();
			virtual void				load(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
			virtual void				save(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) const;
			BOOST_SERIALIZATION_SPLIT_MEMBER();
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
			/** @name convenience functions
			 * @{
			 */
			/** @brief create rigiddynamic
			 *
			 * @note typeof returned actor will be determined by final implementation of this
			 *
			 * @warning return actor is not initialized
			 */
			virtual weak_ptr<neb::core::core::actor::base>		createActorRigidStaticUninitialized() = 0;
			/** @brief create rigidstatic
			 *
			 * @note typeof returned actor will be determined by final implementation of this
			 *
			 * @warning return actor is not initialized
			 */
			virtual weak_ptr<neb::core::core::actor::base>		createActorRigidDynamicUninitialized() = 0;
			/** @} */
<<<<<<< HEAD
=======




			// rendering data
			
			struct
			{
				std::shared_ptr<neb::gfx::glsl::program::threed>	_M_d3;
				std::shared_ptr<neb::gfx::glsl::program::threed>	_M_d3_HF;
				std::shared_ptr<neb::gfx::glsl::program::threed>	_M_d3_inst;
			} _M_programs;
			
			// one for static, one for dynamic
			std::shared_ptr<neb::gfx::glsl::uniform::light_array>		light_array_[2];

			std::shared_ptr<neb::gfx::texture>				tex_shadow_map_;

			// standard meshes
			struct {
				std::shared_ptr<neb::gfx::mesh::instanced>		cuboid_;
			} meshes_;








>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
		public:
			physx::PxScene*						px_scene_;
			physx::PxSimulationFilterShader				px_filter_shader_;
			neb::phx::simulation_callback*				simulation_callback_;
			vec3							gravity_;
			//neb::vehicle_manager					vehicle_manager_;
	};
}}}}

#endif





