#include <stdio.h>

#include <gal/log/log.hpp>

#include <neb/core/util/cast.hpp>
#include <neb/core/util/debug.hpp>
#include <neb/core/core/scene/util/decl.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/core/actor/rigidstatic/base.hpp>
#include <neb/phx/core/actor/rigiddynamic/base.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/util/convert.hpp>
#include <neb/phx/util/log.hpp>



#include <neb/core/util/log.hpp>
#include <neb/core/util/config.hpp>
#include <neb/core/core/light/base.hpp>
#include <neb/core/core/light/util/light_count.hpp>
#include <neb/core/timer/Types.hh>
#include <neb/core/timer/Actor/Release.hpp>
#include <neb/core/math/geo/polyhedron.hh>

#include <neb/phx/core/scene/base.hpp>

#include <neb/gfx/core/actor/base.hpp>
#include <neb/gfx/core/shape/base.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/camera/view/Base.hh>
#include <neb/gfx/mesh/instanced.hpp>
#include <neb/gfx/texture.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/RenderDesc.hpp>

typedef neb::phx::core::scene::base THIS;

typedef neb::core::core::actor::util::parent A;

typedef neb::gfx::glsl::program::base	P;
typedef neb::gfx::glsl::program::threed	P3;

neb::phx::core::scene::base::base():
	px_scene_(NULL),
	px_filter_shader_(NULL),
	simulation_callback_(NULL)
{
	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__;

	flag_.set(neb::core::core::scene::util::flag::PHYSX_VISUALIZATION);
}
neb::phx::core::scene::base::~base() {

	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__;

	assert(px_scene_ == NULL);
}
void			neb::phx::core::scene::base::init(parent_t * const & p)
{
	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__;

	//neb::core::core::scene::base::init(p);

	create_physics();

	// graphics

	// use _M_programs._M_d3 as completion flag
	if(!_M_programs._M_d3)
	{
		// programs
		_M_programs._M_d3.reset(new P3("3d"));
		_M_programs._M_d3->init();

		_M_programs._M_d3_HF.reset(new P3("3d_HF"));
		_M_programs._M_d3_HF->init();

		_M_programs._M_d3_inst.reset(new P3("3d_inst"));
		_M_programs._M_d3_inst->init();

		init_light();

		// meshes
		math::geo::cuboid cube(1.0,1.0,1.0);

		meshes_.cuboid_.reset(new neb::gfx::mesh::instanced);
		meshes_.cuboid_->mesh_.construct(&cube);

		meshes_.cuboid_->instances_.reset(new neb::gfx::mesh::instanced::instances_type);
		meshes_.cuboid_->instances_->alloc(2048);

		unsigned int shadow_tex_size = 512;

		tex_shadow_map_ = std::make_shared<neb::gfx::texture>();
		tex_shadow_map_->init_shadow(
				shadow_tex_size,
				shadow_tex_size,
				std::shared_ptr<neb::gfx::context::base>());
	}
}
void			THIS::init_light()
{
	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__;

	if(!light_array_[0])
	{
		// light arrays
		light_array_[0].reset(new neb::gfx::glsl::uniform::light_array);
		light_array_[0]->alloc(32);

		light_array_[1].reset(new neb::gfx::glsl::uniform::light_array);
		light_array_[1]->alloc(32);
	}
}
void			neb::phx::core::scene::base::release() {
	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__;

	if(px_scene_)
	{
		px_scene_->release();
		px_scene_ = NULL;
	}
}
void			neb::phx::core::scene::base::create_physics() {
	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__;

	if(px_scene_ != NULL) {
		LOG(lg, neb::phx::core::scene::sl, debug) << "been here!";
		return;
	}

	auto pxphysics = neb::phx::app::base::global()->px_physics_;

	physx::PxSceneDesc scene_desc(pxphysics->getTolerancesScale());

	scene_desc.gravity = phx::util::convert(gravity_);

	scene_desc.flags |= physx::PxSceneFlag::eENABLE_ACTIVETRANSFORMS;

	int m_nbThreads = 1;

	// cpu dispatcher
	printf("cpu dispatcher\n");
	if( !scene_desc.cpuDispatcher )
	{
		physx::PxDefaultCpuDispatcher* cpuDispatcher =
			::physx::PxDefaultCpuDispatcherCreate( m_nbThreads );

		assert( cpuDispatcher );

		scene_desc.cpuDispatcher = cpuDispatcher;
	}

	// filter shader
	printf("filter shader\n");
	if(!scene_desc.filterShader)
	{
		if(px_filter_shader_)
		{
			scene_desc.filterShader = px_filter_shader_;
		}
		else
		{
			scene_desc.filterShader = DefaultFilterShader;
		}
	}

	// gpu dispatcher
	printf("gpu dispatcher\n");
#ifdef PX_WINDOWS
	if( !scene_desc.gpuDispatcher && m_cudaContextManager )
	{
		sceneDesc.gpuDispatcher = m_cudaContextManager->getGpuDispatcher();
	}
#endif
	assert( scene_desc.isValid() );

	px_scene_ = pxphysics->createScene(scene_desc);
	assert(px_scene_);

	// simulation callback
	phx::simulation_callback* sec = new phx::simulation_callback;

	simulation_callback_ = sec;

	px_scene_->setSimulationEventCallback(sec);


	// visualization
	physx::PxVisualizationParameter::Enum flags[] = {
		physx::PxVisualizationParameter::eSCALE,
		physx::PxVisualizationParameter::eWORLD_AXES,
		physx::PxVisualizationParameter::eBODY_AXES,
		physx::PxVisualizationParameter::eBODY_MASS_AXES,
		physx::PxVisualizationParameter::eBODY_LIN_VELOCITY,
		physx::PxVisualizationParameter::eBODY_ANG_VELOCITY,
		physx::PxVisualizationParameter::eBODY_JOINT_GROUPS,
		physx::PxVisualizationParameter::eCONTACT_POINT,
		physx::PxVisualizationParameter::eCONTACT_NORMAL,
		physx::PxVisualizationParameter::eCONTACT_ERROR,
		physx::PxVisualizationParameter::eCONTACT_FORCE,
		physx::PxVisualizationParameter::eACTOR_AXES,
		physx::PxVisualizationParameter::eCOLLISION_AABBS,
		physx::PxVisualizationParameter::eCOLLISION_SHAPES,
		physx::PxVisualizationParameter::eCOLLISION_AXES,
		physx::PxVisualizationParameter::eCOLLISION_COMPOUNDS,
		physx::PxVisualizationParameter::eCOLLISION_FNORMALS,
		physx::PxVisualizationParameter::eCOLLISION_EDGES,
		physx::PxVisualizationParameter::eCOLLISION_STATIC,
		physx::PxVisualizationParameter::eCOLLISION_DYNAMIC,
		physx::PxVisualizationParameter::eCOLLISION_PAIRS,
		physx::PxVisualizationParameter::eJOINT_LOCAL_FRAMES,
		physx::PxVisualizationParameter::eJOINT_LIMITS,
		physx::PxVisualizationParameter::ePARTICLE_SYSTEM_POSITION,
		physx::PxVisualizationParameter::ePARTICLE_SYSTEM_VELOCITY,
		physx::PxVisualizationParameter::ePARTICLE_SYSTEM_COLLISION_NORMAL,
		physx::PxVisualizationParameter::ePARTICLE_SYSTEM_BOUNDS,
		physx::PxVisualizationParameter::ePARTICLE_SYSTEM_GRID,
		physx::PxVisualizationParameter::ePARTICLE_SYSTEM_BROADPHASE_BOUNDS,
		physx::PxVisualizationParameter::ePARTICLE_SYSTEM_MAX_MOTION_DISTANCE,
		physx::PxVisualizationParameter::eCULL_BOX,
		physx::PxVisualizationParameter::eCLOTH_VERTICAL,
		physx::PxVisualizationParameter::eCLOTH_HORIZONTAL,
		physx::PxVisualizationParameter::eCLOTH_BENDING,
		physx::PxVisualizationParameter::eCLOTH_SHEARING,
		physx::PxVisualizationParameter::eCLOTH_VIRTUAL_PARTICLES,
		physx::PxVisualizationParameter::eMBP_REGIONS
	};

	for(unsigned int i = 0; i < (sizeof(flags) / sizeof(unsigned int)); i++)
	{
		px_scene_->setVisualizationParameter(flags[i], 1.0f);
	}



}
void			neb::phx::core::scene::base::step(gal::etc::timestep const & ts) {

	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__ << " dt = " << ts.dt;

	auto app = phx::app::base::global();

	// timer
	//timer_set_.step(time);

	//physx::PxU32 nbPxactor = px_scene_->getNbActors(physx::PxActorTypeSelectionFlag::eRIGID_DYNAMIC);

	// PxScene
	assert(px_scene_ != NULL);

	typedef neb::core::core::actor::util::parent A;


	//========================================================================
	// lock all actors

	A::map_.for_each([&] (A::map_type::pointer p) {
			auto actor = std::dynamic_pointer_cast<neb::core::core::actor::base>(p);
			assert(actor);
			actor->mutex_.lock();
			LOG(lg, neb::phx::core::scene::sl, debug) << "actor = " << actor.get();
			});

	LOG(lg, neb::phx::core::scene::sl, debug) << "actors locked";
	/*A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
	  auto actor = std::dynamic_pointer_cast<neb::core::core::actor::base>(it->ptr_);
	  assert(actor);
	  LOG(lg, neb::phx::core::scene::sl, debug) << "actor = " << actor.get();
	  });*/

	LOG(lg, neb::phx::core::scene::sl, debug) << "simulate";

	px_scene_->simulate(ts.dt);
	px_scene_->fetchResults(true);

	LOG(lg, neb::phx::core::scene::sl, debug) << "simulation complete";

	// retrieve array of actors that moved
	physx::PxU32 nb_active_transforms;
	const physx::PxActiveTransform* active_transforms = px_scene_->getActiveTransforms(nb_active_transforms);


	LOG(lg, neb::phx::core::scene::sl, debug)
		<< "active transforms: " << nb_active_transforms;

	//physx::PxTransform pose;
	physx::PxTransform pose;

	// update each render object with the new transform
	for(physx::PxU32 i = 0; i < nb_active_transforms; ++i) {
		//physx::PxActor* px_actor = active_transforms[i].actor;

		//printf( "actor type = %i\n", px_actor->getType() );

		physx::PxActor* pxactor = active_transforms[i].actor;
		assert(pxactor);

		void* ud = active_transforms[i].userData;
		assert(ud);

		LOG(lg, neb::phx::core::scene::sl, debug) << "ud = " << ud;

		physx::PxRigidBody* pxrigidbody = pxactor->isRigidBody();


		neb::core::core::actor::base* pactor = static_cast<neb::core::core::actor::base*>(ud);
		auto actor = pactor->isActorBase();
		assert(actor);

		if(actor) {
			pose = active_transforms[i].actor2World;
			actor->setPose(neb::core::pose(
						phx::util::convert(pose.p),
						phx::util::convert(pose.q)
						));

			LOG(lg, neb::phx::core::scene::sl, debug)
				<< ::std::setw(8) << "p"
				<< ::std::setw(8) << pose.p.x
				<< ::std::setw(8) << pose.p.y
				<< ::std::setw(8) << pose.p.z;

			if(pxrigidbody != NULL) {
				auto rigidbody = ::std::dynamic_pointer_cast<phx::core::actor::rigidbody::base>(actor);
				if(!rigidbody) {
					std::cout << typeid(*actor).name() << ::std::endl;
					abort();
				}

				physx::PxVec3 v(pxrigidbody->getLinearVelocity());

				rigidbody->velocity_ = phx::util::convert(v);

				//v.print();
			}

			actor->flag_.set(neb::core::core::actor::util::flag::E::SHOULD_UPDATE);
		}
	}
	// unlock all actors
	A::map_.for_each([&] (A::map_type::pointer p) {
			auto actor = std::dynamic_pointer_cast<neb::core::core::actor::base>(p);
			assert(actor);
			actor->mutex_.unlock();
			});




	// vehicle
	//physx::PxVec3 g(0,-0.25,0);
	//vehicle_manager_.vehicle_suspension_raycasts(px_scene_);
	//vehicle_manager_.update((float)dt, g);
	//send_actor_update();
}


void			neb::phx::core::scene::base::draw(neb::gfx::RenderDesc const & desc)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	assert(desc.p);
	assert(desc.v);

	drawMesh(desc);
	drawMeshHF(desc);
	drawMeshInst(desc);
}
void			THIS::drawMesh(neb::gfx::RenderDesc const & desc)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	// If program parameter is not NULL, use it and do not load lights.
	//
	// For rendering lights, use one of the programs owned by this, which contain persistent data for the lights.

	P* d3;

	if(desc.d3) {
		d3 = desc.d3;
	} else {
		assert(_M_programs._M_d3);
		d3 = _M_programs._M_d3.get();
	}

	assert(d3);

	d3->use();

	desc.p->load(d3);
	desc.v->load(d3);

	// lights
	assert(light_array_[0]);
	light_array_[0]->load_uniform(d3);

	// individual meshes
	auto la = [&] (A::map_type::pointer p) {
		auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(p);
		assert(actor);
		actor->draw(d3, neb::core::pose());
	};

	A::map_.for_each(la);

}
void			THIS::drawMeshHF(neb::gfx::RenderDesc const & desc)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	// If program parameter is not NULL, use it and do not load lights.
	//
	// For rendering lights, use one of the programs owned by this, which contain persistent data for the lights.

	P* p;

	if(desc.d3_HF) {
		p = desc.d3_HF;
	} else {
		assert(_M_programs._M_d3_HF);
		p = _M_programs._M_d3_HF.get();
	}

	assert(p);

	p->use();

	desc.p->load(p);
	desc.v->load(p);

	// lights
	assert(light_array_[0]);
	light_array_[0]->load_uniform(p);

	// individual meshes
	auto la = [&] (A::map_type::pointer ptr) {
		auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(ptr);
		assert(actor);
		actor->drawHF(p, neb::core::pose());
	};

	A::map_.for_each(la);

}
void			THIS::drawMeshInst(neb::gfx::RenderDesc const & desc)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	P* d3_inst;

	if(desc.d3_inst) {
		d3_inst = desc.d3_inst;
	} else {
		assert(_M_programs._M_d3);
		d3_inst = _M_programs._M_d3_inst.get();
	}

	assert(d3_inst);

	d3_inst->use();

	desc.p->load(d3_inst);
	desc.v->load(d3_inst);

	// lights
	assert(light_array_[0]);
	light_array_[0]->load_uniform(d3_inst);

	if(tex_shadow_map_) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(tex_shadow_map_->target_, tex_shadow_map_->o_);

		GLint loc = d3_inst->uniform_table_[neb::gfx::glsl::uniforms::TEX_SHADOW_MAP];
		neb::gfx::ogl::glUniform(loc, 0);
	}

	// meshes
	assert(meshes_.cuboid_);
	meshes_.cuboid_->draw(d3_inst);

}
void			neb::phx::core::scene::base::drawDebug(
		neb::gfx::RenderDesc const & desc)
{
	auto app(neb::gfx::app::__gfx_glsl::global().lock());

	auto p = app->program_simple3_;
	p->use();

	desc.p->load(p.get());
	desc.v->load(p.get());

	// individual meshes
	auto la = [&] (A::map_type::pointer ptr) {
		auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(ptr);
		assert(actor);
		actor->drawDebug(p.get(), neb::core::pose());
	};

	A::map_.for_each(la);

}	
void			neb::phx::core::scene::base::drawPhysxVisualization(
		neb::gfx::RenderDesc const & desc)
{

	auto app(neb::gfx::app::__gfx_glsl::global().lock());

	if(!flag_.all(neb::core::core::scene::util::flag::PHYSX_VISUALIZATION)) return;

	// visual debugging
	if(px_scene_)
	{
		const physx::PxRenderBuffer& rb = px_scene_->getRenderBuffer();

		physx::PxU32 nblines = rb.getNbLines();
		const physx::PxDebugLine* lines = rb.getLines();

		physx::PxU32 nbtriangles = rb.getNbTriangles();
		const physx::PxDebugTriangle* triangles = rb.getTriangles();


		auto p = app->program_simple3_;
		p->use();


		//auto e = neb::could_be<neb::gfx::environ::base, neb::gfx::environ::three>(context->environ_);
		//if(e)
		{
			desc.p->load(p.get());
			desc.v->load(p.get());

			glClear(GL_DEPTH_BUFFER_BIT);


			LOG(lg, neb::phx::core::scene::sl, debug) << "Debug visualization";
			LOG(lg, neb::phx::core::scene::sl, debug) << "number of points    " << rb.getNbPoints();
			LOG(lg, neb::phx::core::scene::sl, debug) << "number of lines     " << nblines;
			LOG(lg, neb::phx::core::scene::sl, debug) << "number of triangles " << nbtriangles;


			GLint i_color = p->attrib_table_[neb::gfx::glsl::attribs::COLOR];

			glEnableVertexAttribArray(p->attrib_table_[neb::gfx::glsl::attribs::POSITION]);
			if(i_color > -1)
				glEnableVertexAttribArray(i_color);

			GLuint buf;
			glGenBuffers(1, &buf);
			glBindBuffer(GL_ARRAY_BUFFER, buf);


			// lines
			glBufferData(
					GL_ARRAY_BUFFER,
					sizeof(physx::PxDebugLine) * nblines,
					lines,
					GL_STREAM_DRAW
				    );

			glVertexAttribPointer(
					p->attrib_table_[neb::gfx::glsl::attribs::POSITION],
					3,
					GL_FLOAT,
					GL_FALSE,
					16,
					0);


			if(i_color > -1)
				glVertexAttribIPointer(
						p->attrib_table_[neb::gfx::glsl::attribs::COLOR],
						1,
						GL_UNSIGNED_INT,
						16,
						(GLvoid*)12);

			glDrawArrays(GL_LINES, 0, nblines * 2);

			checkerror("");

			// triangles
			glBufferData(
					GL_ARRAY_BUFFER,
					sizeof(physx::PxDebugTriangle) * nbtriangles,
					triangles,
					GL_STREAM_DRAW
				    );

			glVertexAttribPointer(
					p->attrib_table_[neb::gfx::glsl::attribs::POSITION],
					3,
					GL_FLOAT,
					GL_FALSE,
					16,
					0);


			if(i_color > -1)
				glVertexAttribIPointer(
						p->attrib_table_[neb::gfx::glsl::attribs::COLOR],
						1,
						GL_UNSIGNED_INT,
						16,
						(GLvoid*)12);

			glDrawArrays(GL_TRIANGLES, 0, nbtriangles * 3);

			checkerror("");

			// cleanup
			glDisableVertexAttribArray(p->attrib_table_[neb::gfx::glsl::attribs::POSITION]);
			if(i_color > -1)
				glDisableVertexAttribArray(p->attrib_table_[neb::gfx::glsl::attribs::COLOR]);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}
void			neb::phx::core::scene::base::resize(int w, int h) {
}
void			THIS::load(boost::archive::polymorphic_iarchive & ar, unsigned int const & version)
{
	ar & boost::serialization::make_nvp("gravity",gravity_);
}
void			THIS::save(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) const
{
	ar & boost::serialization::make_nvp("gravity",gravity_);
}



