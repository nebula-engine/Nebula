// math??? ////////////////////////////////////////////////////////////////////////////////////////

static PxMat44		EulerToMat33(const PxVec3& e)
{
	const float c1 = cosf(e.z);
	const float s1 = sinf(e.z);
	const float c2 = cosf(e.y);
	const float s2 = sinf(e.y);
	const float c3 = cosf(e.x);
	const float s3 = sinf(e.x);
	PxMat44 m;
	m.column0 = PxVec4(c1*c2,              -s1*c2,             s2,	0.0f);
	m.column1 = PxVec4((s1*c3)+(c1*s2*s3), (c1*c3)-(s1*s2*s3),-c2*s3, 0.0f);
	m.column2 = PxVec4((s1*s3)-(c1*s2*c3), (c1*s3)+(s1*s2*c3), c2*c3, 0.0f);
	m.column3 = PxVec4(0,0,0,1);
	return m;
}

static PxVec3		Mat33ToEuler(const PxMat44& m)
{
	const PxF32 epsilon = 0.99999f;
	PxVec3 e, x, y, z;

	x = PxVec3(m.column0.x, m.column1.x, m.column2.x);
	y = PxVec3(m.column0.y, m.column1.y, m.column2.y);
	z = PxVec3(m.column0.z, m.column1.z, m.column2.z);

	if(x.z > epsilon)
	{
		e.x = PxAtan2(z.y, y.y);
		e.y = PxPi * 0.5f;
		e.z = 0;
	}
	else if(x.z < -epsilon)
	{
		e.x = PxAtan2(z.y, y.y);
		e.y = -PxPi * 0.5f;
		e.z = 0;
	}
	else
	{
		e.x = PxAtan2(-y.z, z.z);
		e.y = PxAsin(x.z);
		e.z = PxAtan2(-x.y, x.x);
	}
	return e;
}

inline float		SmoothStepPolynomial( float s )
{
	if( s <= 0 ) return 0;
	if( s >= 1 ) return 1;
	return s*s*(3-2*s);
}

template <typename T> T SmoothStep( const T& start, const T& end, float s )
{
	float ss = SmoothStepPolynomial( s );
	return ss * (end - start) + start;
}

// allocator //////////////////////////////////////////////////////////////////////////////////////

void				initNxAllocator()
{
	PX_ASSERT(!m_Allocator);
	m_Allocator = new PxNxAllocator;
}

void				releaseNxAllocator()
{
	DELETESINGLE(m_Allocator);
}

PxNxAllocator*		getNxAllocator()
{
	PX_ASSERT(m_Allocator);
	return m_Allocator;
}

static	PxNxAllocator* m_Allocator = NULL;

template <typename T> void releaseAll(T& container)
{
	for (PxU32 i = 0; i < container.size(); ++i)
	{
		container[i]->release();
	}

	container.clear();
}


