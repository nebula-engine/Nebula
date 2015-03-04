

#include <assert.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <PxPhysicsAPI.h>

#include <gal/log/log.hpp>

#include <neb/fnd/core/scene/Base.hpp>
#include <neb/fnd/util/debug.hpp>

#include <neb/phx/simulation_callback.hh>
#include <neb/phx/app/base.hpp>
#include <neb/phx/test.hpp>

typedef neb::phx::app::base THIS;

physx::PxFilterFlags	DefaultFilterShader(
		physx::PxFilterObjectAttributes attributes0,
		physx::PxFilterData filterData0,
		physx::PxFilterObjectAttributes attributes1,
		physx::PxFilterData filterData1,
		physx::PxPairFlags& pairFlags,
		const void* constantBlock,
		physx::PxU32 constantBlockSize )
{	
	printf(/*DEBUG, */"%s\n", __PRETTY_FUNCTION__);
	//printv(DEBUG, "%i %i %i %i\n", filterData0.word0, filterData1.word1, filterData1.word0, filterData0.word1);
	
	physx::PxFilterFlags filter_flags = physx::PxFilterFlag::eDEFAULT;
	
	// let triggers through
	if(physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
		return physx::PxFilterFlag::eDEFAULT;
	}
	
	// collision
	physx::PxU32 w0 = filterData0.word0 & filterData1.word1;
	physx::PxU32 w1 = filterData1.word0 & filterData0.word1;
	
	if(w0 && w1) {
		pairFlags |= physx::PxPairFlag::eCONTACT_DEFAULT;
		
		filter_flags = physx::PxFilterFlag::eDEFAULT;

		//printf("collision\n");
	} else {
		filter_flags = physx::PxFilterFlag::eSUPPRESS;
		//printf("suppress\n");
	}
	
	// notification
	physx::PxU32 w2 = filterData0.word2 & filterData1.word3;
	physx::PxU32 w3 = filterData1.word2 & filterData0.word3;

	if(w2 && w3)
	{
		pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
	}
	
	return filter_flags;
}

void DefaultErrorCallback::reportError(
		physx::PxErrorCode::Enum code,
		char const * message,
		char const * file,
		int line)
{
	printf(/*DEBUG, */"%s:%i: %s\n",file,line,message);
}
THIS::base():
	px_physics_(NULL)
{
}
void				THIS::init(parent_t * const & parent)
{
	setParent(parent);

	// Physx
	// Foundation
	px_foundation_ = PxCreateFoundation(
			PX_PHYSICS_VERSION,
			px_default_allocator_callback_,
			px_default_error_callback_);
	assert(px_foundation_);
	
	bool recordMemoryAllocations = true;

	// Profile Zone Manager
	px_profile_zone_manager_ = &::physx::PxProfileZoneManager::createProfileZoneManager( px_foundation_ );
	assert( px_profile_zone_manager_ );

	// Physics
	px_physics_ = PxCreatePhysics(
			PX_PHYSICS_VERSION,
			*px_foundation_,
			physx::PxTolerancesScale(),
			recordMemoryAllocations, px_profile_zone_manager_ );
	assert( px_physics_ );

	// cooking
	/** @todo fix cooking signature */
	auto scales = physx::PxTolerancesScale();
	
	px_cooking_ = PxCreateCooking( PX_PHYSICS_VERSION, *px_foundation_, ::physx::PxCookingParams(scales) );
	assert( px_cooking_ );

	// Extensions
	assert( PxInitExtensions( *px_physics_ ) );

	// character controller manager
	/** @todo fix cooking signature */
/*	px_character_controller_manager_ = ::PxCreateControllerManager( *px_foundation_ );
	assert( px_character_controller_manager_ );*/

	// vehicle
	assert( PxInitVehicleSDK(*px_physics_) );
	PxVehicleSetBasisVectors(physx::PxVec3(0,1,0), physx::PxVec3(0,0,-1));
	PxVehicleSetUpdateMode(physx::PxVehicleUpdateMode::Enum::eACCELERATION);
}
void			THIS::release()
{
	printv_func(DEBUG);

	physx::PxCloseVehicleSDK();

	px_physics_->release();
	px_foundation_->release();
}
void			THIS::step(gal::etc::timestep const & ts)
{
	printv_func(DEBUG);

	//neb::phx::game::game::util::parent::step(ts);

}
physx::PxConvexMeshGeometry*	THIS::frustrum_geometry(glm::mat4 proj)
{
	//auto app = get_phx_app();

	glm::vec4 gverts[8] = {
		glm::vec4( 1, 1, 1,1),
		glm::vec4( 1,-1, 1,1),
		glm::vec4(-1, 1, 1,1),
		glm::vec4(-1,-1, 1,1),
		glm::vec4( 1, 1,-1,1),
		glm::vec4( 1,-1,-1,1),
		glm::vec4(-1, 1,-1,1),
		glm::vec4(-1,-1,-1,1)};

	physx::PxVec3 verts[8];

	glm::mat4 inv = glm::inverseTranspose(glm::transpose(proj));

	//printv(DEBUG, "proj\n", proj);
	//printv(DEBUG, "inv \n", inv);

	printv(DEBUG, "verts\n");
	for(int c = 0; c < 8; c++)
	{
		gverts[c] = inv * gverts[c];
		gverts[c] = gverts[c] / gverts[c].w;
		verts[c] = physx::PxVec3(
				gverts[c].x,
				gverts[c].y,
				gverts[c].z);

	}

/*	physx::PxHullPolygon polys[6];

	glm::vec3 n;

	// near
	n = glm::vec3(0,0,1);
	polys[0].mPlane[0] = n.x;
	polys[0].mPlane[1] = n.y;
	polys[0].mPlane[2] = n.z;
	polys[0].mPlane[3] = glm::dot(n, glm::vec3(gverts[4]));
*/

	physx::PxConvexMeshDesc convexDesc;
	convexDesc.points.count     = 8;
	convexDesc.points.stride    = sizeof(physx::PxVec3);
	convexDesc.points.data      = verts;
	convexDesc.flags            = physx::PxConvexFlag::eCOMPUTE_CONVEX;
	convexDesc.vertexLimit      = 256;



	//PxToolkit::MemoryOutputStream buf;
	physx::PxDefaultMemoryOutputStream buf;
	if(!px_cooking_->cookConvexMesh(convexDesc, buf))
		abort();

	physx::PxDefaultMemoryInputData input(buf.getData(), buf.getSize());

	physx::PxConvexMesh* convexMesh = px_physics_->createConvexMesh(input);

	physx::PxConvexMeshGeometry* g = new physx::PxConvexMeshGeometry(convexMesh);

	assert(g->isValid());

	//auto b = convexMesh->getLocalBounds();

	const physx::PxVec3* nverts = convexMesh->getVertices();
	
	

	printv(DEBUG, "convex mesh\n");
	//printv(DEBUG, b.getExtents(0));
	//printv(DEBUG, b.getExtents(1));
	//printv(DEBUG, b.getExtents(2));
	printv(DEBUG, "num polygons %i\n", convexMesh->getNbPolygons());
	printv(DEBUG, "num verts    %i\n", convexMesh->getNbVertices());
	printv(DEBUG, "num polygons %i\n", convexMesh->getNbPolygons());

	for(unsigned int c = 0; c < convexMesh->getNbVertices(); c++)
	{
		printv(DEBUG, "%16f%16f%16f\n",
			nverts[c].x,
			nverts[c].y,
			nverts[c].z);
	}

	//delete convexMesh;

	return g;
}
bool		THIS::query(
	physx::PxConvexMeshGeometry& g0,
	glm::mat4 v0, physx::PxConvexMeshGeometry& g1,
	glm::mat4 v1)
{
	assert(g0.isValid());
	assert(g1.isValid());

	physx::PxTransform t0(physx::PxMat44((float*)&v0[0][0]));
	physx::PxTransform t1(physx::PxMat44((float*)&v1[0][0]));

	t0 = t0.getInverse();
	t1 = t1.getInverse();

	return physx::PxGeometryQuery::overlap(g0, t0, g1, t1);
}
/*bool	neb::frustrum_overlap(neb::gfx::environ::base * const e0, neb::gfx::environ::base * const e1)
{
	return query(
			e0->proj_->px_geometry_,
			e0->view_->view(),
			e1->proj_->px_geometry_,
			e1->view_->view());
}*/
physx::PxDefaultCpuDispatcher*			THIS::create_default_cpu_dispatcher()
{
	return physx::PxDefaultCpuDispatcherCreate(1);
}


