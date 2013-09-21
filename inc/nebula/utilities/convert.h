#ifndef _CORE_PHYSX_COVERT_H
#define _CORE_PHYSX_COVERT_H

#include <PxPhysicsAPI.h>

#include <boost/numeric/ublas/vector.hpp>


physx::PxVec3 boost_to_PxVec3( const boost::numeric::ublas::vector<float>& v );


#endif







