

#include "SampleCamera.h"
#include "SampleUtils.h"
#include "RenderPhysX3Debug.h"
#include "RendererColor.h"

using namespace SampleRenderer;

// PT: the base camera code should be the same for all cameras, regardless of how
// the camera is controlled. For example this should deal with VFC, etc.

				Camera::Camera() :
	mProjMatrix		(degtorad(45.0f), 1.0f, 1.0f, 100.0f),
	mFOV			(0.0f),
	mNearPlane		(0.0f),
	mFarPlane		(0.0f),
	mDirtyProj		(true),
	mDirtyView		(true)
{
	mViewMatrix		= PxTransform::createIdentity();
	mPos	= PxVec3(0);
	mRot	= PxVec3(0);

	mDrawDebugData	= false;
	mFreezeFrustum	= false;
	mPerformVFC		= false;
}

				Camera::~Camera()
{
}

void			Camera::updateInternals()
{
	if(mDirtyProj)
	{
		mDirtyProj	= false;
		mProjMatrix = RendererProjection(degtorad(mFOV), mViewport.computeRatio(), mNearPlane, mFarPlane);
	}
	if(mDirtyView)
	{
		mDirtyView	= false;

		mViewMatrix.q	= PxQuat(EulerToMat33(mRot));
		mViewMatrix.p	= mPos;
	}
}

PxVec3			Camera::getViewDir() const
{
	const PxTransform& camPose = getViewMatrix();
	PxVec3 forward = PxMat33(camPose.q)[2];
	return -forward;
}

void			Camera::lookAt(const PxVec3& position, const PxVec3& target)
{
	PxVec3 dir = target - position;
	dir.normalize();

	PxVec3 right, up;
	computeBasis(dir, right, up);

	PxTransform view;
	view.p	= position;
	view.q	= PxQuat(PxMat33(-right, up, -dir));
	setView(view);
}

void			Camera::BuildFrustum()
{
	if(mFreezeFrustum)
		return;

	// PT: a better way is to extract the planes from the view-proj matrix but it has some subtle differences with D3D/GL.
	// Building the frustum explicitly is just easier here (although not as efficient)

	const PxReal ratio		= mViewport.computeRatio();

	const PxReal Tan		= tanf(degtorad(0.5f * mFOV)) / ratio;

	const PxReal nearCoeff	= mNearPlane * Tan;
	const PxReal farCoeff	= mFarPlane * Tan;

	const PxReal rightCoeff = ratio;
	const PxReal upCoeff	= 1.0f;

	const PxTransform& view = getViewMatrix();
	PxMat33 mat33(view.q);
	PxVec3 right	= mat33[0];
	PxVec3 up		= mat33[1];
	PxVec3 forward	=-mat33[2];

	mFrustum[0] = mPos + forward*mNearPlane - right*nearCoeff*rightCoeff + up*nearCoeff*upCoeff;
	mFrustum[1] = mPos + forward*mNearPlane - right*nearCoeff*rightCoeff - up*nearCoeff*upCoeff;
	mFrustum[2] = mPos + forward*mNearPlane + right*nearCoeff*rightCoeff - up*nearCoeff*upCoeff;
	mFrustum[3] = mPos + forward*mNearPlane + right*nearCoeff*rightCoeff + up*nearCoeff*upCoeff;

	mFrustum[4] = mPos + forward*mFarPlane - right*farCoeff*rightCoeff + up*farCoeff*upCoeff;
	mFrustum[5] = mPos + forward*mFarPlane - right*farCoeff*rightCoeff - up*farCoeff*upCoeff;
	mFrustum[6] = mPos + forward*mFarPlane + right*farCoeff*rightCoeff - up*farCoeff*upCoeff;
	mFrustum[7] = mPos + forward*mFarPlane + right*farCoeff*rightCoeff + up*farCoeff*upCoeff;

	if(0)
	{
		mPlanes[0] = PxPlane(mFrustum[4], mFrustum[1], mFrustum[5]);
		mPlanes[1] = PxPlane(mFrustum[3], mFrustum[6], mFrustum[2]);
		mPlanes[2] = PxPlane(mFrustum[4], mFrustum[3], mFrustum[0]);
		mPlanes[3] = PxPlane(mFrustum[1], mFrustum[6], mFrustum[5]);
		mPlanes[4] = PxPlane(mFrustum[0], mFrustum[2], mFrustum[1]);
		mPlanes[5] = PxPlane(mFrustum[5], mFrustum[7], mFrustum[4]);

		{
			for(int i=0;i<6;i++)
			{
				mPlanes[i].n = -mPlanes[i].n;
				mPlanes[i].d = -mPlanes[i].d;
			}
		}
	}

	if(1)
	{
		//
		const PxVec3 axisX(1.0f, 0.0f, 0.0f);
		const PxVec3 axisY(0.0f, 1.0f, 0.0f);
		const PxVec3 axisZ(0.0f, 0.0f, 1.0f);

		PxQuat RotX(degtorad(0.5f * mFOV), axisX);
		PxQuat RotY(degtorad(0.5f * mFOV), axisY);
		PxQuat RotZ(degtorad(0.5f * mFOV), axisZ);

		PxVec3 tmp1 = RotY.rotate(-axisX);
		PxVec3 tmp11 = view.q.rotate(tmp1);	// Plane0
		mPlanes[0].n = tmp11;
		mPlanes[0].d = - mPos.dot(mPlanes[0].n);
		//

		RotY = PxQuat(-degtorad(0.5f * mFOV), axisY);

		PxVec3 tmpy = RotY.rotate(axisX);
		PxVec3 tmpyy = view.q.rotate(tmpy);	// Plane1
		mPlanes[1].n = tmpyy;
		mPlanes[1].d = - mPos.dot(mPlanes[1].n);

		//

		RotX = PxQuat(degtorad(0.5f * mFOV)/ratio, axisX);
		PxVec3 tmpx = RotX.rotate(axisY);
		PxVec3 tmpxx = view.q.rotate(tmpx);		// Plane2?
		mPlanes[2].n = tmpxx;
		mPlanes[2].d = - mPos.dot(mPlanes[2].n);

		//

		RotX = PxQuat(-degtorad(0.5f * mFOV)/ratio, axisX);
		tmpx = RotX.rotate(axisY);
		tmpxx = view.q.rotate(tmpx);		// -Plane3?
		mPlanes[3].n = -tmpxx;
		mPlanes[3].d = - mPos.dot(mPlanes[3].n);

		//

		mPlanes[4].n = -forward;
		mPlanes[4].d = - (mPos.dot(mPlanes[4].n) + forward.dot(mPlanes[4].n)*mNearPlane);

		mPlanes[5].n = forward;
		mPlanes[5].d = - (mPos.dot(mPlanes[5].n) + forward.dot(mPlanes[5].n)*mFarPlane);
	}


	if(0)
	{
		PxMat44 proj44 = convertProjMatrix(mProjMatrix);
		PxMat44 view44 = convertViewMatrix(view);
//		PxMat44 combo44 = view44 * proj44;
		PxMat44 combo44 = proj44 * view44;

		PxReal combo[4][4];
		PxReal* dst = &combo[0][0];
		memcpy(dst, &combo44, sizeof(PxReal)*16);

		// D3D:
		// -w' < x' < w'
		// -w' < y' < w'
		// 0 < z' < w'
		//
		// GL:
		// -w' < x' < w'
		// -w' < y' < w'
		// -w' < z' < w'

		// Left clipping plane
		mPlanes[FRUSTUM_PLANE_LEFT].n.x	= -(combo[0][3] + combo[0][0]);
		mPlanes[FRUSTUM_PLANE_LEFT].n.y	= -(combo[1][3] + combo[1][0]);
		mPlanes[FRUSTUM_PLANE_LEFT].n.z	= -(combo[2][3] + combo[2][0]);
		mPlanes[FRUSTUM_PLANE_LEFT].d	= -(combo[3][3] + combo[3][0]);

		// Right clipping plane
		mPlanes[FRUSTUM_PLANE_RIGHT].n.x	= -(combo[0][3] - combo[0][0]);
		mPlanes[FRUSTUM_PLANE_RIGHT].n.y	= -(combo[1][3] - combo[1][0]);
		mPlanes[FRUSTUM_PLANE_RIGHT].n.z	= -(combo[2][3] - combo[2][0]);
		mPlanes[FRUSTUM_PLANE_RIGHT].d		= -(combo[3][3] - combo[3][0]);

		// Top clipping plane
		mPlanes[FRUSTUM_PLANE_TOP].n.x	= -(combo[0][3] - combo[0][1]);
		mPlanes[FRUSTUM_PLANE_TOP].n.y	= -(combo[1][3] - combo[1][1]);
		mPlanes[FRUSTUM_PLANE_TOP].n.z	= -(combo[2][3] - combo[2][1]);
		mPlanes[FRUSTUM_PLANE_TOP].d	= -(combo[3][3] - combo[3][1]);

		// Bottom clipping plane
		mPlanes[FRUSTUM_PLANE_BOTTOM].n.x	= -(combo[0][3] + combo[0][1]);
		mPlanes[FRUSTUM_PLANE_BOTTOM].n.y	= -(combo[1][3] + combo[1][1]);
		mPlanes[FRUSTUM_PLANE_BOTTOM].n.z	= -(combo[2][3] + combo[2][1]);
		mPlanes[FRUSTUM_PLANE_BOTTOM].d		= -(combo[3][3] + combo[3][1]);

		// Near clipping plane
		if(1)
		{
			// OpenGL path
			mPlanes[FRUSTUM_PLANE_NEAR].n.x	= -(combo[0][3] + combo[0][2]);
			mPlanes[FRUSTUM_PLANE_NEAR].n.y	= -(combo[1][3] + combo[1][2]);
			mPlanes[FRUSTUM_PLANE_NEAR].n.z	= -(combo[2][3] + combo[2][2]);
			mPlanes[FRUSTUM_PLANE_NEAR].d	= -(combo[3][3] + combo[3][2]);
		}
		else
		{
			// D3D path
			mPlanes[FRUSTUM_PLANE_NEAR].n.x	= - combo[0][2];
			mPlanes[FRUSTUM_PLANE_NEAR].n.y	= - combo[1][2];
			mPlanes[FRUSTUM_PLANE_NEAR].n.z	= - combo[2][2];
			mPlanes[FRUSTUM_PLANE_NEAR].d	= - combo[3][2];
		}

		// Far clipping plane (must be last for infinite far clip)
		mPlanes[FRUSTUM_PLANE_FAR].n.x	= -(combo[0][3] - combo[0][2]);
		mPlanes[FRUSTUM_PLANE_FAR].n.y	= -(combo[1][3] - combo[1][2]);
		mPlanes[FRUSTUM_PLANE_FAR].n.z	= -(combo[2][3] - combo[2][2]);
		mPlanes[FRUSTUM_PLANE_FAR].d	= -(combo[3][3] - combo[3][2]);

		// Normalize if needed
		for(PxU32 i=0;i<6;i++)
		{
//			mPlanes[i].normalize();
			mPlanes[i].n.normalize();
//			mPlanes[i].normal = -mPlanes[i].normal;
//			mPlanes[i].d = -mPlanes[i].d;
			mPlanes[i].d *= 0.5f;
		}
	}
}

PlaneAABBCode	Camera::cull(const PxBounds3& aabb) const
{
	// Following code from Umbra/dPVS.

	//------------------------------------------------------------------------
	//
	// Function:        DPVS::intersectAABBFrustum()
	//
	// Description:     Determines whether an AABB intersects a frustum
	//
	// Parameters:      a           = reference to AABB (defined by minimum & maximum vectors)
	//                  p           = array of pre-normalized clipping planes
	//                  outClipMask = output clip mask (if function returns 'true')
	//                  inClipMask  = input clip mask (indicates which planes are active)
	//
	// Returns:         true if AABB intersects the frustum, false otherwise
	//
	//                  Intersection of AABB and a frustum. The frustum may 
	//                  contain 0-32 planes (active planes are defined by inClipMask). 
	//                  If AABB intersects the frustum, an output clip mask is returned 
	//                  as well (indicating which planes are crossed by the AABB). This 
	//                  information can be used to optimize testing of child nodes or 
	//                  objects inside the nodes (pass value as 'inClipMask' next time).
	//
	//                  This is a variant of the classic "fast" AABB/frustum 
	//                  intersection tester. AABBs that are not culled away by any single 
	//                  plane are classified as "intersecting" even though the AABB may 
	//                  actually be outside the convex volume formed by the planes.
	//------------------------------------------------------------------------
	
	const PxU32 nbFrustumPlanes		= 6;	// PT: can sometimes be 5 with infinite far clip plane
	const PxU32 frustumPlanesMask	= (1<<nbFrustumPlanes)-1;

	PxU32 outClipMask;
	if(!planesAABBOverlap(aabb, mPlanes, outClipMask, frustumPlanesMask))
		return PLANEAABB_EXCLUSION;

	if(outClipMask)
		return PLANEAABB_INTERSECT;

	return PLANEAABB_INCLUSION;
}

void			Camera::drawDebug(RenderPhysX3Debug* debug)
{
	if(mDrawDebugData)
	{
/*		for(PxU32 i=0;i<8;i++)
		{
			debug->addLine(mFrustum[i], mFrustum[i]+PxVec3(1,0,0), RendererColor(255,0,0));
			debug->addLine(mFrustum[i], mFrustum[i]+PxVec3(0,1,0), RendererColor(0, 255,0));
			debug->addLine(mFrustum[i], mFrustum[i]+PxVec3(0,0,1), RendererColor(0, 0, 255));
		}*/

		const RendererColor lineColor(255, 255, 0);
		debug->addLine(mFrustum[0], mFrustum[1], lineColor);
		debug->addLine(mFrustum[1], mFrustum[2], lineColor);
		debug->addLine(mFrustum[2], mFrustum[3], lineColor);
		debug->addLine(mFrustum[3], mFrustum[0], lineColor);

		debug->addLine(mFrustum[4], mFrustum[5], lineColor);
		debug->addLine(mFrustum[5], mFrustum[6], lineColor);
		debug->addLine(mFrustum[6], mFrustum[7], lineColor);
		debug->addLine(mFrustum[7], mFrustum[4], lineColor);

		debug->addLine(mFrustum[0], mFrustum[4], lineColor);
		debug->addLine(mFrustum[3], mFrustum[7], lineColor);
		debug->addLine(mFrustum[1], mFrustum[5], lineColor);
		debug->addLine(mFrustum[6], mFrustum[2], lineColor);
	}
}

// Projection part

PX_FORCE_INLINE	PxReal	Camera::getFOV()			const
{ return mFOV;						}
PX_FORCE_INLINE	PxReal	Camera::getNearPlane()		const
{ return mNearPlane;				}
PX_FORCE_INLINE	PxReal	Camera::getFarPlane()		const
{ return mFarPlane;					}
PX_FORCE_INLINE	PxU32	Camera::getScreenWidth()	const
{ return mViewport.mClientWidth;	}
PX_FORCE_INLINE	PxU32	Camera::getScreenHeight()	const
{ return mViewport.mClientHeight;	}
PX_FORCE_INLINE	void	Camera::setFOV(PxReal fov)
{ mFOV			= fov;	mDirtyProj = true;	}
PX_FORCE_INLINE	void	Camera::setNearPlane(PxReal d)	
{ mNearPlane	= d;	mDirtyProj = true;	}
PX_FORCE_INLINE	void	Camera::setFarPlane(PxReal d)
{ mFarPlane		= d;	mDirtyProj = true;	}
PX_FORCE_INLINE	void	Camera::setScreenSize(PxU32 clientWidth, PxU32 clientHeight, PxU32 windowWidth, PxU32 windowHeight)
{
	mViewport.mClientWidth	= clientWidth;
	mViewport.mClientHeight	= clientHeight;
	mViewport.mWindowWidth	= windowWidth;
	mViewport.mWindowHeight	= windowHeight;
	mDirtyProj				= true;
}

PX_FORCE_INLINE	const SampleRenderer::RendererProjection& getProjMatrix()		const
{
	if(mDirtyProj)
		const_cast<Camera*>(this)->updateInternals();

	return mProjMatrix;
}

// View part

PX_FORCE_INLINE	const	PxVec3&			getPos()					const
{ return mPos;								}
PX_FORCE_INLINE	const	PxVec3&			getRot()					const
{ return mRot;								}
PX_FORCE_INLINE			void			setRot(const PxVec3& rot)
{ mRot = rot;			mDirtyView = true;	}
PX_FORCE_INLINE			void			setView(const PxTransform& view)
{ mViewMatrix = view;	mDirtyView = false;	}
PX_FORCE_INLINE	const	PxTransform&	getViewMatrix()				const
{
	if(mDirtyView)
		const_cast<Camera*>(this)->updateInternals();

	return mViewMatrix;
}
PX_FORCE_INLINE	const	PxVec3*			getFrustumVerts()	const
{ return mFrustum;	}