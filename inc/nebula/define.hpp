#ifndef __NEBULA_DEFINE_HPP__
#define __NEBULA_DEFINE_HPP__

#include <stdio.h>

#include <assert.h>


// for physx
#if defined(__DEBUG__)
	#define _DEBUG 1
#else
	#define NDEBUG 1
#endif




#ifdef __LIN__
	#define NEB_FUNCSIG __PRETTY_FUNCTION__
#elif defined __WIN__
	#define NEB_FUNCSIG __FUNCSIG__
#else
	#error "must define __WIN__ or __LIN__"
#endif


#define NEB_ASSERT(x)	assert(x)
#define NEB_LOG(x)	printf( x )
#define NEB_LOG_FUNC	printf( "%s\n", NEB_FUNCSIG )


#endif
