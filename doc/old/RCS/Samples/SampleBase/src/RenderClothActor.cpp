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

#include "RenderClothActor.h"
#include "RenderCapsuleActor.h"
#include "RenderMaterial.h"
#include "RendererMeshShape.h"
#include "RendererClothShape.h"
#include "RendererCapsuleShape.h"
#include "PsFastMemory.h"
#include "PhysXSample.h"
#include "foundation/PxBounds3.h"

#include "cloth/PxClothReadData.h"
#include "cloth/PxCloth.h"

#include "extensions/PxSmoothNormals.h"

using namespace SampleRenderer;

/// These functions can probably move to PxToolkit or PxExtension
namespace 
{

// create uv from planar projection onto xz plane (where most cloth grids are created)
void createUVWithPlanarProjection(PxReal* uvs, PxU32 numVerts, const PxVec3* verts)
{
	PxBounds3 bounds = PxBounds3::empty();

    for(PxU32 i = 0; i < numVerts; i++)
		bounds.include(verts[i]);

	PxVec3 dim = bounds.getDimensions();
	PxReal minVal = PX_MAX_REAL;
	PxU32 minAxis = 0;

	// find smallest axis
	if (dim.x < minVal) { minVal = dim.x; minAxis = 0; }
	if (dim.y < minVal) { minVal = dim.y; minAxis = 1; }
	if (dim.z < minVal) { minVal = dim.z; minAxis = 2; }

	PxU32 uAxis = 0, vAxis = 1;
	switch (minAxis)
	{
		case 0: uAxis = 1; vAxis = 2; break; 
		case 1: uAxis = 0; vAxis = 2; break; 
		case 2: uAxis = 0; vAxis = 1; break; 
	}
	
	const float sizeU = dim[uAxis];
	const float sizeV = dim[vAxis];
	const float minU = bounds.minimum[uAxis];
	const float minV = bounds.minimum[vAxis];

	for (PxU32 i = 0; i < numVerts; ++i)
    {
        uvs[i*2+0] = (verts[i][uAxis] - minU) / sizeU;
        uvs[i*2+1] = 1.f - (verts[i][vAxis]-minV) / sizeV;
    }
    
}

// extract current cloth particle position from PxCloth
// verts is supposed to have been pre-allocated to be at least size of particle array
bool getVertsFromCloth(PxVec3* verts, const PxCloth& cloth)
{
	PxClothReadData* readData = cloth.lockClothReadData();
    if (!readData)
        return false;

    // copy vertex positions
    PxU32 numVerts = cloth.getNbParticles();
	for (PxU32 i = 0; i < numVerts; ++i)
		verts[i] = readData->particles[i].pos;

	readData->unlock();

    return true;
}

// copy face structure from PxClothMeshDesc
PxU16* createFacesFromMeshDesc(const PxClothMeshDesc& desc)
{
    PxU32 numFaces = desc.triangles.count;

    PxU16* faces = (PxU16*)SAMPLE_ALLOC(sizeof(PxU16)*numFaces * 3);

    PxU8* triangles = (PxU8*)desc.triangles.data;

    for (PxU32 i = 0; i < numFaces; i++)
    {
        if (desc.flags & PxMeshFlag::e16_BIT_INDICES)
        {
            PxU16* triangle = (PxU16*)triangles;
            faces[ i * 3 + 0] = triangle[ 0 ];
            faces[ i * 3 + 1] = triangle[ 1 ];
            faces[ i * 3 + 2] = triangle[ 2 ];
        } 
        else
        {
            PxU32* triangle = (PxU32*)triangles;
            faces[ i * 3 + 0] = triangle[ 0 ];
            faces[ i * 3 + 1] = triangle[ 1 ];
            faces[ i * 3 + 2] = triangle[ 2 ];
        }
        triangles += desc.triangles.stride;
    }
    
    return faces;
}

} // anonymous namespace

RenderClothActor::RenderClothActor(SampleRenderer::Renderer& renderer, const PxCloth& cloth, const PxClothMeshDesc &desc, const PxReal* uv, const PxVec3 &rendererColor, const PxReal capsuleScale)
    : mRenderer(renderer)
	, mCloth(cloth)
	, mFaces(NULL)
	, mPlanes(0), mConvexMasks(0)
	, mNumPlanes(0), mNumConvexes(0)
	, mUV(NULL)
	, mRendererColor(rendererColor)
	, mCapsuleScale(capsuleScale)
    , mClothRenderShape(NULL)
{
	PxU32 numCollisionSpheres = mCloth.getNbCollisionSpheres();
	PxU32 numPairs = mCloth.getNbCollisionSpherePairs();

	mSpheres = (PxClothCollisionSphere*)SAMPLE_ALLOC(sizeof(PxClothCollisionSphere) * numCollisionSpheres);
	mIndexPairs = (PxU32*)SAMPLE_ALLOC(sizeof(PxU32) * numPairs * 2);

	int numVerts = desc.points.count;

    mNumFaces = desc.triangles.count;
    mFaces = createFacesFromMeshDesc(desc);

	const PxVec3* verts = reinterpret_cast<const PxVec3*>(desc.points.data);

    mUV = (PxReal*)SAMPLE_ALLOC(sizeof(PxReal)*numVerts*2);		
	if (uv)
		physx::shdfnd::fastMemcpy( mUV, uv, sizeof(PxReal) * 2 * numVerts);
	else
        createUVWithPlanarProjection(mUV, numVerts, verts);

	// create sphere actors (we reuse the RenderCapsuleActor type)
	for ( PxU32 i = 0; i < numCollisionSpheres; i++)
	{
		RenderCapsuleActor* capsule = SAMPLE_NEW(RenderCapsuleActor)(renderer, 1.0f, 0.0f);
		mSphereActors.pushBack(capsule);
	}

	// create capsule actors
	for ( PxU32 i = 0; i < numPairs; i++)
	{
		RenderCapsuleActor* capsule = SAMPLE_NEW(RenderCapsuleActor)(renderer, 1.0f, 1.0f);
		mCapsuleActors.pushBack(capsule);
	}

	updateRenderShape();
}

RenderClothActor::~RenderClothActor() 
{
	SAMPLE_FREE( mUV );
    SAMPLE_FREE( mFaces );
	SAMPLE_FREE( mSpheres );
	SAMPLE_FREE( mIndexPairs );
	SAMPLE_FREE( mPlanes );
	SAMPLE_FREE( mConvexMasks );
}

void RenderClothActor::updateRenderShape()
{
    int numVerts = mCloth.getNbParticles();

    PX_ASSERT(numVerts > 0);

    std::vector<PxVec3> verts(numVerts);

	bool result = getVertsFromCloth(&verts[0], mCloth);

	PX_ASSERT(result == true);

    // update render normal
    std::vector<PxVec3> normals(numVerts);
    PxBuildSmoothNormals(mNumFaces, numVerts, &verts[0], NULL, mFaces, &normals[0], false);

    if(!mClothRenderShape)
    {
        mClothRenderShape = new RendererClothShape(
            mRenderer,
            &verts[0],
            numVerts,
            &normals[0],
            mUV,
            &mFaces[0],
            mNumFaces, false);

        setRenderShape(mClothRenderShape);
    }
    else
    {
        mClothRenderShape->update(&verts[0], numVerts, &normals[0]);
    }

	setTransform(mCloth.getGlobalPose());
}

void RenderClothActor::update(float deltaTime)
{
	updateRenderShape();

	// update collision shapes
	PxU32 numCollisionSpheres = mCloth.getNbCollisionSpheres();
	PxU32 numPairs = mCloth.getNbCollisionSpherePairs();
	PxU32 numPlanes = mCloth.getNbCollisionPlanes();
	PxU32 numConvexes = mCloth.getNbCollisionConvexes();

	if (numCollisionSpheres == 0 && numConvexes == 0)
		return;

	if(numPlanes != mNumPlanes)
		mPlanes = (PxClothCollisionPlane*)SAMPLE_ALLOC(sizeof(PxClothCollisionPlane) * (mNumPlanes = numPlanes));

	if(numConvexes != mNumConvexes)
		mConvexMasks = (PxU32*)SAMPLE_ALLOC(sizeof(PxU32) * (mNumConvexes = numConvexes));

	mCloth.getCollisionData(mSpheres, mIndexPairs, mPlanes, mConvexMasks);

	PxTransform clothPose = mCloth.getGlobalPose();

	// update all spheres
	for (PxU32 i=0; i < mSphereActors.size(); ++i)
	{
		float r = mSpheres[i].radius*mCapsuleScale;

		mSphereActors[i]->setRendering(true);
		mSphereActors[i]->setTransform(PxTransform(clothPose.transform(mSpheres[i].pos)));
		mSphereActors[i]->setMeshScale(PxMeshScale(PxVec3(r, r, r), PxQuat::createIdentity()));
	}
	
	// capsule needs to be flipped to match PxTransformFromSegment
	PxTransform flip(PxVec3(0.0f), PxQuat(-PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));

	// update all capsules
	for (PxU32 i=0; i < mCapsuleActors.size(); ++i)
	{
		PxU32 i0 = mIndexPairs[i*2];
		PxU32 i1 = mIndexPairs[i*2+1];

		PxClothCollisionSphere& sphere0 = mSpheres[i0];
		PxClothCollisionSphere& sphere1 = mSpheres[i1];
		
		// disable individual rendering for spheres belonging to a capsule
		mSphereActors[i0]->setRendering(false);
		mSphereActors[i1]->setRendering(false);

		PxVec3 p0 = clothPose.transform(sphere0.pos);
		PxVec3 p1 = clothPose.transform(sphere1.pos);

		mCapsuleActors[i]->setDimensions((p1-p0).magnitude()*0.5f, mCapsuleScale*sphere0.radius, mCapsuleScale*sphere1.radius);
		mCapsuleActors[i]->setTransform(PxTransformFromSegment(p0, p1)*flip);		
	}	
}

#endif // PX_USE_CLOTH_API

