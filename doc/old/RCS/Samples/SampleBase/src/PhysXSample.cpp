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

#include "PxPhysX.h"
#include "SamplePreprocessor.h"
#include "PhysXSampleApplication.h"
#include "PhysXSample.h"
#include "SampleCommandLine.h"

#include "PsFile.h"

#include "PxToolkit.h"
#include "common/PxCoreUtilities.h"

#include "RenderBoxActor.h"
#include "RenderSphereActor.h"
#include "RenderCapsuleActor.h"
#include "RenderMeshActor.h"
#include "RenderGridActor.h"
#include "RenderMaterial.h"
#include "RenderTexture.h"
#include "RenderPhysX3Debug.h"
#include "RenderClothActor.h"
#include "ParticleSystem.h"
#include "physxprofilesdk/PxProfileZoneManager.h"
#ifdef PX_PS3
#include "extensions/ps3/PxPS3Extension.h"
#include "extensions/ps3/PxDefaultSpuDispatcher.h"
#endif

#include <SamplePlatform.h>
#include "SampleBaseInputEventIds.h"
#include <SampleUserInputIds.h>
#include "SampleUserInputDefines.h"
#include <SampleInputAsset.h>
#include "SampleInputMappingAsset.h"

#include <algorithm>
#include <ctype.h>

#include "cloth/PxClothReadData.h"
#include "TestClothHelpers.h"

#include "Picking.h"
#include "TestGroup.h"

using namespace SampleFramework;
using namespace SampleRenderer;

#define	PVD_HOST	"127.0.0.1"

static bool gRecook	= false;
PxDefaultAllocator gDefaultAllocatorCallback;

enum MaterialID
{
	MATERIAL_CLOTH	 = 444,
#ifdef RENDERER_TABLET
	MATERIAL_CONTROLS,
	MATERIAL_BUTTONS,
#endif
};
#ifdef RENDERER_TABLET
#include "SampleMaterialAsset.h"
static const char* controlMaterialPath = "materials/tablet_sticks.xml";
static const char* buttonMaterialPath = "materials/tablet_buttons.xml";
#endif

///////////////////////////////////////////////////////////////////////////////

PX_FORCE_INLINE PxSimulationFilterShader getSampleFilterShader()
{
	return PxDefaultSimulationFilterShader;
}

///////////////////////////////////////////////////////////////////////////////

PX_FORCE_INLINE void SetupDefaultRigidDynamic(PxRigidDynamic& body, bool kinematic=false)
{
	body.setActorFlag(PxActorFlag::eVISUALIZATION, true);
	body.setAngularDamping(0.5f);
	body.setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, kinematic);
}

PX_FORCE_INLINE void link(RenderBaseActor* renderActor, PxShape* shape)
{
	shape->userData = renderActor;
	renderActor->setPhysicsShape(shape);
}

SampleDirManager& PhysXSample::getSampleOutputDirManager()
{
	static SampleDirManager gSampleOutputDirManager(SAMPLE_OUTPUT_DIR, false);
	return gSampleOutputDirManager;
}

PxToolkit::BasicRandom& getSampleRandom()
{
	static PxToolkit::BasicRandom gRandom(42);
	return gRandom;
}

PxErrorCallback& getSampleErrorCallback()
{
	static PxDefaultErrorCallback gDefaultErrorCallback;
	return gDefaultErrorCallback;
}

// PT: TODO: move this function to a better place
static const char* ChangeExtension(const char* filename, const char* new_ext)
{
	// WARNING: old code, not very safe
	static char NewName[1024];
	const PxU32 l = (PxU32)strlen(filename);
	for(PxU32 i=0;i<l;i++)
	{
		NewName[i] = tolower(filename[i]);
	}
	NewName[l] = 0;
	char* p = strrchr(NewName, '.');
	*++p='\0';
	strcat(NewName, new_ext);
	return(NewName);
}

// sschirm: same here: would be good to have a place for platform independent path manipulation
// shared for all apps
const char* getFilenameFromPath(const char* filePath, char* buffer)
{
	const char* ptr = strrchr(filePath, '/');
	if (!ptr)
		ptr = strrchr(filePath, '\\');
	
	if (ptr)
	{
		strcpy(buffer, ptr + 1);
	}
	else 
	{
		strcpy(buffer, filePath);
	}
	return buffer;
}

const char* PhysXSample::getSampleOutputFilePath(const char* inFilePath, const char* outExtension)
{
	static char sBuffer[1024];
	char tmpBuffer[1024];
	
	const char* inFilename = getFilenameFromPath(inFilePath, sBuffer);
	sprintf(tmpBuffer, "cached/%s%s", inFilename, outExtension);
	return getSampleOutputDirManager().getFilePath(tmpBuffer, sBuffer, false);	
}

static void GenerateCirclePts(unsigned int nb, PxVec3* pts, float scale, float z)
{
	for(unsigned int i=0;i<nb;i++)
	{
		const PxF32 angle = 6.28f*PxF32(i)/PxF32(nb);
		pts[i].x = cosf(angle)*scale;
		pts[i].y = z;
		pts[i].z = sinf(angle)*scale;
	}
}

static PxConvexMesh* GenerateConvex(PxPhysics& sdk, PxCooking& cooking, PxU32 nbVerts, const PxVec3* verts, bool recenterVerts=false)
{
	PxVec3Alloc* tmp = NULL;
	if(recenterVerts)
	{
		PxVec3 center(0);
		for(PxU32 i=0;i<nbVerts;i++)
			center += verts[i];
		center /= PxReal(nbVerts);

		tmp = SAMPLE_NEW(PxVec3Alloc)[nbVerts];
		PxVec3* recentered = tmp;
		for(PxU32 i=0;i<nbVerts;i++)
			recentered[i] = verts[i] - center;
	}

	PxConvexMesh* convexMesh = PxToolkit::createConvexMesh(sdk, cooking, recenterVerts ? tmp : verts, nbVerts, PxConvexFlag::eCOMPUTE_CONVEX);

	DELETEARRAY(tmp);

	return convexMesh;
}

static PxConvexMesh* GenerateConvex(PxPhysics& sdk, PxCooking& cooking, float scale, bool large=false, bool randomize=true)
{
	const PxI32 minNb = large ? 16 : 3;
	const PxI32 maxNb = large ? 32 : 8;
	const int nbInsideCirclePts = !randomize ? 3 : getSampleRandom().rand(minNb, maxNb);
	const int nbOutsideCirclePts = !randomize ? 8 : getSampleRandom().rand(minNb, maxNb);
	const int nbVerts = nbInsideCirclePts + nbOutsideCirclePts;
	
	// Generate random vertices
	PxVec3Alloc* verts = SAMPLE_NEW(PxVec3Alloc)[nbVerts];
	
	// Two methods
	if(randomize && getSampleRandom().rand(0, 100) > 50)
	{
		for(int i=0;i<nbVerts;i++)
		{
			verts[i].x = scale * getSampleRandom().rand(-2.5f, 2.5f);
			verts[i].y = scale * getSampleRandom().rand(-2.5f, 2.5f);
			verts[i].z = scale * getSampleRandom().rand(-2.5f, 2.5f);
		}
	}
	else
	{
		GenerateCirclePts(nbInsideCirclePts, verts, scale, 0.0f);
		GenerateCirclePts(nbOutsideCirclePts, verts+nbInsideCirclePts, scale*3.0f, 10.0f*scale);
	}

	PxConvexMesh* convexMesh = GenerateConvex(sdk, cooking, nbVerts, verts);

	DELETEARRAY(verts);
	return convexMesh;
}

#if 0

static PxConvexMesh* GenerateConvex(PxPhysics& sdk, PxCooking& cooking, int nbInsideCirclePts, int nbOutsideCirclePts, float scale0, float scale1, float z)
{
	const int nbVerts = nbInsideCirclePts + nbOutsideCirclePts;
	
	// Generate random vertices
	PxVec3Alloc* verts = SAMPLE_NEW(PxVec3Alloc)[nbVerts];
	
	GenerateCirclePts(nbInsideCirclePts, verts, scale0, 0.0f);
	GenerateCirclePts(nbOutsideCirclePts, verts+nbInsideCirclePts, scale1, z);

	PxConvexMesh* convexMesh = GenerateConvex(sdk, cooking, nbVerts, verts);

	DELETEARRAY(verts);
	return convexMesh;
}

#endif

static PxRigidDynamic* GenerateCompound(PxPhysics& sdk, PxScene* scene, PxMaterial* defaultMat, const PxVec3& pos, const PxQuat& rot, const std::vector<PxTransform>& poses, const std::vector<const PxGeometry*>& geometries, bool kinematic=false, PxReal density = 1.0f)
{
	PxRigidDynamic* actor = sdk.createRigidDynamic(PxTransform(pos, rot));
	SetupDefaultRigidDynamic(*actor);

	PX_ASSERT(poses.size() == geometries.size());
	for(PxU32 i=0;i<poses.size();i++)
	{
		const PxTransform& currentPose = poses[i];
		const PxGeometry* currentGeom = geometries[i];

		PxShape* shape = actor->createShape(*currentGeom, *defaultMat, currentPose);
		shape->setFlag(PxShapeFlag::eVISUALIZATION, true);
		PX_ASSERT(shape);
	}

	if(actor)
	{
		PxRigidBodyExt::updateMassAndInertia(*actor, density);
		scene->addActor(*actor);
	}
	return actor;
}

///////////////////////////////////////////////////////////////////////////////

RenderMeshActor* PhysXSample::createRenderMeshFromRawMesh(const RAWMesh& data, PxShape* shape)
{
	// Create render mesh from raw mesh
	const PxU32 nbTris = data.mNbFaces;
	const PxU32* src = data.mIndices;

	PxU16* indices = (PxU16*)SAMPLE_ALLOC(sizeof(PxU16)*nbTris*3);
	for(PxU32 i=0;i<nbTris;i++)
	{
			indices[i*3+0] = src[i*3+0];
			indices[i*3+1] = src[i*3+2];
			indices[i*3+2] = src[i*3+1];
	}

	RenderMeshActor* meshActor = SAMPLE_NEW(RenderMeshActor)(*getRenderer(), data.mVerts, data.mNbVerts, data.mVertexNormals, data.mUVs, indices, nbTris);
	SAMPLE_FREE(indices);

	if(data.mMaterialID!=0xffffffff)
	{
		size_t nbMaterials = mRenderMaterials.size();
		for(PxU32 i=0;i<nbMaterials;i++)
		{
			if(mRenderMaterials[i]->mID==data.mMaterialID)
			{
				meshActor->setRenderMaterial(mRenderMaterials[i]);
				break;
			}
		}
	}

	meshActor->setTransform(data.mTransform);
	if(data.mName)
		strcpy(meshActor->mName, data.mName);

	mRenderActors.push_back(meshActor);
	return meshActor;
}

///////////////////////////////////////////////////////////////////////////////

RenderTexture* PhysXSample::createRenderTextureFromRawTexture(const RAWTexture& data)
{
	RenderTexture* texture;

	if(!data.mPixels)
	{
		// PT: temporary hack to make this work on consoles... hijack filename and try to load BMPs first...
		bool status = false;
		if(1)
		{
			char buffer[4096];
			strcpy(buffer, data.mName);
			const char* bmpFilename = ChangeExtension(buffer, "bmp");

			PxToolkit::BmpLoader loader;
			status = loader.loadBmp(getSampleMediaFilename(bmpFilename));
			if(status)
			{
				RendererColorAlloc* tmp = SAMPLE_NEW(RendererColorAlloc)[loader.mWidth * loader.mHeight];
				const PxU8* bmpData = loader.mRGB;
				RendererColor* dst = tmp + loader.mWidth * loader.mHeight;
				for(PxI32 y=0;y<loader.mHeight;y++)
				{
					dst -= loader.mWidth;
					for(PxI32 x=0;x<loader.mWidth;x++)
					{
						dst[x].r = *bmpData++;
						dst[x].g = *bmpData++;
						dst[x].b = *bmpData++;
						dst[x].a = loader.mHasAlpha ? *bmpData++ : 255;
					}
				}
				texture = SAMPLE_NEW(RenderTexture)(*getRenderer(), data.mID, loader.mWidth, loader.mHeight, tmp);
				DELETEARRAY(tmp);
			}
		}
		
		if(!status)
		{
			// PT: the pixel data is not included in the RAW file so we use the asset manager to load the texture
			SampleAsset* t = getAsset(getSampleMediaFilename(data.mName), SampleAsset::ASSET_TEXTURE);
			PX_ASSERT(t->getType()==SampleAsset::ASSET_TEXTURE);
			mManagedAssets.push_back(t);

			SampleTextureAsset* textureAsset = static_cast<SampleTextureAsset*>(t);
			texture = SAMPLE_NEW(RenderTexture)(*getRenderer(), data.mID, textureAsset->getTexture());
		}
	}
	else
	{
		// PT: the pixel data is directly included in the RAW file
		texture = SAMPLE_NEW(RenderTexture)(*getRenderer(), data.mID, data.mWidth, data.mHeight, data.mPixels);
	}
	if(data.mName)
		strcpy(texture->mName, data.mName);
	mRenderTextures.push_back(texture);
	return texture;
}

///////////////////////////////////////////////////////////////////////////////

void PhysXSample::newMaterial(const RAWMaterial& data)
{
	RenderTexture* diffuse = NULL;
	if(data.mDiffuseID!=0xffffffff)
	{
		size_t nbTextures = mRenderTextures.size();
		for(PxU32 i=0;i<nbTextures;i++)
		{
			if(mRenderTextures[i]->mID==data.mDiffuseID)
			{
				diffuse = mRenderTextures[i];
				break;
			}
		}
	}

	RenderMaterial* newRM = SAMPLE_NEW(RenderMaterial)(*getRenderer(), data.mDiffuseColor, data.mOpacity, data.mDoubleSided, data.mID, diffuse);
//	strcpy(newRM->mName, data.mName);
	mRenderMaterials.push_back(newRM);
}

void PhysXSample::newMesh(const RAWMesh& data)
{
	// PT: the mesh name should capture the scale value as well, to make sure different scales give birth to different cooked files
	const PxU32 scaleTag = PX_IR(mScale);

	PX_ASSERT(mFilename);
	char extension[256];
	sprintf(extension, "_%d_%x.cooked", mMeshTag, scaleTag);
	
	const char* filePathCooked = getSampleOutputFilePath(mFilename, extension);
	PX_ASSERT(NULL != filePathCooked);

	bool ok = false;
	if(!gRecook)
	{
		FILE* fp = NULL;
		physx::fopen_s(&fp, filePathCooked, "rb");
		if(fp)
		{
			fclose(fp);
			ok = true;
		}
	}

	if(!ok)
	{
		PxTriangleMeshDesc meshDesc;
		meshDesc.points.count		= data.mNbVerts;
		meshDesc.triangles.count	= data.mNbFaces;
		meshDesc.points.stride		= 4*3;
		meshDesc.triangles.stride	= 4*3;
		meshDesc.points.data		= data.mVerts;
		meshDesc.triangles.data		= data.mIndices;

		//
		printf("Cooking object... %s", filePathCooked);
		PxToolkit::FileOutputStream stream(filePathCooked);
		ok = mCooking->cookTriangleMesh(meshDesc, stream);
		printf(" - Done\n");
	}

	if(ok)
	{
		PxToolkit::FileInputData stream(filePathCooked);
		PxTriangleMesh* triangleMesh = mPhysics->createTriangleMesh(stream);
		if(triangleMesh)
		{
			PxTriangleMeshGeometry triGeom;
			triGeom.triangleMesh = triangleMesh;
			PxRigidStatic* actor = mPhysics->createRigidStatic(data.mTransform);
			PxShape* shape = actor->createShape(triGeom, *mMaterial);
			mScene->addActor(*actor);
			mPhysicsActors.push_back(actor);

			if(0)
			{
				// Create render mesh from PhysX mesh
				PxU32 nbVerts = triangleMesh->getNbVertices();
				const PxVec3* verts = triangleMesh->getVertices();
				PxU32 nbTris = triangleMesh->getNbTriangles();
				const void* tris = triangleMesh->getTriangles();
				bool s = triangleMesh->has16BitTriangleIndices();
				PX_ASSERT(s);

				const PxU16* src = (const PxU16*)tris;
				PxU16* indices = (PxU16*)SAMPLE_ALLOC(sizeof(PxU16)*nbTris*3);
				for(PxU32 i=0;i<nbTris;i++)
				{
					indices[i*3+0] = src[i*3+0];
					indices[i*3+1] = src[i*3+2];
					indices[i*3+2] = src[i*3+1];
				}

				RenderMeshActor* meshActor = SAMPLE_NEW(RenderMeshActor)(*getRenderer(), verts, nbVerts, verts, NULL, indices, nbTris);
				if(data.mName)
					strcpy(meshActor->mName, data.mName);
				PxShape* shape; 
				actor->getShapes(&shape, 1);
				link(meshActor, shape);
				mRenderActors.push_back(meshActor);
				SAMPLE_FREE(indices);
			}
			else
			{
				PxShape* shape; 
				actor->getShapes(&shape, 1);
				RenderMeshActor* meshActor = createRenderMeshFromRawMesh(data, shape);
				link(meshActor, shape);
			}

			mMeshTag++;
		}
	}
}

void PhysXSample::newShape(const RAWShape&)
{
}

void PhysXSample::newHelper(const RAWHelper&)
{
}

void PhysXSample::newTexture(const RAWTexture& data)
{
	createRenderTextureFromRawTexture(data);
}

///////////////////////////////////////////////////////////////////////////////

void PhysXSample::togglePvdConnection()
{
	if(!mPhysics->getPvdConnectionManager()) return;
	if (mPhysics->getPvdConnectionManager()->isConnected())
		mPhysics->getPvdConnectionManager()->disconnect();
	else
		createPvdConnection();
}

void PhysXSample::createPvdConnection()
{
	if(mPhysics->getPvdConnectionManager() == NULL)
		return;


	//The connection flags state overall what data is to be sent to PVD.  Currently
	//the Debug connection flag requires support from the implementation (don't send
	//the data when debug isn't set) but the other two flags, profile and memory
	//are taken care of by the PVD SDK.

	//Use these flags for a clean profile trace with minimal overhead
	PxVisualDebuggerConnectionFlags theConnectionFlags( PxVisualDebuggerExt::getAllConnectionFlags() );
	if (!mUseFullPvdConnection)
		theConnectionFlags = PxVisualDebuggerConnectionFlag::Profile;

	//Create a pvd connection that writes data straight to the filesystem.  This is
	//the fastest connection on windows for various reasons.  First, the transport is quite fast as
	//pvd writes data in blocks and filesystems work well with that abstraction.
	//Second, you don't have the PVD application parsing data and using CPU and memory bandwidth
	//while your application is running.
	//PxVisualDebuggerExt::createConnection(mPhysics->getPvdConnectionManager(), "c:\\temp.pxd2", theConnectionFlags);
	
	//The normal way to connect to pvd.  PVD needs to be running at the time this function is called.
	//We don't worry about the return value because we are already registered as a listener for connections
	//and thus our onPvdConnected call will take care of setting up our basic connection state.
	PVD::PvdConnection* theConnection = PxVisualDebuggerExt::createConnection(mPhysics->getPvdConnectionManager(), PVD_HOST, 5425, 10, theConnectionFlags );
	if (theConnection)
		theConnection->release();
}

void PhysXSample::onPvdConnected(PVD::PvdConnection& )
{
	//setup joint visualization.  This gets piped to pvd.
	mPhysics->getVisualDebugger()->setVisualizeConstraints(true);
	mPhysics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlags::eTRANSMIT_CONTACTS, true);
}

void PhysXSample::onPvdDisconnected(PVD::PvdConnection& )
{
}

void PhysXSample::updateSweepSettingForShapes()
{
	enum Word3
	{
		SWEPT_INTEGRATION_LINEAR = 1,
		CLEAN_PAIR_FLAG = 2		// usually the pair flag is initialized to PxPairFlag::eCONTACT_DEFAULT and changes are 
								// applied on top of that. Set this flag to start from a clean pair flag.
	};

	PxU32 word3 = 0;
	bool enable = false;
	if(getActiveScene().getFlags() & PxSceneFlag::eENABLE_SWEPT_INTEGRATION)
	{
		word3 |= SWEPT_INTEGRATION_LINEAR;
		enable = true;
	}

	PxU32 count = getActiveScene().getNbActors(PxActorTypeSelectionFlag::eRIGID_STATIC | PxActorTypeSelectionFlag::eRIGID_DYNAMIC);
	PxActor** buffer = new PxActor*[count];
	getActiveScene().getActors(PxActorTypeSelectionFlag::eRIGID_STATIC | PxActorTypeSelectionFlag::eRIGID_DYNAMIC, buffer, count);

	for(PxU32 i = 0; i < count; i++)
	{
		PxRigidActor* actor = static_cast<PxRigidActor*>(buffer[i]);
		PxU32 nbShapes = actor->getNbShapes();
		PxShape** shapes = (PxShape**) ::alloca(nbShapes * sizeof(PxShape*));

		actor->getShapes(shapes, nbShapes);
		for(PxU32 j = 0; j < nbShapes; j++)
		{
			PxShape* shape = shapes[j];
			if(actor->is<PxRigidDynamic>())
				shape->setFlag(PxShapeFlag::eUSE_SWEPT_BOUNDS, enable);

			//also rerun filtering
			PxFilterData d = shape->getSimulationFilterData();
			d.word3 = word3;
			shape->setSimulationFilterData(d);
		}
	}
	delete buffer;
}
///////////////////////////////////////////////////////////////////////////////
//
// default implemententions for PhysXSample interface
//
void PhysXSample::onPointerInputEvent(const InputEvent& ie, physx::PxU32 x, physx::PxU32 y, physx::PxReal dx, physx::PxReal dy, bool pressed)
{
	switch (ie.m_Id)
	{
	case CAMERA_MOUSE_LOOK:
		{
			if(mPicking)
				mPicking->moveCursor(x,y);
		}
		break;
	case PICKUP:
		{
			if(mPicking)
			{
				mPicked = pressed;
				if(pressed)
					mPicking->lazyPick();
				else
					mPicking->letGo();
			}
		}
		break;
	}

}

void PhysXSample::onResize(PxU32 width, PxU32 height)
{
	mApplication.baseResize(width, height);
}

PhysXSample::~PhysXSample()
{
	for (size_t i = mDeletedRenderActors.size(); i--;)
	{
		mDeletedRenderActors[i]->release();
	}
	mDeletedRenderActors.clear();

	PX_ASSERT(!mRenderActors.size());
	PX_ASSERT(!mRenderTextures.size());
	PX_ASSERT(!mRenderMaterials.size());
	PX_ASSERT(!mPhysicsActors.size());
	PX_ASSERT(!mManagedAssets.size());
	PX_ASSERT(!mBufferedActiveTransforms);
	PX_ASSERT(!mScene);
	PX_ASSERT(!mCpuDispatcher);
//	PX_ASSERT(!mMaterial);
#ifdef PX_WINDOWS
	PX_ASSERT(!mCudaContextManager);
#endif
#ifdef PX_PS3
	PX_ASSERT(!mSpuDispatcher);
#endif
	PX_ASSERT(!mCooking);
	PX_ASSERT(!mPhysics);
	PX_ASSERT(!mProfileZoneManager);
	PX_ASSERT(!mFoundation);

	if(SCRATCH_BLOCK_SIZE)
		SAMPLE_FREE(mScratchBlock);

	delete mPicking;
}

PhysXSample::PhysXSample(PhysXSampleApplication& app, PxU32 maxSubSteps) :
	mInitialDebugRender(false),
	mCreateCudaCtxManager(false),
	mCreateGroundPlane(true),
	mUseDebugStepper(false),
	mUseFixedStepper(true),
	mMaxNumSubSteps(maxSubSteps),
	mNbThreads(1),
	mMaxNumSpus(5),
	mDefaultDensity(1.0f),
	mUseFullPvdConnection(true),
	mDisplayFPS(true),

	mPause(app.mPause),
	mOneFrameUpdate(app.mOneFrameUpdate),
	mShowHelp(app.mShowHelp),
	mShowDescription(app.mShowDescription),
	mShowExtendedHelp(app.mShowExtendedHelp),
	mHideGraphics(false),
	mEnableAutoFlyCamera(false),
	mCameraController(app.mCameraController),
	mApplication(app),
	mFoundation(NULL),
	mProfileZoneManager(NULL),
	mPhysics(NULL),
	mCooking(NULL),
	mScene(NULL),
	mMaterial(NULL),
	mCpuDispatcher(NULL),
#ifdef PX_PS3
	mSpuDispatcher(NULL),
#endif
#ifdef PX_WINDOWS
	mCudaContextManager(NULL),
#endif
	mManagedMaterials(app.mManagedMaterials),
	mSampleInputAsset(NULL),
	mBufferedActiveTransforms(NULL),
	mActiveTransformCount(0),
	mActiveTransformCapacity(0),
	mMeshTag(0),
	mFilename(NULL),
	mScale(1.0f),
	mDebugRenderScale(1.0f),
	mWaitForResults(false),
	mSavedCameraController(NULL),
	
	mDebugStepper(0.016666660f),
	mFixedStepper(0.016666660f, maxSubSteps),
	mVariableStepper(1.0f / 80.0f, 1.0f / 40.0f, maxSubSteps),
	mWireFrame(false),

	mSimulationTime(0.0f),
	mPicked(false),
	mExtendedHelpPage(0),
	mDebugObjectType(DEBUG_OBJECT_BOX)
{
	mDebugStepper.mSample = this;
	mFixedStepper.mSample = this;
	mVariableStepper.mSample = this;
	
	mScratchBlock = SCRATCH_BLOCK_SIZE ? SAMPLE_ALLOC(SCRATCH_BLOCK_SIZE) : 0;

	if (mApplication.getCommandLine().hasSwitch("nonVizPvd"))
		mUseFullPvdConnection = false;

	mFlyCameraController.init(PxVec3(0.0f, 10.0f, 0.0f), PxVec3(0.0f, 0.0f, 0.0f));

	mPicking = new physx::Picking(*this);

	mDeletedActors.clear();
}

void PhysXSample::render()
{
	PxU32 nbVisible = 0;

	if(!mHideGraphics)
	{
		Camera& camera = getCamera();
		Renderer* renderer = getRenderer();

		for(PxU32 i = 0; i < mRenderActors.size(); ++i)
		{
			RenderBaseActor* renderActor = mRenderActors[i];
			if(camera.mPerformVFC && getCamera().cull(renderActor->getWorldBounds())==PLANEAABB_EXCLUSION)
				continue;

			renderActor->render(*renderer, mManagedMaterials[MATERIAL_GREY], mWireFrame);
			++nbVisible;
		}

		if(camera.mPerformVFC)
			printf("Nb visible: %d\n", nbVisible);
	}
	
	RenderPhysX3Debug* debugRender = getDebugRenderer();
	if(debugRender)
		debugRender->queueForRender();
}

void PhysXSample::displayFPS()
{
	if(!mDisplayFPS)
		return;

	char fpsText[512];
	sprintf(fpsText, "%0.2f fps", mFPS.getFPS());

	Renderer* renderer = getRenderer();

	const PxU32 yInc = 18;
	renderer->print(10, getCamera().getScreenHeight() - yInc*2, fpsText);

//	sprintf(fpsText, "%d visible objects", mNbVisible);
//	renderer->print(10, mCamera.getScreenHeight() - yInc*3, fpsText);
}

void PhysXSample::onShutdown()
{
#if defined(RENDERER_TABLET)
	getRenderer()->releaseAllButtons();
#endif
	
	releaseAll(mRenderActors);
	releaseAll(mRenderTextures);
	releaseAll(mRenderMaterials);
	releaseAll(mPhysicsActors);
	
	SAMPLE_FREE(mBufferedActiveTransforms);
	mFixedStepper.shutdown();
	mDebugStepper.shutdown();
	mVariableStepper.shutdown();

	const size_t nbManagedAssets = mManagedAssets.size();
	if(nbManagedAssets)
	{
		SampleAssetManager* assetManager = mApplication.getAssetManager();
		for(PxU32 i=0; i<nbManagedAssets; i++)
			assetManager->returnAsset(*mManagedAssets[i]);
	}
	mManagedAssets.clear();

	mApplication.getPlatform()->getSampleUserInput()->shutdown();

	if(mSampleInputAsset)
	{
		mApplication.getAssetManager()->returnAsset(*mSampleInputAsset);
		mSampleInputAsset = NULL;
	}

	SAFE_RELEASE(mScene);
	SAFE_RELEASE(mCpuDispatcher);

//	SAFE_RELEASE(mMaterial);
	SAFE_RELEASE(mCooking);

#ifdef PX_PS3
	SAFE_RELEASE(mSpuDispatcher);
	PxGetPS3Extension().terminateSDK();
#endif

	PxCloseExtensions();

	if(getApplication().getProfileZone())
	{
		mProfileZoneManager->removeProfileZone(*getApplication().getProfileZone());
		getApplication().releaseProfileZone();
	}

	SAFE_RELEASE(mPhysics);

#ifdef PX_WINDOWS
	SAFE_RELEASE(mCudaContextManager);
#endif

	SAFE_RELEASE(mProfileZoneManager);
	SAFE_RELEASE(mFoundation);
}

void PhysXSample::onInit()
{

	//Recording memory allocations is necessary if you want to 
	//use the memory facilities in PVD effectively.  Since PVD isn't necessarily connected
	//right away, we add a mechanism that records all outstanding memory allocations and
	//forwards them to PVD when it does connect.

	//This certainly has a performance and memory profile effect and thus should be used
	//only in non-production builds.
	bool recordMemoryAllocations = true;
#ifdef RENDERER_ANDROID
	const bool useCustomTrackingAllocator = false;
#else
	const bool useCustomTrackingAllocator = true;
#endif

	PxAllocatorCallback* allocator = &gDefaultAllocatorCallback;

	if(useCustomTrackingAllocator)		
		allocator = getSampleAllocator();		//optional override that will track memory allocations

	mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *allocator, getSampleErrorCallback());
	if(!mFoundation)
		fatalError("PxCreateFoundation failed!");

	mProfileZoneManager = &PxProfileZoneManager::createProfileZoneManager(mFoundation);
	if(!mProfileZoneManager)
		fatalError("PxProfileZoneManager::createProfileZoneManager failed!");

	if(mCreateCudaCtxManager)
	{
#ifdef PX_WINDOWS
		pxtask::CudaContextManagerDesc cudaContextManagerDesc;
		mCudaContextManager = pxtask::createCudaContextManager(*mFoundation, cudaContextManagerDesc, mProfileZoneManager);
		if( mCudaContextManager )
		{
			if( !mCudaContextManager->contextIsValid() )
			{
				mCudaContextManager->release();
				mCudaContextManager = NULL;
			}
		}
#endif
	}

	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale(), recordMemoryAllocations, mProfileZoneManager);
	if(!mPhysics)
		fatalError("PxCreatePhysics failed!");

	if(getApplication().getOrCreateProfileZone(*mFoundation))
		mProfileZoneManager->addProfileZone(*getApplication().getProfileZone());

	if(!PxInitExtensions(*mPhysics))
		fatalError("PxInitExtensions failed!");

	mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, PxCookingParams());
	if(!mCooking)
		fatalError("PxCreateCooking failed!");

	togglePvdConnection();

	if(mPhysics->getPvdConnectionManager())
		mPhysics->getPvdConnectionManager()->addHandler(*this);

#ifdef PX_PS3

#ifdef _DEBUG 
	bool spuPrintfEnabled = true;
#else
	bool spuPrintfEnabled = false;
#endif

	PxGetPS3Extension().initSDK(mMaxNumSpus, spuPrintfEnabled);
#endif

	// setup default material...
	mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.1f);
	if(!mMaterial)
		fatalError("createMaterial failed!");

#if defined(RENDERER_TABLET)
		// load touchscreen control material
		{
			SampleFramework::SampleAsset* ps_asset = getAsset(controlMaterialPath, SampleFramework::SampleAsset::ASSET_MATERIAL);
			mManagedAssets.push_back(ps_asset);
			PX_ASSERT(ps_asset->getType() == SampleFramework::SampleAsset::ASSET_MATERIAL);	
			SampleFramework::SampleMaterialAsset* mat_ps_asset = static_cast<SampleFramework::SampleMaterialAsset*>(ps_asset);
			if(mat_ps_asset->getNumVertexShaders() > 0) 
			{
				RenderMaterial* mat = SAMPLE_NEW(RenderMaterial)(*getRenderer(), mat_ps_asset->getMaterial(0), mat_ps_asset->getMaterialInstance(0), MATERIAL_CONTROLS);
				mRenderMaterials.push_back(mat);
			}
		}
		// load touchscreen button material
		{
			SampleFramework::SampleAsset* ps_asset = getAsset(buttonMaterialPath, SampleFramework::SampleAsset::ASSET_MATERIAL);
			mManagedAssets.push_back(ps_asset);
			PX_ASSERT(ps_asset->getType() == SampleFramework::SampleAsset::ASSET_MATERIAL);	
			SampleFramework::SampleMaterialAsset* mat_ps_asset = static_cast<SampleFramework::SampleMaterialAsset*>(ps_asset);
			if(mat_ps_asset->getNumVertexShaders() > 0) 
			{
				RenderMaterial* mat = SAMPLE_NEW(RenderMaterial)(*getRenderer(), mat_ps_asset->getMaterial(0), mat_ps_asset->getMaterialInstance(0), MATERIAL_BUTTONS);
				mRenderMaterials.push_back(mat);
			}
		}
		Renderer* renderer = getRenderer();
		RenderMaterial* controlMaterial = getMaterial(MATERIAL_CONTROLS);
		renderer->initControls(controlMaterial->mRenderMaterial, 
			controlMaterial->mRenderMaterialInstance);
		RenderMaterial* buttonMaterial = getMaterial(MATERIAL_BUTTONS);
		// add buttons for common use
		PxReal yInc = -0.12f;
		PxVec2 leftBottom(0.58f, 0.90f);
		PxVec2 rightTop(0.99f, 0.82f);
		renderer->addButton(leftBottom, rightTop, NULL, 
			buttonMaterial->mRenderMaterial, buttonMaterial->mRenderMaterialInstance);
		leftBottom.y += yInc; rightTop.y += yInc;
		renderer->addButton(leftBottom, rightTop, NULL,
			buttonMaterial->mRenderMaterial, buttonMaterial->mRenderMaterialInstance);
		leftBottom.y += yInc; rightTop.y += yInc;
		renderer->addButton(leftBottom, rightTop, NULL,
			buttonMaterial->mRenderMaterial, buttonMaterial->mRenderMaterialInstance);
		leftBottom.y += yInc; rightTop.y += yInc;
		renderer->addButton(leftBottom, rightTop, NULL,
			buttonMaterial->mRenderMaterial, buttonMaterial->mRenderMaterialInstance);
		leftBottom.y += yInc; rightTop.y += yInc;

		// add buttons for individual sample
		leftBottom.y += yInc; rightTop.y += yInc;
		renderer->addButton(leftBottom, rightTop, NULL,
			buttonMaterial->mRenderMaterial, buttonMaterial->mRenderMaterialInstance);
		leftBottom.y += yInc; rightTop.y += yInc;
		renderer->addButton(leftBottom, rightTop, NULL, 
			buttonMaterial->mRenderMaterial, buttonMaterial->mRenderMaterialInstance);
		leftBottom.y += yInc; rightTop.y += yInc;
		renderer->addButton(leftBottom, rightTop, NULL,
			buttonMaterial->mRenderMaterial, buttonMaterial->mRenderMaterialInstance);
		leftBottom.y += yInc; rightTop.y += yInc;
		renderer->addButton(leftBottom, rightTop, NULL, 
			buttonMaterial->mRenderMaterial, buttonMaterial->mRenderMaterialInstance);
		leftBottom.y += yInc; rightTop.y += yInc;

		// quick access button
		leftBottom.y += yInc; rightTop.y += yInc;
		renderer->addButton(leftBottom, rightTop, NULL, 
			buttonMaterial->mRenderMaterial, buttonMaterial->mRenderMaterialInstance);

		// next, previous buttons
		leftBottom.x = -0.4f;
		leftBottom.y = 0.9f;
		rightTop.x = -0.1f;
		rightTop.y = 0.82f;
		renderer->addButton(leftBottom, rightTop, NULL, 
			buttonMaterial->mRenderMaterial, buttonMaterial->mRenderMaterialInstance);
		leftBottom.x = 0.1f;
		leftBottom.y = 0.9f;
		rightTop.x = 0.4f;
		rightTop.y = 0.82f;
		renderer->addButton(leftBottom, rightTop, NULL, 
			buttonMaterial->mRenderMaterial, buttonMaterial->mRenderMaterialInstance);

#endif		

	PX_ASSERT(NULL == mScene);

	PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	getDefaultSceneDesc(sceneDesc);
	customizeSceneDesc(sceneDesc);
	

	if(!sceneDesc.cpuDispatcher)
	{
		mCpuDispatcher = PxDefaultCpuDispatcherCreate(mNbThreads);
		if(!mCpuDispatcher)
			fatalError("PxDefaultCpuDispatcherCreate failed!");
		sceneDesc.cpuDispatcher	= mCpuDispatcher;
	}

	if(!sceneDesc.filterShader)
		sceneDesc.filterShader	= getSampleFilterShader();

#ifdef PX_WINDOWS
	if(!sceneDesc.gpuDispatcher && mCudaContextManager)
	{
		sceneDesc.gpuDispatcher = mCudaContextManager->getGpuDispatcher();
	}
#endif

#ifdef PX_PS3
	if(!sceneDesc.spuDispatcher)
	{
		mSpuDispatcher = PxDefaultSpuDispatcherCreate(PxGetPS3Extension().getSimulationTaskSet(),
											  		  PxGetPS3Extension().getQueryTaskSet());
		if(!mSpuDispatcher)
			fatalError("PxDefaultSpuDispatcherCreate failed!");
		sceneDesc.spuDispatcher = mSpuDispatcher;
	}
#endif

	//sceneDesc.flags |= PxSceneFlag::eENABLE_TWO_DIRECTIONAL_FRICTION;
	//sceneDesc.flags |= PxSceneFlag::eENABLE_PCM;//need to register the pcm code in the PxCreatePhysics
	//sceneDesc.flags |= PxSceneFlag::eENABLE_ONE_DIRECTIONAL_FRICTION;
	//sceneDesc.flags |= PxSceneFlag::eADAPTIVE_FORCE;
	sceneDesc.flags |= PxSceneFlag::eENABLE_ACTIVETRANSFORMS;
	mScene = mPhysics->createScene(sceneDesc);
	if(!mScene)
		fatalError("createScene failed!");
   
	PxSceneFlags flag = mScene->getFlags();


	mScene->setVisualizationParameter(PxVisualizationParameter::eSCALE,				mInitialDebugRender ? mDebugRenderScale : 0.0f);
	mScene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES,	1.0f);
	
	mApplication.refreshVisualizationMenuState(PxVisualizationParameter::eCOLLISION_SHAPES);
	mApplication.applyDefaultVisualizationSettings();
	mApplication.setMouseCursorHiding(false);
	mApplication.setMouseCursorRecentering(false);
	mCameraController.setMouseLookOnMouseButton(false);
	mCameraController.setMouseSensitivity(1.0f);

	if(mCreateGroundPlane)
		createGrid();
	LOG_INFO("PhysXSample", "Init sample ok!");
}

RenderMaterial* PhysXSample::getMaterial(PxU32 materialID)
{
	for(PxU32 i = 0; i < mRenderMaterials.size(); ++i) 
	{
		if(mRenderMaterials[i]->mID == materialID) 
		{
			return mRenderMaterials[i];
		}
	}

	return NULL;
}

Stepper* PhysXSample::getStepper()
{
	if(mUseDebugStepper)
		return &mDebugStepper;
	else if(mUseFixedStepper)
		return &mFixedStepper;
	else
		return &mVariableStepper;
}

#if !defined(PX_PROFILE)	// Only enabled for profile build
	#define PIX_PROFILE_ZONE(name)
#elif defined(PX_X360)
	#include "Xtl.h"

	struct PixProfileZone
	{
		PX_INLINE PixProfileZone(char* name)	{ PIXBeginNamedEvent(0, name); }
		PX_INLINE ~PixProfileZone()				{ PIXEndNamedEvent(); }
	};

	#define PIX_PROFILE_ZONE(name)				PixProfileZone profileZone_##name(#name)
#else
	#define PIX_PROFILE_ZONE(name)
#endif

void PhysXSample::freeDeletedActors()
{
	getRenderer()->finishRendering();

	// delete buffered render actors
	for (size_t i = mDeletedRenderActors.size(); i--;)
	{
		mDeletedRenderActors[i]->release();
	}

	mDeletedRenderActors.clear();

}

void PhysXSample::onTickPreRender(float dtime)
{
	// delete buffered render actors
	for (size_t i = mDeletedRenderActors.size(); i--;)
	{
		mDeletedRenderActors[i]->release();
	}

	mDeletedRenderActors.clear();

	mApplication.baseTickPreRender(dtime);
	
	mFPS.update();

	if(!isPaused())
	{
		Stepper* stepper = getStepper();

		mWaitForResults = false;

		if(mScene)
		{
			updateRenderObjectsAsync(dtime);

#if !defined(PX_PROFILE)
			mWaitForResults = stepper->advance(mScene, dtime, mScratchBlock, SCRATCH_BLOCK_SIZE);

			// tells the stepper shape data is not going to be accessed until next frame 
			// (frame ends with stepper->wait(mScene))
			stepper->renderDone();

#else
			// in profile builds we run the whole frame sequentially
			// simulate, wait, update render objects, render
			bool simulationStarted;
			{
				PIX_PROFILE_ZONE(simulate);
				simulationStarted = stepper->advance(mScene, dtime, mScratchBlock, SCRATCH_BLOCK_SIZE);
				stepper->renderDone();
				stepper->wait(mScene);
				mSimulationTime = stepper->getSimulationTime();
			}

			// update render objects immediately
			if (simulationStarted)
			{
				bufferActiveTransforms();
				updateRenderObjectsSync(dtime);
				if (mOneFrameUpdate)
					updateRenderObjectsAsync(dtime);
			}
#endif
		}
	}

	// profile builds can update render actors debug 
	// draw immediately to avoid one frame lag
#if defined(PX_PROFILE)
	updateRenderObjectsDebug(dtime);
#endif

	if(mPicking)
	{
		mPicking->tick();
	}
}

void PhysXSample::onTickPostRender(float dtime)
{
#if !defined(PX_PROFILE)

	if(!isPaused())
	{
		if(mScene && mWaitForResults)
		{
			Stepper* stepper = getStepper();
			stepper->wait(mScene);
			mSimulationTime = stepper->getSimulationTime();

			bufferActiveTransforms();

			// make sure that in single step mode, the render objects get updated immediately
			if (mOneFrameUpdate)  
			{
				updateRenderObjectsSync(dtime);
				updateRenderObjectsAsync(dtime);
			}
			else
				updateRenderObjectsSync(dtime);
		}
	}

#endif
	
	RenderPhysX3Debug* debugRenderer = getDebugRenderer();
	if(debugRenderer && mScene)
	{
		const PxRenderBuffer& debugRenderable = mScene->getRenderBuffer();
		debugRenderer->clear();
		debugRenderer->update(debugRenderable);

#if !defined(PX_PROFILE)
		updateRenderObjectsDebug(dtime);
#endif

		renderScene();
	}

	if(mOneFrameUpdate)
	{
		mOneFrameUpdate = false;
		if (!isPaused()) togglePause();
	}
}

void PhysXSample::saveUserInputs()
{
	char name[256];
	char sBuffer[512];

	const char* sampleName = mApplication.mRunning->getName();

	strcpy(name,"input");	
	strcat(name,"/UserInputList.txt");

	if(getSampleOutputDirManager().getFilePath(name, sBuffer, false))
	{
		sprintf(name, "input/%s/%sUserInputList.txt", sampleName,mApplication.getPlatform()->getPlatformName());

		if(getSampleOutputDirManager().getFilePath(name, sBuffer, false))
		{
			FILE* file = NULL;
			shdfnd::fopen_s(&file, sBuffer, "w");

			if(file)
			{
				fputs("UserInputList:\n",file);
				fputs("----------------------------------------\n",file);
				const std::vector<UserInput>& ilist = mApplication.getPlatform()->getSampleUserInput()->getUserInputList();
				for (size_t i = 0; i < ilist.size(); i++)
				{
					const UserInput& ui = ilist[i];
					fputs(ui.m_IdName,file);
					fputs("\n",file);
				}

				fclose(file);
			}
		}
	}
}

void PhysXSample::saveInputEvents(const std::vector<const InputEvent*>& inputEvents)
{
	char name[256];
	char sBuffer[512];

	const char* sampleName = mApplication.mRunning->getName();

	strcpy(name,"input");	
	strcat(name,"/InputEventList.txt");

	if(getSampleOutputDirManager().getFilePath(name, sBuffer, false))
	{
		sprintf(name, "input/%s/%sInputEventList.txt", sampleName,mApplication.getPlatform()->getPlatformName());

		if(getSampleOutputDirManager().getFilePath(name, sBuffer, false))
		{
			FILE* file = NULL;
			shdfnd::fopen_s(&file, sBuffer, "w");

			if(file)
			{
				fputs("InputEventList:\n",file);
				fputs("----------------------------------------\n",file);
				for (size_t i = 0; i < inputEvents.size(); i++)
				{
					const InputEvent* inputEvent = inputEvents[i];
					
					if(!inputEvent)
						continue;
					
					const std::vector<size_t>* userInputs = mApplication.getPlatform()->getSampleUserInput()->getUserInputs(inputEvent->m_Id);
					if(userInputs && !userInputs->empty())
					{
						fputs(inputEvent->m_Name,file);
						fputs("\n",file);
					}
				}

				fclose(file);
			}
		}
	}
}

void PhysXSample::parseSampleOutputAsset(const char* sampleName,PxU32 userInputCS, PxU32 inputEventCS)
{
	char name[256];
	char sBuffer[512];

	sprintf(name, "input/%s/%sInputMapping.ods", sampleName,mApplication.getPlatform()->getPlatformName());
	if(getSampleOutputDirManager().getFilePath(name, sBuffer, false))
	{
		SampleInputMappingAsset* inputAsset = NULL;
		FILE* fp = NULL;
		physx::fopen_s(&fp, sBuffer, "r");
		if(fp)
		{
			inputAsset = SAMPLE_NEW(SampleInputMappingAsset)(fp,sBuffer, false, userInputCS, inputEventCS);
			if(!inputAsset->isOk())
			{
				DELETESINGLE(inputAsset);
				fp = NULL;
			}
		}

		if(inputAsset)
		{
			std::vector<SampleInputMapping> inputMappings;
			for (size_t i = inputAsset->getSampleInputData().size();i--;)
			{
				const SampleInputData& data = inputAsset->getSampleInputData()[i];
				size_t userInputIndex;
				PxI32 userInputId = mApplication.getPlatform()->getSampleUserInput()->translateUserInputNameToId(data.m_UserInputName,userInputIndex);
				size_t inputEventIndex;
				PxI32 inputEventId = mApplication.getPlatform()->getSampleUserInput()->translateInputEventNameToId(data.m_InputEventName, inputEventIndex);
				if(userInputId >= 0 && inputEventId >= 0)
				{
					SampleInputMapping mapping;
					mapping.m_InputEventId = inputEventId;
					mapping.m_InputEventIndex = inputEventIndex;
					mapping.m_UserInputId = userInputId;
					mapping.m_UserInputIndex = userInputIndex;
					inputMappings.push_back(mapping);
				}
				else
				{
					PX_ASSERT(0);
				}
			}

			for (size_t i = inputMappings.size(); i--;)
			{
				const SampleInputMapping& mapping = inputMappings[i];
				mApplication.getPlatform()->getSampleUserInput()->unregisterInputEvent(mapping.m_InputEventId);
			}

			//now I have the default keys definition left, save it to the mapping
			const std::vector<UserInput>& userInputs = mApplication.getPlatform()->getSampleUserInput()->getUserInputList();
			const std::map<physx::PxU16, std::vector<size_t> >& inputEventUserInputMap = mApplication.getPlatform()->getSampleUserInput()->getInputEventUserInputMap();
			std::map<physx::PxU16, std::vector<size_t> >::const_iterator it = inputEventUserInputMap.begin();
			std::map<physx::PxU16, std::vector<size_t> >::const_iterator itEnd = inputEventUserInputMap.end();
			while (it != itEnd)
			{
				PxU16 inputEventId = it->first;
				const std::vector<size_t>& uis = it->second;
				for (size_t j = 0; j < uis.size(); j++)
				{
					const UserInput& ui = userInputs[uis[j]];
					const InputEvent* ie = mApplication.getPlatform()->getSampleUserInput()->getInputEventSlow(inputEventId);
					if(ie)
					{
						inputAsset->addMapping(ui.m_IdName, ie->m_Name);							
					}
				}
				++it;
			}

			for (size_t i = inputMappings.size(); i--;)
			{
				const SampleInputMapping& mapping = inputMappings[i];
				mApplication.getPlatform()->getSampleUserInput()->registerInputEvent(mapping);
			}
		}
		else
		{
			// the file does not exist create one
			FILE* fp = NULL;
			physx::fopen_s(&fp, sBuffer, "w");
			if(fp)
			{
				inputAsset = SAMPLE_NEW(SampleInputMappingAsset)(fp,sBuffer,true,userInputCS, inputEventCS);	

				const std::vector<UserInput>& userInputs = mApplication.getPlatform()->getSampleUserInput()->getUserInputList();
				const std::map<physx::PxU16, std::vector<size_t> >& inputEventUserInputMap = mApplication.getPlatform()->getSampleUserInput()->getInputEventUserInputMap();
				std::map<physx::PxU16, std::vector<size_t> >::const_iterator it = inputEventUserInputMap.begin();
				std::map<physx::PxU16, std::vector<size_t> >::const_iterator itEnd = inputEventUserInputMap.end();
				while (it != itEnd)
				{
					PxU16 inputEventId = it->first;
					const std::vector<size_t>& uis = it->second;
					for (size_t j = 0; j < uis.size(); j++)
					{
						const UserInput& ui = userInputs[uis[j]];
						const InputEvent* ie = mApplication.getPlatform()->getSampleUserInput()->getInputEventSlow(inputEventId);
						if(ie)
						{
							inputAsset->addMapping(ui.m_IdName, ie->m_Name);							
						}
					}
					++it;
				}
			}
		}

		if(inputAsset)
		{
			inputAsset->saveMappings();
			DELETESINGLE(inputAsset);
		}
	}
}

void PhysXSample::prepareInputEventUserInputInfo(const char* sampleName,PxU32 &userInputCS, PxU32 &inputEventCS)
{
	saveUserInputs();

	std::vector<const InputEvent*> inputEvents;
	mApplication.collectInputEvents(inputEvents);
	
	for (size_t i = inputEvents.size(); i--;)
	{
		const InputEvent* ie = inputEvents[i];
		inputEventCS += ie->m_Id;

		const std::vector<size_t>* userInputs = mApplication.getPlatform()->getSampleUserInput()->getUserInputs(ie->m_Id);
		if(userInputs)
		{
			for (size_t j = userInputs->size(); j--;)
			{
				const UserInput& ui = mApplication.getPlatform()->getSampleUserInput()->getUserInputList()[ (*userInputs)[j] ];
				userInputCS += (ui.m_Id + ie->m_Id);
			}
		}
	}

	inputEventCS = inputEventCS + ((PxU16)mApplication.getPlatform()->getSampleUserInput()->getInputEventList().size() << 16);
	userInputCS = userInputCS + ((PxU16)mApplication.getPlatform()->getSampleUserInput()->getUserInputList().size() << 16);

	saveInputEvents(inputEvents);

	char name[256];

	strcpy(name,"input/");
	strcat(name,mApplication.getPlatform()->getPlatformName());
	strcat(name,"/");
	strcat(name,sampleName);
	strcat(name,"InputMapping.ods");

	// psp2 has memory problems, we will have to pass the allocator
#ifndef RENDERER_PSP2
	// load the additional mapping file 
	mSampleInputAsset = (SampleInputAsset*)getAsset(name, SampleAsset::ASSET_INPUT, false);
#endif
}

void PhysXSample::unregisterInputEvents()
{
	mApplication.getPlatform()->getSampleUserInput()->shutdown();
}

void PhysXSample::registerInputEvents(bool ignoreSaved)
{
	const char* sampleName = mApplication.mRunning->getName();
		
	PxU32 inputEventCS = 0;
	PxU32 userInputCS = 0;
	prepareInputEventUserInputInfo(sampleName, inputEventCS, userInputCS);	

	// register the additional mapping
	if(mSampleInputAsset)
	{
		std::vector<SampleInputMapping> inputMappings;
		for (size_t i = mSampleInputAsset->GetSampleInputData().size();i--;)
		{
			const SampleInputData& data = mSampleInputAsset->GetSampleInputData()[i];
			size_t userInputIndex;
			PxI32 userInputId = mApplication.getPlatform()->getSampleUserInput()->translateUserInputNameToId(data.m_UserInputName,userInputIndex);
			size_t inputEventIndex;
			PxI32 inputEventId = mApplication.getPlatform()->getSampleUserInput()->translateInputEventNameToId(data.m_InputEventName, inputEventIndex);
			if(userInputId >= 0 && inputEventId >= 0)
			{
				SampleInputMapping mapping;
				mapping.m_InputEventId = inputEventId;
				mapping.m_InputEventIndex = inputEventIndex;
				mapping.m_UserInputId = userInputId;
				mapping.m_UserInputIndex = userInputIndex;
				inputMappings.push_back(mapping);
			}
			else
			{
				PX_ASSERT(0);
			}
		}

		for (size_t i = inputMappings.size(); i--;)
		{
			const SampleInputMapping& mapping = inputMappings[i];
			mApplication.getPlatform()->getSampleUserInput()->registerInputEvent(mapping);
		}
	}

#if !defined(RENDERER_ANDROID) && !defined(RENDERER_IOS)
	if (!ignoreSaved)
		parseSampleOutputAsset(sampleName, inputEventCS, userInputCS);
#endif
}

void PhysXSample::onKeyDownEx(SampleFramework::SampleUserInput::KeyCode keyCode, PxU32 param)
{
}

void PhysXSample::collectInputEvents(std::vector<const SampleFramework::InputEvent*>& inputEvents)
{
	//digital keyboard events
	DIGITAL_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT,				WKEY_1,			XKEY_1,			PS3KEY_1,		AKEY_UNKNOWN,	OSXKEY_1,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_1		);
	DIGITAL_INPUT_EVENT_DEF(PAUSE_SAMPLE,					WKEY_P,			XKEY_P,			PS3KEY_P,		AKEY_UNKNOWN,	OSXKEY_P,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_P		);
	DIGITAL_INPUT_EVENT_DEF(STEP_ONE_FRAME,					WKEY_O,			XKEY_O,			PS3KEY_O,		AKEY_UNKNOWN,	OSXKEY_O,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_O		);
	DIGITAL_INPUT_EVENT_DEF(TOGGLE_VISUALIZATION,			WKEY_V,			XKEY_V,			PS3KEY_V,		AKEY_UNKNOWN,	OSXKEY_V,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_V		);
	DIGITAL_INPUT_EVENT_DEF(DECREASE_DEBUG_RENDER_SCALE,	WKEY_F7,		XKEY_F7,		PS3KEY_F7,		AKEY_UNKNOWN,	OSXKEY_F7,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_F7		);
	DIGITAL_INPUT_EVENT_DEF(INCREASE_DEBUG_RENDER_SCALE,	WKEY_F8,		XKEY_F8,		PS3KEY_F8,		AKEY_UNKNOWN,	OSXKEY_F8,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_F8		);
	DIGITAL_INPUT_EVENT_DEF(HIDE_GRAPHICS,					WKEY_G,			XKEY_G,			PS3KEY_G,		AKEY_UNKNOWN,	OSXKEY_G,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_G		);
	DIGITAL_INPUT_EVENT_DEF(WIREFRAME,						WKEY_N,			XKEY_N,			PS3KEY_N,		AKEY_UNKNOWN,	OSXKEY_N,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_N		);
	DIGITAL_INPUT_EVENT_DEF(SWEPT_INTEGRATION,				WKEY_I,			XKEY_I,			PS3KEY_I,		AKEY_UNKNOWN,	OSXKEY_I,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_I		);
	DIGITAL_INPUT_EVENT_DEF(TOGGLE_PVD_CONNECTION,			WKEY_F5,		XKEY_F5,		PS3KEY_F5,		AKEY_UNKNOWN,	OSXKEY_F5,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_F5		);
	DIGITAL_INPUT_EVENT_DEF(SHOW_HELP,						WKEY_H,			XKEY_H,			PS3KEY_H,		AKEY_UNKNOWN,	OSXKEY_H,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_H		);
	DIGITAL_INPUT_EVENT_DEF(SHOW_DESCRIPTION,				WKEY_F,			XKEY_F,			PS3KEY_F,		AKEY_UNKNOWN,	OSXKEY_F,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_F		);
	DIGITAL_INPUT_EVENT_DEF(VARIABLE_TIMESTEP,				WKEY_T,			XKEY_T,			PS3KEY_T,		AKEY_UNKNOWN,	OSXKEY_T,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_T		);
	DIGITAL_INPUT_EVENT_DEF(NEXT_PAGE,						WKEY_NEXT,		XKEY_UNKNOWN,	PS3KEY_NEXT,	AKEY_UNKNOWN,	OSXKEY_RIGHT,	PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_NEXT	);
	DIGITAL_INPUT_EVENT_DEF(PREVIOUS_PAGE,					WKEY_PRIOR,		XKEY_UNKNOWN,	PS3KEY_PRIOR,	AKEY_UNKNOWN,	OSXKEY_LEFT,	PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_PRIOR	);	
	DIGITAL_INPUT_EVENT_DEF(PROFILE_ONLY_PVD,				WKEY_9,			XKEY_UNKNOWN,	PS3KEY_UNKNOWN,	AKEY_UNKNOWN,	OSXKEY_UNKNOWN,	PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_UNKNOWN);

	//digital gamepad events
	DIGITAL_INPUT_EVENT_DEF(SHOW_HELP,						GAMEPAD_SELECT,	GAMEPAD_SELECT,	GAMEPAD_SELECT,	AKEY_UNKNOWN,	GAMEPAD_SELECT,	GAMEPAD_SELECT,	IKEY_UNKNOWN,	LINUXKEY_UNKNOWN);
	DIGITAL_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT,				GAMEPAD_NORTH,	GAMEPAD_NORTH,	GAMEPAD_NORTH,	AKEY_UNKNOWN,	GAMEPAD_NORTH,	GAMEPAD_NORTH,	IKEY_UNKNOWN,	LINUXKEY_UNKNOWN);

	//digital mouse events (are registered in the individual samples as needed)

    //touch events (reserve first 4 buttons for common use, individual samples start from 5)
	TOUCH_INPUT_EVENT_DEF(PAUSE_SAMPLE,		"Pause",		ABUTTON_1,		IBUTTON_1);
	TOUCH_INPUT_EVENT_DEF(STEP_ONE_FRAME,	"Single Step",	ABUTTON_2,		IBUTTON_2);
}

void PhysXSample::onAnalogInputEvent(const SampleFramework::InputEvent& , float val)
{
}

bool PhysXSample::onDigitalInputEvent(const SampleFramework::InputEvent& ie, bool val)
{
	if (!mScene) return true;

	if (val)
	{
		if (mShowExtendedHelp)
		{
			switch (ie.m_Id)
			{
			case NEXT_PAGE:
				{
					mExtendedHelpPage++;
				}
				break;
			case PREVIOUS_PAGE:
				{
					if(mExtendedHelpPage)
						mExtendedHelpPage--;
				}
				break;
			}
			return false;
		}

		switch (ie.m_Id)
		{
		case SPAWN_DEBUG_OBJECT:
			spawnDebugObject();
			break;
		case PAUSE_SAMPLE:
			togglePause();
			break;
		case STEP_ONE_FRAME:
			mOneFrameUpdate = !mOneFrameUpdate;
			break;
		case TOGGLE_VISUALIZATION:
			toggleVisualizationParam(*mScene, PxVisualizationParameter::eSCALE);
			break;
		case DECREASE_DEBUG_RENDER_SCALE:
			{
				mDebugRenderScale -= 0.1f;
				mDebugRenderScale = PxMax(mDebugRenderScale, 0.f);
				mScene->setVisualizationParameter(PxVisualizationParameter::eSCALE, mDebugRenderScale);
				break;
			}
		case INCREASE_DEBUG_RENDER_SCALE:
			{
				mDebugRenderScale += 0.1f;
				mScene->setVisualizationParameter(PxVisualizationParameter::eSCALE, mDebugRenderScale);
				break;
			}
		case HIDE_GRAPHICS:
			mHideGraphics = !mHideGraphics;
			break;
		case WIREFRAME:
			{
				mWireFrame = !mWireFrame;
				break;
			}
		case SWEPT_INTEGRATION:
			{
				if(mScene)
				{
					PxScene& s = getActiveScene();
					if (s.getFlags() & PxSceneFlag::eENABLE_SWEPT_INTEGRATION)
					{
						s.setFlag(PxSceneFlag::eENABLE_SWEPT_INTEGRATION, false);
						updateSweepSettingForShapes();
						printf("PxSceneFlag::eENABLE_SWEPT_INTEGRATION disabled.\n" );
					}
					else
					{
						s.setFlag(PxSceneFlag::eENABLE_SWEPT_INTEGRATION, true);
						updateSweepSettingForShapes();
						printf("PxSceneFlag::eENABLE_SWEPT_INTEGRATION enabled.\n" );
					}
				}
				break;
			}
		case TOGGLE_PVD_CONNECTION:
			{
				togglePvdConnection();
				break;
			}
		case SHOW_HELP:
				mShowHelp = !mShowHelp;
				if(mShowHelp) mShowDescription=false;
			break;
		case SHOW_DESCRIPTION:
				mShowDescription = !mShowDescription;
				if(mShowDescription) mShowHelp=false;
			break;
		case VARIABLE_TIMESTEP:
			mUseFixedStepper = !mUseFixedStepper;
			mFixedStepper.reset();
			mVariableStepper.reset();		
			break;
		case DELETE_PICKED:
			if(mPicked && mPicking)
			{
				//sschirm: this seems to be incomplete. RenderActors that are linked aren't take care 
				//of all the time and we should have a callback for Samples and Tests that have references 
				//to the actors.
				PxActor* pickedActor = mPicking->letGo();
				if(pickedActor)
					pickedActor->release();
			}
			break;
		case PICKUP:
			{
				if(mPicking)
				{
					mPicked = true;
					PxU32 width;
					PxU32 height;
					mApplication.getPlatform()->getWindowSize(width, height);
					mPicking->moveCursor(width/2,height/2);
					mPicking->lazyPick();
				}
			}
			break;
		case PROFILE_ONLY_PVD:
			if (mUseFullPvdConnection && NULL != mPhysics->getPvdConnectionManager())
			{
				mPhysics->getPvdConnectionManager()->disconnect();
				mUseFullPvdConnection = false;
				createPvdConnection();
			}
			break;
		default: break;
		}
	}
	else
	{
		if (mShowExtendedHelp)
		{
			return false;
		}

		if (ie.m_Id == PICKUP)
		{
			if(mPicking)
			{
				mPicked = false;
				mPicking->letGo();
			}
		}
	}
	return true;
}

void PhysXSample::togglePause()
{
	unregisterInputEvents();
	mPause = !mPause;
	if (mEnableAutoFlyCamera)
	{
		if (mPause)
		{
			mSavedCameraController = getCurrentCameraController();
			mApplication.saveCameraState();
			mFlyCameraController.init(getCamera().getViewMatrix());
			setCameraController(&mFlyCameraController);
		}
		else
		{
			mApplication.restoreCameraState();
			setCameraController(mSavedCameraController);
		}
	}
	registerInputEvents(true);
}

void PhysXSample::showExtendedInputEventHelp(PxU32 x, PxU32 y)
{
	const PxReal scale = 0.5f;
	const PxReal shadowOffset = 6.0f;
	const RendererColor textColor(255, 255, 255, 255);

	Renderer* renderer = getRenderer();
	const PxU32 yInc = 18;
	char message[512];

	PxU32 width = 0;
	PxU32 height = 0;
	renderer->getWindowSize(width, height);
	y += yInc;

	PxU16 numIe = (height - y)/yInc - 8;

	const std::vector<InputEvent> inputEventList = getApplication().getPlatform()->getSampleUserInput()->getInputEventList();

	size_t maxHelpPage = inputEventList.size()/numIe;
	if(maxHelpPage < mExtendedHelpPage)
		mExtendedHelpPage = (PxU8) maxHelpPage;

	PxU16 printed = 0;
	PxU16 startPrint = 0; 
	for (size_t i = 0; i < inputEventList.size(); i++)
	{
		const InputEvent& ie = inputEventList[i];
		const char* msg = mApplication.inputInfoMsg("Press "," to ", ie.m_Id, -1);
		if(msg)
		{
			startPrint++;
			if(startPrint <= numIe*mExtendedHelpPage)
				continue;

			strcpy(message,msg);
			strcat(message,ie.m_Name);
			renderer->print(x, y, message,								scale, shadowOffset, textColor);
			y += yInc;

			printed++;
			if(printed >= numIe)
			{			
				break;
			}
		}
	}

	if(printed == 0)
	{
		if(mExtendedHelpPage)
			mExtendedHelpPage--;
	}

	y += yInc;
	const char* msg = mApplication.inputInfoMsg("Press "," to show next/previous page", NEXT_PAGE, PREVIOUS_PAGE);
	if(msg)
		renderer->print(x, y += yInc, msg, scale, shadowOffset, textColor);
}

///////////////////////////////////////////////////////////////////////////////

RenderBaseActor* PhysXSample::createRenderBoxFromShape(PxShape* shape, RenderMaterial* material, const PxReal* uvs)
{
	RenderBaseActor* shapeRenderActor = NULL;
	Renderer* renderer = getRenderer();
	PX_ASSERT(renderer);

	PxGeometryType::Enum geomType = shape->getGeometryType();
	PX_ASSERT(geomType==PxGeometryType::eBOX);
	switch(geomType)
	{
	case PxGeometryType::eBOX:
		{
			// Get physics geometry
			PxBoxGeometry geometry;
			bool status = shape->getBoxGeometry(geometry);
			PX_ASSERT(status);

			// Create render object
			shapeRenderActor = SAMPLE_NEW(RenderBoxActor)(*renderer, geometry.halfExtents, uvs);
		}
		break;
	default: {}
	};

	if(shapeRenderActor)
	{
		link(shapeRenderActor, shape);
		mRenderActors.push_back(shapeRenderActor);
		shapeRenderActor->setRenderMaterial(material);
	}
	return shapeRenderActor;
}


RenderBaseActor* PhysXSample::createRenderObjectFromShape(PxShape* shape, RenderMaterial* material)
{
	PX_ASSERT(getRenderer());
	RenderBaseActor* shapeRenderActor = NULL;
	Renderer& renderer = *getRenderer();

	PxGeometryHolder geom = shape->getGeometry();

	switch(geom.getType())
	{
	case PxGeometryType::eSPHERE:
		shapeRenderActor = SAMPLE_NEW(RenderSphereActor)(renderer, geom.sphere().radius);
		break;
	case PxGeometryType::ePLANE:
		shapeRenderActor = SAMPLE_NEW(RenderGridActor)(renderer, 50, 1.f, PxShapeExt::getGlobalPose(*shape).q);
		break;
	case PxGeometryType::eCAPSULE:
		shapeRenderActor = SAMPLE_NEW(RenderCapsuleActor)(renderer, geom.capsule().radius, geom.capsule().halfHeight);
		break;
	case PxGeometryType::eBOX:
		shapeRenderActor = SAMPLE_NEW(RenderBoxActor)(renderer, geom.box().halfExtents);
		break;
	case PxGeometryType::eCONVEXMESH:
		{
			PxConvexMesh* convexMesh = geom.convexMesh().convexMesh;

			// ### doesn't support scale
			PxU32 nbVerts = convexMesh->getNbVertices();
			const PxVec3* convexVerts = convexMesh->getVertices();
			const PxU8* indexBuffer = convexMesh->getIndexBuffer();
			PxU32 nbPolygons = convexMesh->getNbPolygons();

			PxU32 totalNbTris = 0;
			PxU32 totalNbVerts = 0;
			for(PxU32 i=0;i<nbPolygons;i++)
			{
				PxHullPolygon data;
				bool status = convexMesh->getPolygonData(i, data);
				PX_ASSERT(status);
				totalNbVerts += data.mNbVerts;
				totalNbTris += data.mNbVerts - 2;
			}

			PxVec3Alloc* allocVerts = SAMPLE_NEW(PxVec3Alloc)[totalNbVerts];
			PxVec3Alloc* allocNormals = SAMPLE_NEW(PxVec3Alloc)[totalNbVerts];
			PxReal*	UVs = (PxReal*)SAMPLE_ALLOC(sizeof(PxReal)*(totalNbVerts * 2));
			PxU16* faces = (PxU16*)SAMPLE_ALLOC(sizeof(PxU16)*totalNbTris*3);

			PxU16* triangles = faces;
			PxVec3* vertices = allocVerts,
				  * normals = allocNormals;

			PxU32 offset = 0;
			for(PxU32 i=0;i<nbPolygons;i++)
			{
				PxHullPolygon face;
				bool status = convexMesh->getPolygonData(i, face);
				PX_ASSERT(status);
	
				const PxU8* faceIndices = indexBuffer+face.mIndexBase;
				for(PxU32 j=0;j<face.mNbVerts;j++)
				{
					vertices[offset+j] = convexVerts[faceIndices[j]];
					normals[offset+j] = PxVec3(face.mPlane[0], face.mPlane[1], face.mPlane[2]);
				}

				for(PxU32 j=2;j<face.mNbVerts;j++)
				{
					*triangles++ = PxU16(offset);
					*triangles++ = PxU16(offset+j);
					*triangles++ = PxU16(offset+j-1);
				}

				offset += face.mNbVerts;
			}

			// prepare UVs for convex:
			// filling like this
			// vertice #0 - 0,0
			// vertice #1 - 0,1
			// vertice #2 - 1,0
			// vertice #3 - 0,0
			// ...
			for(PxU32 i = 0; i < totalNbVerts; ++i)
			{
				PxU32 c = i % 3;
				if(c == 0)
				{
					UVs[2 * i] = 0.0f;
					UVs[2 * i + 1] = 0.0f;
				}
				else if(c == 1) 
				{
					UVs[2 * i] = 0.0f;
					UVs[2 * i + 1] = 1.0f;
				}
				else if(c == 2)
				{
					UVs[2 * i] = 1.0f;
					UVs[2 * i + 1] = 0.0f;
				}
			}

			PX_ASSERT(offset==totalNbVerts);
			shapeRenderActor = SAMPLE_NEW(RenderMeshActor)(renderer, vertices, totalNbVerts, normals, UVs, faces, totalNbTris);
			shapeRenderActor->setMeshScale(geom.convexMesh().scale);

			SAMPLE_FREE(faces);
			SAMPLE_FREE(UVs);
			DELETEARRAY(allocVerts);
			DELETEARRAY(allocNormals);
		}
		break;
	case PxGeometryType::eTRIANGLEMESH:
		{
			// Get physics geometry
			PxTriangleMesh* tm = geom.triangleMesh().triangleMesh;

			const PxU32 nbVerts = tm->getNbVertices();
			const PxVec3* verts = tm->getVertices();
			const PxU32 nbTris = tm->getNbTriangles();
			const void* tris = tm->getTriangles();
			const bool has16bitIndices = tm->has16BitTriangleIndices();
			PX_ASSERT(has16bitIndices);

			shapeRenderActor = SAMPLE_NEW(RenderMeshActor)(renderer, verts, nbVerts, NULL, NULL, (const PxU16*)tris, nbTris, true);			
			shapeRenderActor->setMeshScale(geom.triangleMesh().scale);

			if (!material)
				material = mManagedMaterials[MATERIAL_FLAT];
		}
		break;
	case PxGeometryType::eHEIGHTFIELD:
		{
			// Get physics geometry
			const PxHeightFieldGeometry& geometry = geom.heightField();
			
			const PxReal	rs = geometry.rowScale;
			const PxReal	hs = geometry.heightScale;
			const PxReal	cs = geometry.columnScale;

			// Create render object
			PxHeightField*	hf = geometry.heightField;
			const PxU32		nbCols = hf->getNbColumns();
			const PxU32		nbRows = hf->getNbRows();
			const PxU32		nbVerts = nbRows * nbCols;	
			const PxU32     nbFaces = (nbCols - 1) * (nbRows - 1) * 2;

			PxHeightFieldSample* sampleBuffer = new PxHeightFieldSample[nbVerts];
			hf->saveCells(sampleBuffer, nbVerts * sizeof(PxHeightFieldSample));

			PxVec3* vertexes = new PxVec3[nbVerts];
			for(PxU32 i = 0; i < nbRows; i++) 
			{
				for(PxU32 j = 0; j < nbCols; j++) 
				{
					vertexes[i * nbCols + j] = PxVec3(PxReal(i) * rs, PxReal(sampleBuffer[j + (i*nbCols)].height) * hs, PxReal(j) * cs);
				}
			}

			PxU32* indices = (PxU32*)SAMPLE_ALLOC(sizeof(PxU32) * nbFaces * 3);
			for(PxU32 i = 0; i < (nbCols - 1); ++i) 
			{
				for(PxU32 j = 0; j < (nbRows - 1); ++j) 
				{
					PxU8 tessFlag = sampleBuffer[i+j*nbCols].tessFlag();
					PxU32 i0 = i * nbRows + j;
					PxU32 i1 = i * nbRows + j + 1;
					PxU32 i2 = (i+1) * nbRows + j;
					PxU32 i3 = (i+1) * nbRows + j+1;
					// i2---i3
					// |    |
					// |    |
					// i0---i1
					// this is really a corner vertex index, not triangle index
					PxU32 mat0 = hf->getTriangleMaterialIndex((j*nbCols+i)*2);
					PxU32 mat1 = hf->getTriangleMaterialIndex((j*nbCols+i)*2+1);
					bool hole0 = (mat0 == PxHeightFieldMaterial::eHOLE);
					bool hole1 = (mat1 == PxHeightFieldMaterial::eHOLE);
					// first triangle
					indices[6 * (i * (nbRows - 1) + j) + 0] = hole0 ? i0 : i2; // duplicate i0 to make a hole
					indices[6 * (i * (nbRows - 1) + j) + 1] = i0;
					indices[6 * (i * (nbRows - 1) + j) + 2] = tessFlag ? i3 : i1;
					// second triangle
					indices[6 * (i * (nbRows - 1) + j) + 3] = hole1 ? i1 : i3; // duplicate i1 to make a hole
					indices[6 * (i * (nbRows - 1) + j) + 4] = tessFlag ? i0 : i2;
					indices[6 * (i * (nbRows - 1) + j) + 5] = i1;
				}
			}
			
			PxU16* indices_16bit = (PxU16*)SAMPLE_ALLOC(sizeof(PxU16) * nbFaces * 3);
			for(PxU32 i=0;  i< nbFaces; i++)
			{
				indices_16bit[i*3+0] = indices[i*3+0];
				indices_16bit[i*3+1] = indices[i*3+2];
				indices_16bit[i*3+2] = indices[i*3+1];
			}
		
			shapeRenderActor = SAMPLE_NEW(RenderMeshActor)(renderer, vertexes, nbVerts, NULL, NULL, indices_16bit, nbFaces);
			SAMPLE_FREE(indices_16bit);
			SAMPLE_FREE(indices);
			DELETEARRAY(sampleBuffer);
			DELETEARRAY(vertexes);

			if (!material)				
				material = mManagedMaterials[MATERIAL_FLAT];
		}
		break;
		default: {}
	};

	if(shapeRenderActor)
	{
		link(shapeRenderActor, shape);
		mRenderActors.push_back(shapeRenderActor);
		shapeRenderActor->setRenderMaterial(material);
	}
	return shapeRenderActor;
}

void PhysXSample::updateRenderObjectsFromRigidActor(PxRigidActor& actor)
{
	PxU32 nbShapes = actor.getNbShapes();
	if(nbShapes > 0)
	{
		const PxU32 nbShapesOnStack = 8;
		PxShape* shapesOnStack[nbShapesOnStack], **shapes = &shapesOnStack[0];
		if(nbShapes > nbShapesOnStack)
			shapes = new PxShape*[nbShapes];
		actor.getShapes(shapes, nbShapes);

		for(PxU32 i = 0; i < nbShapes; ++i)
		{
			RenderBaseActor* renderActor = reinterpret_cast<RenderBaseActor*>(shapes[i]->userData);
			if(renderActor != NULL)
				renderActor->mActive = true;
			else 
				createRenderObjectFromShape(shapes[i]);
		}

		if(nbShapes > nbShapesOnStack)
			delete[] shapes;
	}
}
void PhysXSample::createRenderObjectsFromScene()
{
	PxScene& scene = getActiveScene();

	PxActorTypeSelectionFlags types = PxActorTypeSelectionFlag::eRIGID_STATIC | PxActorTypeSelectionFlag::eRIGID_DYNAMIC;

#if PX_USE_PARTICLE_SYSTEM_API
	types |= PxActorTypeSelectionFlag::ePARTICLE_SYSTEM | PxActorTypeSelectionFlag::ePARTICLE_FLUID;
#endif

#if PX_USE_CLOTH_API
	types |= PxActorTypeSelectionFlag::eCLOTH;
#endif

		PxU32 nbActors = scene.getNbActors(types);
		if(nbActors)
		{
			PxActor** actors = new PxActor* [nbActors];
			scene.getActors(types, actors, nbActors);
			for(PxU32 i = 0; i < nbActors; ++i) 
			{
				switch (actors[i]->getType())
				{
				case PxActorType::eRIGID_STATIC:
				case PxActorType::eRIGID_DYNAMIC:
					updateRenderObjectsFromRigidActor(*reinterpret_cast<PxRigidActor*>(actors[i]));
					break;
#if PX_USE_PARTICLE_SYSTEM_API
				case PxActorType::ePARTICLE_SYSTEM:
				case PxActorType::ePARTICLE_FLUID:
					//				updateRenderObjectsFromRigidActor(*reinterpret_cast<PxRigidActor*>(actors[i]));
					//				break;
#endif
#if PX_USE_CLOTH_API
				case PxActorType::eCLOTH:
#endif
				default:
					break;
				}
			}
			delete[] actors;
		}

		PxU32 nbArticulations = scene.getNbArticulations();
		if(nbArticulations > 0)
		{
			PxArticulation** articulations = new PxArticulation* [nbArticulations];
			scene.getArticulations(articulations, nbArticulations);	
			for(PxU32 i=0; i < nbArticulations; i++)
			{
				updateRenderObjectsFromArticulation(*articulations[i]);
			}
			delete[] articulations;
		}	
}

void PhysXSample::updateRenderObjectsFromArticulation(PxArticulation& articulation)
{
	SampleInlineArray<PxArticulationLink*,20> links;
	links.resize(articulation.getNbLinks());
	articulation.getLinks(links.begin(), links.size());
	
	for(PxU32 i=0; i < links.size(); i++)
	{
		updateRenderObjectsFromRigidActor(*links[i]);
	}
}
void PhysXSample::createRenderObjectsFromActor(PxRigidActor* rigidActor, RenderMaterial* material)
{
	PX_ASSERT(rigidActor);

	PxU32 nbShapes = rigidActor->getNbShapes();
	if(!nbShapes)
		return;

	PxShape** shapes = (PxShape**)SAMPLE_ALLOC(sizeof(PxShape*)*nbShapes);
	PxU32 nb = rigidActor->getShapes(shapes, nbShapes);
	PX_ASSERT(nb==nbShapes);
	for(PxU32 i=0;i<nbShapes;i++)
	{
		createRenderObjectFromShape(shapes[i], material);
	}
	SAMPLE_FREE(shapes);
}

void PhysXSample::updateRenderObjectsDebug(float dtime)
{
	RenderPhysX3Debug* debugRenderer = getDebugRenderer();
	if(debugRenderer && mScene)
	{
		for(PxU32 i = 0; i < mRenderActors.size(); ++i)
		{
			if (mRenderActors[i]->getEnableDebugRender())
				mRenderActors[i]->drawDebug(debugRenderer);
		}
		getCamera().drawDebug(debugRenderer);

#ifdef VISUALIZE_PICKING_RAYS
		if(mPicking)
		{
			const std::vector<Picking::Ray>& rays = mPicking->getRays();
			PxU32 nbRays = rays.size();
			const RendererColor color(255, 0, 0);
			for(PxU32 i=0;i<nbRays;i++)
			{
				debugRenderer->addLine(rays[i].origin, rays[i].origin + rays[i].dir * 1000.0f, color);
			}
		}
#endif
	}
}

void PhysXSample::initRenderObjects()
{
	for (PxU32 i = 0; i < mRenderActors.size(); ++i)
	{
		mRenderActors[i]->update(0.0f);
	}
}

void PhysXSample::updateRenderObjectsSync(float dtime)
{
#if PX_USE_CLOTH_API
	for(PxU32 i = 0; i < mRenderClothActors.size(); ++i)
		mRenderClothActors[i]->update(dtime);
#endif

#if PX_USE_PARTICLE_SYSTEM_API
	for(PxU32 i = 0; i < mRenderParticleSystemActors.size(); ++i)
		mRenderParticleSystemActors[i]->update(dtime);
#endif
}

void PhysXSample::updateRenderObjectsAsync(float dtime)
{
	if(mActiveTransformCount)
	{
		void* cct = (void*)PX_MAKE_FOURCC('C','C','T','S'); // Mark as a "CCT Shape"
		
		PxU32 nbActiveTransforms = mActiveTransformCount;
		PxActiveTransform* currentTransform = mBufferedActiveTransforms;
		while(nbActiveTransforms--)
		{
			const PxActiveTransform& activeTransform = *currentTransform++;
			PxActor* actor = activeTransform.actor;

			// Check that actor is not a deleted actor
			bool isDeleted = false;
			for (PxU32 i=0; i < mDeletedActors.size(); i++)
			{
				if (mDeletedActors[i] == actor)
				{
					isDeleted = true;
					break;
				}
			}
			if (isDeleted) continue;

			const PxType actorType = actor->getConcreteType();
			if(actorType==PxConcreteType::eRIGID_DYNAMIC || actorType==PxConcreteType::eRIGID_STATIC 
				|| actorType == PxConcreteType::eARTICULATION_LINK || actorType == PxConcreteType::eARTICULATION_JOINT)
			{
				PxRigidActor* rigidActor = static_cast<PxRigidActor*>(actor);
				PxU32 nbShapes = rigidActor->getNbShapes();
				for(PxU32 i=0;i<nbShapes;i++)
				{
					PxShape* shape;
					PxU32 n = rigidActor->getShapes(&shape, 1, i);
					PX_ASSERT(n==1);

					if(shape->userData && shape->userData != cct)
					{
						RenderBaseActor* renderActor = reinterpret_cast<RenderBaseActor*>(shape->userData);
						renderActor->update(dtime);
					}
				}
			}
		}
		mActiveTransformCount = 0;
		mDeletedActors.clear();
	}
}

void PhysXSample::bufferActiveTransforms()
{
	// buffer active transforms to perform render object update parallel to simulation

	const PxActiveTransform* activeTransforms = mScene->getActiveTransforms(mActiveTransformCount);
	if(mActiveTransformCapacity < mActiveTransformCount)
	{
		SAMPLE_FREE(mBufferedActiveTransforms);
		mActiveTransformCapacity = (PxU32)(mActiveTransformCount * 1.5f);
		mBufferedActiveTransforms = (PxActiveTransform*)SAMPLE_ALLOC(sizeof(PxActiveTransform) * mActiveTransformCapacity);
	}
	if(mActiveTransformCount)
		Ps::memCopy(mBufferedActiveTransforms, activeTransforms, sizeof(PxActiveTransform) * mActiveTransformCount);
}

///////////////////////////////////////////////////////////////////////////////
#if PX_USE_CLOTH_API

PxCloth* PhysXSample::createClothFromMeshDesc(
	PxClothMeshDesc& meshDesc, const PxTransform& pose, PxClothCollisionData* collData, const PxVec3& gravityDir, const PxReal* uv, const char* textureFile, const PxVec3& color, PxReal scale)
{
	PxClothFabric* clothFabric = Test::ClothHelpers::createFabric(getPhysics(), getCooking(), meshDesc, gravityDir);
	if (!clothFabric)
		return 0;

	// create cloth particle to set initial position and inverse mass (constraint)
	SampleArray<PxClothParticle> clothParticles(meshDesc.points.count);
	Test::ClothHelpers::createDefaultParticles(meshDesc, clothParticles.begin());

	// flags to set GPU solver, CCD, etc.
	PxClothFlags flags;

	// create the cloth actor
	PxCloth* cloth;	
	if (collData)
		cloth = getPhysics().createCloth( pose, *clothFabric, &clothParticles[0], *collData, flags);
	else
	{
		PxClothCollisionData collisionData;
		cloth = getPhysics().createCloth( pose, *clothFabric, &clothParticles[0], collisionData, flags);
	}

	cloth->setSolverFrequency(60.0f); // don't know how to get target simulation frequency, just hardcode for now

	PX_ASSERT(cloth);	

	// add this cloth into the scene
	getActiveScene().addActor(*cloth);

	// create render material
	RenderMaterial* clothMaterial = createRenderMaterialFromTextureFile(textureFile);

	// create the render object in sample framework
	createRenderObjectsFromCloth(*cloth, meshDesc, clothMaterial, uv, true, color, scale);

	return cloth;
}

///////////////////////////////////////////////////////////////////////////////
// create cloth from obj file
PxCloth* PhysXSample::createClothFromObj(
	const char* objFileName, const PxTransform& pose, PxClothCollisionData* collData, const char* textureFile)
{
	// create a mesh grid
	PxClothMeshDesc meshDesc;
	SampleArray<PxVec3> vertices;
	SampleArray<PxU32> primitives;
	SampleArray<PxReal> textures;
	Test::ClothHelpers::createMeshFromObj(objFileName, 1.0f, NULL, NULL, vertices, primitives, &textures, meshDesc);

	return createClothFromMeshDesc(meshDesc, pose, collData, PxVec3(0,0,-1), textures.begin(), textureFile);
}

///////////////////////////////////////////////////////////////////////////////
// create cloth grid in XZ plane
PxCloth* PhysXSample::createGridCloth(
    PxReal sizeX, PxReal sizeZ, PxU32 numX, PxU32 numZ,
	const PxTransform& pose, PxClothCollisionData* collData,
	const char* textureFile)
{
	// create a mesh grid
	PxClothMeshDesc meshDesc;
	SampleArray<PxVec3> vertices;
	SampleArray<PxU32> primitives;
	SampleArray<PxReal> uvs;
	Test::ClothHelpers::createMeshGrid(sizeX, sizeZ, numX, numZ, vertices, primitives, uvs, meshDesc);

	return createClothFromMeshDesc(meshDesc, pose, collData, PxVec3(0,0,-1), uvs.begin(), textureFile);
}

#endif // PX_USE_CLOTH_API

///////////////////////////////////////////////////////////////////////////////
RenderMaterial* PhysXSample::createRenderMaterialFromTextureFile(const char* filename)
{
	RenderMaterial* material = NULL;
	if (!filename)
		return NULL;

	RAWTexture data;
	data.mName = filename;
	RenderTexture* texture = createRenderTextureFromRawTexture(data);	
	material = SAMPLE_NEW(RenderMaterial)(*getRenderer(), PxVec3(0.7f, 0.7f, 0.7f), 1.0f, true, MATERIAL_CLOTH, texture);
	mRenderMaterials.push_back(material);

	return material;
}

///////////////////////////////////////////////////////////////////////////////
#if PX_USE_CLOTH_API

void PhysXSample::createRenderObjectsFromCloth(const PxCloth& cloth, const PxClothMeshDesc& meshDesc, RenderMaterial* material, const PxReal* uv, bool enableDebugRender, const PxVec3& color, PxReal scale)
{
    RenderClothActor* clothActor = SAMPLE_NEW (RenderClothActor)(*getRenderer(), cloth, meshDesc,uv, color, scale );
	if(!clothActor)
		return;

    if (material)
        clothActor->setRenderMaterial(material);

	clothActor->setEnableDebugRender(enableDebugRender);

	mRenderClothActors.push_back(clothActor);
	mRenderActors.push_back(clothActor);
	
	const RenderClothActor::CollisionActorArray& spheres = clothActor->getSphereActors();
	for (PxU32 i=0; i < spheres.size(); ++i)
		mRenderActors.push_back(spheres[i]);

	const RenderClothActor::CollisionActorArray& capsules = clothActor->getCapsuleActors();
	for (PxU32 i=0; i < capsules.size(); ++i)
		mRenderActors.push_back(capsules[i]);
}

#endif // PX_USE_CLOTH_API

///////////////////////////////////////////////////////////////////////////////

PxRigidActor* PhysXSample::createGrid(RenderMaterial* material)
{
	Renderer* renderer = getRenderer();
	PX_ASSERT(renderer);

	PxRigidStatic* plane = PxCreatePlane(*mPhysics, PxPlane(PxVec3(0,1,0), 0), *mMaterial);
	if(!plane)
		fatalError("create plane failed!");

	mScene->addActor(*plane);

	PxShape* shape;
	plane->getShapes(&shape, 1);

	RenderGridActor* actor = SAMPLE_NEW(RenderGridActor)(*renderer, 20, 10.0f);
	link(actor, shape);
	actor->setTransform(PxTransform::createIdentity());
	mRenderActors.push_back(actor);
	actor->setRenderMaterial(material);
	return plane;
}

///////////////////////////////////////////////////////////////////////////////

void PhysXSample::spawnDebugObject()
{
	PxU32 types = getDebugObjectTypes();

	if (!types)
		return;

	//select legal type
	while ((mDebugObjectType & types) == 0)
		mDebugObjectType = (mDebugObjectType << 1) ? 0 : 1;

	if ((mDebugObjectType & DEBUG_OBJECT_ALL) == 0)
		return; 

	const PxVec3 pos = getCamera().getPos();
	const PxVec3 vel = getCamera().getViewDir() * getDebugObjectsVelocity();

	PxRigidDynamic* actor = NULL;
	switch (mDebugObjectType)
	{
	case DEBUG_OBJECT_SPHERE:
		actor = createSphere(pos, getDebugSphereObjectRadius(), &vel, mManagedMaterials[MATERIAL_GREEN], mDefaultDensity);
		break;
	case DEBUG_OBJECT_BOX:
		actor = createBox(pos, getDebugBoxObjectExtents(), &vel, mManagedMaterials[MATERIAL_RED], mDefaultDensity);
		break;
	case DEBUG_OBJECT_CAPSULE:
		actor = createCapsule(pos, getDebugCapsuleObjectRadius(), getDebugCapsuleObjectHalfHeight(), &vel, mManagedMaterials[MATERIAL_BLUE], mDefaultDensity);
		break;
	case DEBUG_OBJECT_CONVEX:
		actor = createConvex(pos, &vel, mManagedMaterials[MATERIAL_YELLOW], mDefaultDensity);
		break;
	case DEBUG_OBJECT_COMPOUND:
		actor = createTestCompound(pos, 320, 0.1f, 2.0f, &vel, NULL, mDefaultDensity, true);
		break;
	}
	
	if (actor)
		onDebugObjectCreation(actor);

	//switch type
	mDebugObjectType = mDebugObjectType << 1;
	while ((mDebugObjectType & types) == 0)
		mDebugObjectType = (mDebugObjectType << 1) ? 0 : 1;
}

///////////////////////////////////////////////////////////////////////////////

PxRigidDynamic* PhysXSample::createBox(const PxVec3& pos, const PxVec3& dims, const PxVec3* linVel, RenderMaterial* material, PxReal density)
{
	Renderer* renderer = getRenderer();
	PX_ASSERT(renderer);

	PxRigidDynamic* box = PxCreateDynamic(*mPhysics, PxTransform(pos), PxBoxGeometry(dims), *mMaterial, density);
	PX_ASSERT(box);

	SetupDefaultRigidDynamic(*box);
	mScene->addActor(*box);
	mPhysicsActors.push_back(box);

	if(linVel)
		box->setLinearVelocity(*linVel);

	createRenderObjectsFromActor(box, material);

	return box;
}

///////////////////////////////////////////////////////////////////////////////

PxRigidDynamic* PhysXSample::createSphere(const PxVec3& pos, PxReal radius, const PxVec3* linVel, RenderMaterial* material, PxReal density)
{
	Renderer* renderer = getRenderer();
	PX_ASSERT(renderer);
	
	PxRigidDynamic* sphere = PxCreateDynamic(*mPhysics, PxTransform(pos), PxSphereGeometry(radius), *mMaterial, density);
	PX_ASSERT(sphere);

	SetupDefaultRigidDynamic(*sphere);
	mScene->addActor(*sphere);
	mPhysicsActors.push_back(sphere);

	if(linVel)
		sphere->setLinearVelocity(*linVel);

	createRenderObjectsFromActor(sphere, material);

	return sphere;
}

///////////////////////////////////////////////////////////////////////////////

PxRigidDynamic* PhysXSample::createCapsule(const PxVec3& pos, PxReal radius, PxReal halfHeight, const PxVec3* linVel, RenderMaterial* material, PxReal density)
{
	Renderer* renderer = getRenderer();
	PX_ASSERT(renderer);

	const PxQuat rot = PxQuat::createIdentity();

	PxRigidDynamic* capsule = PxCreateDynamic(*mPhysics, PxTransform(pos), PxCapsuleGeometry(radius, halfHeight), *mMaterial, density);
	PX_ASSERT(capsule);

	SetupDefaultRigidDynamic(*capsule);
	mScene->addActor(*capsule);
	mPhysicsActors.push_back(capsule);

	if(linVel)
		capsule->setLinearVelocity(*linVel);

	createRenderObjectsFromActor(capsule, material);

	return capsule;
}

///////////////////////////////////////////////////////////////////////////////

PxRigidDynamic* PhysXSample::createConvex(const PxVec3& pos, const PxVec3* linVel, RenderMaterial* material, PxReal density)
{
	Renderer* renderer = getRenderer();
	PX_ASSERT(renderer);

	PxConvexMesh* convexMesh = GenerateConvex(*mPhysics, *mCooking, getDebugConvexObjectScale(), false, true);
	PX_ASSERT(convexMesh);

	PxRigidDynamic* convex = PxCreateDynamic(*mPhysics, PxTransform(pos), PxConvexMeshGeometry(convexMesh), *mMaterial, density); 
	PX_ASSERT(convex);

	SetupDefaultRigidDynamic(*convex);
	mScene->addActor(*convex);
	mPhysicsActors.push_back(convex);

	if(linVel)
		convex->setLinearVelocity(*linVel);

	createRenderObjectsFromActor(convex, material);

	return convex;
}

///////////////////////////////////////////////////////////////////////////////

PxRigidDynamic* PhysXSample::createCompound(const PxVec3& pos, const std::vector<PxTransform>& localPoses, const std::vector<const PxGeometry*>& geometries, const PxVec3* linVel, RenderMaterial* material, PxReal density)
{
	Renderer* renderer = getRenderer();
	PX_ASSERT(renderer);

	PxRigidDynamic* compound = GenerateCompound(*mPhysics, mScene, mMaterial, pos, PxQuat::createIdentity(), localPoses, geometries, false, density);
	mPhysicsActors.push_back(compound);
	if(linVel)
		compound->setLinearVelocity(*linVel);

	createRenderObjectsFromActor(compound, material);

	return compound;
}

PxRigidDynamic* PhysXSample::createTestCompound(const PxVec3& pos, PxU32 nbBoxes, float boxSize, float amplitude, const PxVec3* vel, RenderMaterial* material, PxReal density, bool makeSureVolumeEmpty)
{
	if (makeSureVolumeEmpty)
	{
		// Kai: a little bigger than amplitude + boxSize * sqrt(3)
		PxSphereGeometry geometry(amplitude + boxSize + boxSize);
		PxTransform pose(pos);
		PxShape* hit = NULL;
		PxI32 retVal = getActiveScene().overlapMultiple(geometry, pose,&hit,1);
		if (retVal != 0)
		{
//			printf("desination volume is not empty!!!\n");
			return NULL;
		}
	}

	std::vector<PxTransform> localPoses;
	std::vector<const PxGeometry*> geometries;

	PxToolkit::BasicRandom rnd(42);

	PxBoxGeometryAlloc* geoms = SAMPLE_NEW(PxBoxGeometryAlloc)[nbBoxes];

	for(PxU32 i=0;i<nbBoxes;i++)
	{
		geoms[i].halfExtents = PxVec3(boxSize);

		PxTransform localPose;
		rnd.unitRandomPt(localPose.p);
		localPose.p.normalize();
		localPose.p *= amplitude;
		rnd.unitRandomQuat(localPose.q);

		localPoses.push_back(localPose);
		geometries.push_back(&geoms[i]);
	}
	PxRigidDynamic* actor = createCompound(pos, localPoses, geometries, vel, material, density);
	DELETEARRAY(geoms);
	return actor;
}

///////////////////////////////////////////////////////////////////////////////

struct FindRenderActor
{
	FindRenderActor(PxShape* pxShape): mPxShape(pxShape) {}
	bool operator() (const RenderBaseActor* actor) { return actor->getPhysicsShape() == mPxShape; }
	PxShape* mPxShape;
};

void PhysXSample::removeRenderObject(RenderBaseActor* renderAcotr)
{
		std::vector<RenderBaseActor*>::iterator renderIter = std::find(mRenderActors.begin(), mRenderActors.end(), renderAcotr);
		if(renderIter != mRenderActors.end())
		{
			mDeletedRenderActors.push_back((*renderIter));
			mRenderActors.erase(renderIter);
		}
}

void PhysXSample::removeActor(PxRigidActor* actor)
{
	const PxU32 numShapes = actor->getNbShapes();
	PxShape** shapes = (PxShape**)SAMPLE_ALLOC(sizeof(PxShape*)*numShapes);
	actor->getShapes(shapes, numShapes);
	for(PxU32 i = 0; i < numShapes; i++)
	{
		PxShape* shape = shapes[i];
		FindRenderActor findRenderActor(shape);
		std::vector<RenderBaseActor*>::iterator renderIter = std::find_if(mRenderActors.begin(), mRenderActors.end(), findRenderActor);
		if(renderIter != mRenderActors.end())
		{			
			mDeletedRenderActors.push_back((*renderIter));
			mRenderActors.erase(renderIter);
		}
	}

	// check if the actor is in the active transform list and remove
	if(actor->getType() == PxActorType::eRIGID_DYNAMIC)
	{
		for(PxU32 i=0; i < mActiveTransformCount; i++)
		{
			if(mBufferedActiveTransforms[i].actor == actor)
			{
				mBufferedActiveTransforms[i] = mBufferedActiveTransforms[mActiveTransformCount-1];
				mActiveTransformCount--;
				break;
			}
		}
		mDeletedActors.push_back(actor);
	}

	std::vector<PxRigidActor*>::iterator actorIter = std::find(mPhysicsActors.begin(), mPhysicsActors.end(), actor);
	if(actorIter != mPhysicsActors.end())
	{
		mPhysicsActors.erase(actorIter);
		actor->release();
	}
	SAMPLE_FREE(shapes);
}

///////////////////////////////////////////////////////////////////////////////

SampleFramework::SampleAsset* PhysXSample::getAsset(const char* relativePath, SampleFramework::SampleAsset::Type type, bool abortOnError)
{
	SampleFramework::SampleAsset* asset = mApplication.getAssetManager()->getAsset(relativePath, type);
	if (NULL == asset && abortOnError)
	{
		std::string msg = "Error while getting material asset ";
		msg += relativePath;
		msg += "\n";
		fatalError(msg.c_str());
	}
	return asset;
}

void PhysXSample::importRAWFile(const char* relativePath, PxReal scale, bool recook)
{
	mMeshTag	= 0;
	mFilename	= relativePath;
	mScale		= scale;

	const bool saved = gRecook;
	if(!gRecook && recook)
		gRecook = true;

	bool status = loadRAWfile(getSampleMediaFilename(mFilename), *this, scale);
	if (!status)
	{
		std::string msg = "Sample can not load file ";
		msg += getSampleMediaFilename(mFilename);
		msg += "\n";
		fatalError(msg.c_str());
	}

	gRecook = saved;
}

#if PX_USE_PARTICLE_SYSTEM_API

RenderParticleSystemActor* PhysXSample::createRenderObjectFromParticleSystem(ParticleSystem& ps, RenderMaterial* material)
{
	RenderParticleSystemActor* renderActor = SAMPLE_NEW(RenderParticleSystemActor)(*getRenderer(), &ps, false, true);
	if(material) renderActor->setRenderMaterial(material);

	mRenderActors.push_back(renderActor);
	mRenderParticleSystemActors.push_back(renderActor);
	return renderActor;
}

void PhysXSample::addRenderParticleSystemActor(RenderParticleSystemActor& renderActor)
{
	mRenderActors.push_back(&renderActor);
	mRenderParticleSystemActors.push_back(&renderActor);
}

void PhysXSample::removeRenderParticleSystemActor(RenderParticleSystemActor& renderActor)
{
	std::vector<RenderBaseActor*>::iterator baseActorIter = std::find(mRenderActors.begin(), mRenderActors.end(), (RenderBaseActor*)(&renderActor));
	if(baseActorIter != mRenderActors.end())
		mRenderActors.erase(baseActorIter);

	std::vector<RenderParticleSystemActor*>::iterator psActorIter = std::find(mRenderParticleSystemActors.begin(), mRenderParticleSystemActors.end(), &renderActor);
	if(psActorIter != mRenderParticleSystemActors.end())
		mRenderParticleSystemActors.erase(psActorIter);
}

#endif // PX_USE_PARTICLE_SYSTEM_API

