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

#include "PxFoundation.h"
#include "PxPhysicsAPI.h"
#include "PxExtensionsAPI.h"
#include "PxTkStream.h"

#include "RepXUtility.h"
#include "PxStringTableExt.h"

#include "PxTkRepX.h"

using namespace PxToolkit;

RepXCollection* PxToolkit::loadCollection(const char* filename)
{
	PxToolkit::FileInputData data(filename);
	if(!data.isValid())
		return NULL;

	return physx::repx::createCollection(data,  PxGetFoundation().getAllocatorCallback());
}

void PxToolkit::saveCollection(const char* filename, RepXCollection& inCollection)
{
	PxToolkit::FileOutputStream theStream(filename);
	inCollection.save(theStream);
}

void PxToolkit::saveSceneToRepX(const char* inFileName, PxPhysics& physics, PxScene& scene)
{
	RepXCollection* collection = createCollection(physics);

	saveSceneToRepX(physics, scene, *collection);
	saveCollection(inFileName, *collection);
	collection->destroy();
}

void PxToolkit::loadSceneFromRepX( const char* inFileName, PxPhysics& physics, PxCooking& cooking, PxScene& scene)
{
	PxStringTable* stringTable = &PxStringTableExt::createStringTable(  PxGetFoundation().getAllocatorCallback() );
	RepXCollection* collection = loadCollection(inFileName);

	addObjectsToScene( *collection, physics, cooking, scene, stringTable );
	
	collection->destroy();
	stringTable->release();
}