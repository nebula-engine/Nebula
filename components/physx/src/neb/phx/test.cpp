
#include <PxPhysicsAPI.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <neb/gfx/util/io.hpp>
#include <neb/gfx/environ/base.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/test.hpp>

physx::PxConvexMeshGeometry*	neb::frustrum_geometry(glm::mat4 proj) {
	
	auto app = neb::phx::app::base::global();


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

	std::cout << "proj" << std::endl << proj << std::endl;
	std::cout << "inv" << std::endl << inv << std::endl;

	std::cout << "verts" << std::endl;
	for(int c = 0; c < 8; c++)
	{
		gverts[c] = inv * gverts[c];
		gverts[c] = gverts[c] / gverts[c].w;
		verts[c] = physx::PxVec3(
				gverts[c].x,
				gverts[c].y,
				gverts[c].z);

		std::cout << gverts[c] << std::endl;
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
	if(!app->px_cooking_->cookConvexMesh(convexDesc, buf))
		abort();

	physx::PxDefaultMemoryInputData input(buf.getData(), buf.getSize());

	physx::PxConvexMesh* convexMesh = app->px_physics_->createConvexMesh(input);

	physx::PxConvexMeshGeometry* g = new physx::PxConvexMeshGeometry(convexMesh);

	assert(g->isValid());

	auto b = convexMesh->getLocalBounds();

	const physx::PxVec3* nverts = convexMesh->getVertices();
	
	

	std::cout << "convex mesh" << std::endl;
	std::cout << b.getExtents(0) << std::endl;
	std::cout << b.getExtents(1) << std::endl;
	std::cout << b.getExtents(2) << std::endl;
	std::cout << "num polygons " << convexMesh->getNbPolygons() << std::endl;
	std::cout << "num verts    " << convexMesh->getNbVertices() << std::endl;
	//d::cout << "num polygons " << convexMesh->getNbPolygons() << std::endl;

	for(unsigned int c = 0; c < convexMesh->getNbVertices(); c++)
	{
		std::cout
			<< std::setw(16) << nverts[c].x
			<< std::setw(16) << nverts[c].y
			<< std::setw(16) << nverts[c].z
			<< std::endl;
	}

	//delete convexMesh;

	return g;
}

bool		neb::query(physx::PxConvexMeshGeometry& g0, glm::mat4 v0, physx::PxConvexMeshGeometry& g1, glm::mat4 v1)
{
	assert(g0.isValid());
	assert(g1.isValid());

	physx::PxTransform t0(physx::PxMat44((float*)&v0[0][0]));
	physx::PxTransform t1(physx::PxMat44((float*)&v1[0][0]));

	t0 = t0.getInverse();
	t1 = t1.getInverse();

/*	std::cout << "t0" << std::endl;
	std::cout
		<< std::setw(16) << t0.p.x
		<< std::setw(16) << t0.p.y
		<< std::setw(16) << t0.p.z
		<< std::endl;
	std::cout
		<< std::setw(16) << t0.q.x
		<< std::setw(16) << t0.q.y
		<< std::setw(16) << t0.q.z
		<< std::setw(16) << t0.q.w
		<< std::endl;

	std::cout << "t1" << std::endl;
	std::cout
		<< std::setw(16) << t1.p.x
		<< std::setw(16) << t1.p.y
		<< std::setw(16) << t1.p.z
		<< std::endl;
	std::cout
		<< std::setw(16) << t1.q.x
		<< std::setw(16) << t1.q.y
		<< std::setw(16) << t1.q.z
		<< std::setw(16) << t1.q.w
		<< std::endl;
*/

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


