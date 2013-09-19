// This code contains NVIDIA Confidential Information and is disclosed to you 
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and 
// any modifications thereto. Any use, reproduction, disclosure, or 
// distribution of this software and related documentation without an express 
// license agreement from NVIDIA Corporation is strictly prohibited.
// 
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2012 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

#include "PxPhysX.h"

#if PX_USE_CLOTH_API

#include "TestClothHelpers.h"

#include "geometry/PxSphereGeometry.h"
#include "cloth/PxCloth.h"
#include "cloth/PxClothReadData.h"
#include "PxToolkit.h"
#include "PsFastMemory.h"
#include "SampleArray.h"
#include "TestGeometryHelpers.h"

////////////////////////////////////////////////////////////////////////////////
bool 
Test::ClothHelpers::attachBorder(PxCloth& cloth, PxU32 borderFlag)
{
	PxClothReadData* readData = cloth.lockClothReadData();
    if (!readData)
        return false;

	// compute bounds in x and z
	PxReal minX = 1000000.0f;
    PxReal minZ = 1000000.0f;
    PxReal maxX = -1000000.0f;
    PxReal maxZ = -1000000.0f;

	PxU32 numParticles = cloth.getNbParticles();
	SampleArray<PxClothParticle> particles(numParticles);

    for(PxU32 i = 0; i < numParticles; i++)
	{
		const PxVec3& p = readData->particles[i].pos;
        if (p.x < minX) { minX = p.x; }
		if (p.z < minZ) { minZ = p.z; }
        if (p.x > maxX) { maxX = p.x; }
		if (p.z > maxZ) { maxZ = p.z; }

		particles[i].pos = p;
		particles[i].invWeight = readData->particles[i].invWeight;
    }	

	readData->unlock();

	if (borderFlag & BORDER_LEFT)
	{
		for (PxU32 i = 0; i < numParticles; i++)
			if (particles[i].pos.x <= minX)
				particles[i].invWeight = 0.0f;
	}
	if (borderFlag & BORDER_RIGHT)
	{
		for (PxU32 i = 0; i < numParticles; i++)
			if (particles[i].pos.x >= maxX)
				particles[i].invWeight = 0.0f;
	}
	if (borderFlag & BORDER_TOP)
	{
		for (PxU32 i = 0; i < numParticles; i++)
			if (particles[i].pos.z <= minZ)
				particles[i].invWeight = 0.0f;
	}
	if (borderFlag & BORDER_BOTTOM)
	{
		for (PxU32 i = 0; i < numParticles; i++)
			if (particles[i].pos.z >= maxZ)
				particles[i].invWeight = 0.0f;
	}

	cloth.setParticles(particles.begin(), particles.begin());

	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool Test::ClothHelpers::attachClothOverlapToShape(PxCloth& cloth, PxShape& shape,PxReal radius)
{
	PxU32 numVertices = cloth.getNbParticles();

	PxClothReadData* readData = cloth.lockClothReadData();
    if (!readData)
        return false;

	PxTransform pose = cloth.getGlobalPose();
	SampleArray<PxClothParticle> particles(numVertices);
    for (PxU32 i = 0; i < numVertices; i++)
	{
		particles[i].pos = readData->particles[i].pos;
		particles[i].invWeight = 1.0f;
	}

	readData->unlock();

    for (PxU32 i = 0; i < numVertices; i++)
	{
        // check if particle overlaps shape volume
        PxVec3 position = pose.transform(readData->particles[i].pos);
		
        PxSphereGeometry sg(radius);
        PxTransform globalPose(position, PxQuat::createIdentity());

        if (GeometryHelpers::testForOverlap(shape, sg, globalPose))
			particles[i].invWeight = 0.0f;
    }

    cloth.setParticles(particles.begin(), particles.begin());
	

    return true;
}

////////////////////////////////////////////////////////////////////////////////
PxClothFabric* Test::ClothHelpers::createFabric(PxPhysics &physics, PxCooking &cooking, const PxClothMeshDesc &desc, const PxVec3& gravityDir)
{
	// In this example, we cook the fabric on the fly through a memory stream
	// Note that we can also use a file stream and pre-cook the mesh to save the cooking time
	PxToolkit::MemoryOutputStream wb;
	PX_ASSERT(desc.isValid());

	// cook the fabric data into memory buffer (cooking time operation)
	if (!cooking.cookClothFabric(desc, gravityDir, wb))
		return 0;

	// read fabric from memory stream (runtime operation)
	PxToolkit::MemoryInputData rb(wb.getData(), wb.getSize());
	return physics.createClothFabric(rb);
}


////////////////////////////////////////////////////////////////////////////////
bool Test::ClothHelpers::createCollisionCapsule(
	const PxTransform &pose,
	const PxVec3 &center0, PxReal r0, const PxVec3 &center1, PxReal r1, 
	SampleArray<PxClothCollisionSphere> &spheres, SampleArray<PxU32> &indexPairs)
{
	PxTransform invPose = pose.getInverse();

	spheres.resize(2);

	spheres[0].pos = invPose.transform(center0);
	spheres[0].radius = r0;
	spheres[1].pos = invPose.transform(center1);
	spheres[1].radius = r1;

	indexPairs.resize(2);
	indexPairs[0] = 0;
	indexPairs[1] = 1;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool Test::ClothHelpers::createDefaultParticles(const PxClothMeshDesc& meshDesc, PxClothParticle* clothParticles, PxReal massPerParticle)
{
	const PxVec3* srcPoints = reinterpret_cast<const PxVec3*>(meshDesc.points.data);
    for (PxU32 i = 0; i < meshDesc.points.count; i++)
    {
        clothParticles[i].pos = srcPoints[i]; 
		clothParticles[i].invWeight = 1.0f / massPerParticle;
    }		
	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool Test::ClothHelpers::createMeshGrid(
    PxReal sizeU, PxReal sizeV, PxU32 numU, PxU32 numV, PxVec3 dirU, PxVec3 dirV,
	SampleArray<PxVec3>& vertexBuffer, SampleArray<PxU32>& primitiveBuffer, SampleArray<PxReal> &textureBuffer,
	PxClothMeshDesc &meshDesc)
{
	int numVertices = (numU + 1) * (numV + 1);
	int numTriangles = numU * numV * 2;

	vertexBuffer.resize(numVertices);
	primitiveBuffer.resize(numTriangles * 3);
	textureBuffer.resize(numVertices*2);

	// fill in point data
	PxReal offsetU = sizeU * 0.5f;
	PxReal offsetV = sizeV * 0.5f;

	PxU32 i,j;
	PxU32 uvcnt = 0;
	PxVec3 *p = vertexBuffer.begin();
	for (i = 0; i <= numV; i++) 
	{
		PxReal v = PxReal(i) / PxReal(numV);
		PxVec3 di = (v * sizeV - offsetV) * dirV;
		for (j = 0; j <= numU; j++) 
		{
			PxReal u = PxReal(j) / PxReal(numU);
			*p = (u * sizeU - offsetU) * dirU + di;
			p++;

			textureBuffer[uvcnt++] = u;
			textureBuffer[uvcnt++] = 1.0f - v;
		}
	}

    // fill in triangle index data
	PxU32 *id = primitiveBuffer.begin();
	for (i = 0; i < numV; i++) 
	{
		for (j = 0; j < numU; j++) 
		{
			PxU32 i0 = i * (numU+1) + j;
			PxU32 i1 = i0 + 1;
			PxU32 i2 = i0 + (numU+1);
			PxU32 i3 = i2 + 1;
			if ((j+i)%2) 
			{
				*id++ = i0; *id++ = i2; *id++ = i1;
				*id++ = i1; *id++ = i2; *id++ = i3;
			}
			else 
			{
				*id++ = i0; *id++ = i2; *id++ = i3;
				*id++ = i0; *id++ = i3; *id++ = i1;
			}
		}
	}

	// fill the physx cloth mesh descriptor 
	Test::ClothHelpers::fillClothMeshDesc( vertexBuffer, primitiveBuffer, meshDesc);

	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool Test::ClothHelpers::createMeshGrid(
    PxReal sizeX, PxReal sizeZ, PxU32 numX, PxU32 numZ,
	SampleArray<PxVec3>& vertexBuffer, SampleArray<PxU32>& primitiveBuffer, SampleArray<PxReal> &uvs,
	PxClothMeshDesc &meshDesc)
{
	return createMeshGrid(sizeX, sizeZ, numX, numZ, PxVec3(1,0,0), PxVec3(0,0,1), vertexBuffer, primitiveBuffer, uvs, meshDesc);
}

////////////////////////////////////////////////////////////////////////////////
// fill cloth mesh descriptor from vertices and primitives
void Test::ClothHelpers::fillClothMeshDesc(
	SampleArray<PxVec3> &vertexBuffer, 
	SampleArray<PxU32>& primitiveBuffer,
	PxClothMeshDesc &meshDesc)
{
	int numVertices = vertexBuffer.size();
	int numTriangles = primitiveBuffer.size() / 3;

	// convert vertex array to PxBoundedData (desc.points)
	meshDesc.points.data = vertexBuffer.begin();
	meshDesc.points.count = static_cast<PxU32>(numVertices);
	meshDesc.points.stride = sizeof(PxVec3);

	// convert face index array to PxBoundedData (desc.triangles)
	meshDesc.triangles.data = primitiveBuffer.begin();
	meshDesc.triangles.count = static_cast<PxU32>(numTriangles); 
	meshDesc.triangles.stride = sizeof(PxU32) * 3; // <- stride per triangle
}

#include "wavefront.h"

////////////////////////////////////////////////////////////////////////////////
// create cloth mesh from obj file (user must provide vertex, primitive, and optionally texture coord buffer)
bool Test::ClothHelpers::createMeshFromObj(
	const char* path, PxReal scale, const PxQuat* rot, const PxVec3* offset, 
	SampleArray<PxVec3>& vertexBuffer, SampleArray<PxU32>& primitiveBuffer, SampleArray<PxReal>* textureBuffer, 
	PxClothMeshDesc &meshDesc)
{
	bool textured = (textureBuffer != 0);

	WavefrontObj wo;
	wo.loadObj(path, textured);
	if (wo.mVertexCount <= 0)
		return false;

	PxVec3 myOffset(0.0f);
	PxQuat myRot = PxQuat::createIdentity();

	if (offset)
		myOffset = *offset;

	if (rot)
		myRot = *rot;

	int numVertices	= wo.mVertexCount;
	int numPrimitives = wo.mTriCount;	

	vertexBuffer.resize(numVertices);
	primitiveBuffer.resize(numPrimitives*3);

	PxVec3 *vSrc = (PxVec3*)wo.mVertices;
	PxVec3 *vDest = (PxVec3*)vertexBuffer.begin();
	for (int i = 0; i < numVertices; i++, vDest++, vSrc++) 
		*vDest = scale * myRot.rotate(*vSrc) + myOffset;

	physx::shdfnd::fastMemcpy((PxU32*)primitiveBuffer.begin()
                               , wo.mIndices, sizeof(PxU32)*numPrimitives*3);

	if (textured)
	{
		int numTexCoords = numVertices * 2;
		textureBuffer->resize(numTexCoords);
		physx::shdfnd::fastMemcpy((PxReal*)textureBuffer->begin(), wo.mTexCoords, 
                                   sizeof(PxReal) * numTexCoords);
	}

	// fill the physx cloth mesh descriptor 
	Test::ClothHelpers::fillClothMeshDesc( vertexBuffer, primitiveBuffer, meshDesc);

	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool Test::ClothHelpers::setMotionConstraints(PxCloth &cloth, PxReal radius)
{
	PxU32 numParticles = cloth.getNbParticles();

	PxClothReadData* readData = cloth.lockClothReadData();
    if (!readData)
        return false;

	const PxClothParticle* particles = readData->particles;

	SampleArray<PxClothParticleMotionConstraint> constraints(numParticles);

	for (PxU32 i = 0; i < numParticles; i++) {
		constraints[i].pos = particles[i].pos;
		constraints[i].radius = radius;
	}

	readData->unlock();

	cloth.setMotionConstraints(constraints.begin());

	return true;
}

namespace
{
	void setAllPhaseSolverType(PxCloth& cloth, PxClothPhaseSolverConfig::SolverType type)
	{
		PxU32 phaseTypeBegin = PxClothFabricPhaseType::eINVALID + 1;

		for ( PxU32 i = phaseTypeBegin; i < PxClothFabricPhaseType::eCOUNT; i++)
			if  ( (i == PxClothFabricPhaseType::eSTRETCHING)			||
				  (i == PxClothFabricPhaseType::eSTRETCHING_HORIZONTAL) ||
				  (i == PxClothFabricPhaseType::eSHEARING)				||
				  (i == PxClothFabricPhaseType::eBENDING) )
			{
				PxClothPhaseSolverConfig config = cloth.getPhaseSolverConfig(PxClothFabricPhaseType::Enum(i));
				config.solverType = type;
				cloth.setPhaseSolverConfig(PxClothFabricPhaseType::Enum(i), config);
			}
	}
}

////////////////////////////////////////////////////////////////////////////////
bool Test::ClothHelpers::setSolverType(PxCloth& cloth, PxU32 solverType)
{
	if (solverType == Test::ClothHelpers::eMIXED)
	{
		setAllPhaseSolverType(cloth, PxClothPhaseSolverConfig::eFAST);

		PxClothPhaseSolverConfig config = cloth.getPhaseSolverConfig(PxClothFabricPhaseType::eSTRETCHING);
		config.solverType = PxClothPhaseSolverConfig::eSTIFF;
		cloth.setPhaseSolverConfig(PxClothFabricPhaseType::eSTRETCHING, config);
	}

	else if (solverType == Test::ClothHelpers::eFAST)
	{
		setAllPhaseSolverType(cloth, PxClothPhaseSolverConfig::eFAST);
	}

	else if (solverType == Test::ClothHelpers::eSTIFF)
	{
		setAllPhaseSolverType(cloth, PxClothPhaseSolverConfig::eSTIFF);
	}

	else if (solverType == Test::ClothHelpers::eZEROSTRETCH)
	{
		setAllPhaseSolverType(cloth, PxClothPhaseSolverConfig::eFAST);

		PxClothPhaseSolverConfig config = cloth.getPhaseSolverConfig(PxClothFabricPhaseType::eZEROSTRETCH);
		config.solverType = PxClothPhaseSolverConfig::eZEROSTRETCH;
		config.stretchLimit = 1.1f;
		config.stretchStiffness = 1.0f;
		cloth.setPhaseSolverConfig(PxClothFabricPhaseType::eZEROSTRETCH, config);
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool Test::ClothHelpers::setStiffness(PxCloth& cloth, PxReal stiffness)
{
	PxClothPhaseSolverConfig solverConfig;

	PxU32 i = PxClothFabricPhaseType::eINVALID + 1;
	for ( ; i < PxClothFabricPhaseType::eCOUNT; i++)
	{
		PxClothFabricPhaseType::Enum phase = PxClothFabricPhaseType::Enum(i);
		solverConfig = cloth.getPhaseSolverConfig(phase);
		solverConfig.stiffness = stiffness;
		cloth.setPhaseSolverConfig(phase, solverConfig);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////////////
namespace
{
	static PxVec3 gVirtualParticleWeights[] = 
	{ 
		// center point
		PxVec3(1.0f / 3, 1.0f / 3, 1.0f / 3),

		// center of sub triangles
		PxVec3(2.0f / 3, 1.0f / 6, 1.0f / 6),
		PxVec3(1.0f / 6, 2.0f / 3, 1.0f / 6),
		PxVec3(1.0f / 6, 1.0f / 6, 2.0f / 3),

		// edge mid points
		PxVec3(1.0f / 2, 1.0f / 2, 0.0f),
		PxVec3(0.0f, 1.0f / 2, 1.0f / 2),
		PxVec3(1.0f / 2, 0.0f, 1.0f / 2),

		// further subdivision of mid points
		PxVec3(1.0f / 4, 3.0f / 4, 0.0f),
		PxVec3(3.0f / 4, 1.0f / 4, 0.0f),

		PxVec3(0.0f, 1.0f / 4, 3.0f / 4),
		PxVec3(0.0f, 3.0f / 4, 1.0f / 4),

		PxVec3(1.0f / 4, 0.0f, 3.0f / 4),
		PxVec3(3.0f / 4, 0.0f, 1.0f / 4)
	};
}

////////////////////////////////////////////////////////////////////////////////
bool Test::ClothHelpers::createVirtualParticles(PxCloth& cloth, PxClothMeshDesc& meshDesc, int numSamples)
{
	if(!numSamples)
		return false;

	PxU32 numFaces = meshDesc.triangles.count;
    PxU8* triangles = (PxU8*)meshDesc.triangles.data;

	PxU32 numParticles = numFaces * numSamples;
	SampleArray<PxU32> virtualParticleIndices;
	virtualParticleIndices.reserve(4 * numParticles);

    for (PxU32 i = 0; i < numFaces; i++)
    {
		for (int s = 0; s < numSamples; ++s)
		{
			PxU32 v0, v1, v2;

			if (meshDesc.flags & PxMeshFlag::e16_BIT_INDICES)
			{
				PxU16* triangle = (PxU16*)triangles;
				v0 = triangle[0];
				v1 = triangle[1];
				v2 = triangle[2];
			}
			else
			{
				PxU32* triangle = (PxU32*)triangles;
				v0 = triangle[0];
				v1 = triangle[1];
				v2 = triangle[2];
			}
			
			virtualParticleIndices.pushBack(v0);
			virtualParticleIndices.pushBack(v1);
			virtualParticleIndices.pushBack(v2);
			virtualParticleIndices.pushBack(s);
		}
        triangles += meshDesc.triangles.stride;
	}

    cloth.setVirtualParticles(numParticles, virtualParticleIndices.begin(), numSamples, gVirtualParticleWeights);

	return true;
}

////////////////////////////////////////////////////////////////////////////////
PxBounds3 Test::ClothHelpers::getAllWorldBounds(PxCloth& cloth)
{
	PxBounds3 totalBounds = cloth.getWorldBounds();

	PxU32 numSpheres = cloth.getNbCollisionSpheres();
	PxU32 numCapsules = cloth.getNbCollisionSpherePairs();
	PxU32 numPlanes = cloth.getNbCollisionPlanes();
	PxU32 numConvexes = cloth.getNbCollisionConvexes();
	SampleArray<PxClothCollisionSphere> spheres(numSpheres);
	SampleArray<PxU32> pairs(numCapsules*2);
	SampleArray<PxClothCollisionPlane> planes(numPlanes);
	SampleArray<PxU32> convexMasks(numConvexes);

	cloth.getCollisionData(spheres.begin(), pairs.begin(), planes.begin(), convexMasks.begin());

	PxTransform clothPose = cloth.getGlobalPose();

	for (PxU32 i = 0; i < numSpheres; i++)
	{
		PxVec3 p = clothPose.transform(spheres[i].pos);
		PxBounds3 bounds = PxBounds3::centerExtents(p, PxVec3(spheres[i].radius));
		totalBounds.minimum = totalBounds.minimum.minimum(bounds.minimum);
		totalBounds.maximum = totalBounds.maximum.maximum(bounds.maximum);
	}

	return totalBounds;
}

////////////////////////////////////////////////////////////////////////////////
bool Test::ClothHelpers::getParticlePositions(PxCloth &cloth, SampleArray<PxVec3> &positions)
{
	PxClothReadData* readData = cloth.lockClothReadData();
    if (!readData)
        return false;

	const PxClothParticle* particles = readData->particles;
	if (!particles)
		return false;

	PxU32 nbParticles = cloth.getNbParticles();
	positions.resize(nbParticles);
	for (PxU32 i = 0; i < nbParticles; i++) 
		positions[i] = particles[i].pos;

	readData->unlock();

	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool Test::ClothHelpers::setParticlePositions(PxCloth &cloth, const SampleArray<PxVec3> &positions, bool useConstrainedOnly, bool useCurrentOnly)
{
	PxU32 nbParticles = cloth.getNbParticles();
	if (nbParticles != positions.size())
		return false;

	PxClothReadData* readData = cloth.lockClothReadData();
    if (!readData)
        return false;

	const PxClothParticle* particles = readData->particles;
	if (!particles)
		return false;

	SampleArray<PxClothParticle> newParticles(nbParticles);
	for (PxU32 i = 0; i < nbParticles; i++) 
	{		
		bool constrained = ( particles[i].invWeight == 0.0f);

		if (!useConstrainedOnly || constrained)
			newParticles[i].pos = positions[i];
		else
			newParticles[i].pos = particles[i].pos;
		
		newParticles[i].invWeight = particles[i].invWeight;
	}

	readData->unlock();

	if (useCurrentOnly)
		cloth.setParticles(newParticles.begin(), NULL);
	else
		cloth.setParticles(newParticles.begin(), newParticles.begin());


	return true;
}

#endif // PX_USE_CLOTH_API
