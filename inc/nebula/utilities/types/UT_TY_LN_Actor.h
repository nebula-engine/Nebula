#ifndef __TYPES_LINK_ACTOR_INCLUDED__
#define __TYPES_LINK_ACTOR_INCLUDED__

template <class A> class Ptr;
template <class A, class B> class Link;

#include <utilities/Types/UT_TY_Types.h>

typedef Link<Ptr<CO_AC_AD_ActorBase>,		Ptr<CO_AC_AD_Actor> >			L__CO_AC_AD_Actor;
typedef Link<Ptr<CO_AC_PH_ActorBase>,		Ptr<CO_AC_PH_Actor> >			L__CO_AC_PH_Actor;
typedef Link<Ptr<CO_AC_RE_ActorBase>,		Ptr<CO_AC_RE_Actor> >			L__CO_AC_RE_Actor;

typedef Link<Ptr<L__CO_AC_AD_Actor>,		Ptr<CO_AC_AD_RigidActor> >		L__CO_AC_AD_RigidActor;
typedef Link<Ptr<L__CO_AC_PH_Actor>,		Ptr<CO_AC_PH_RigidActor> >		L__CO_AC_PH_RigidActor;
typedef Link<Ptr<L__CO_AC_RE_Actor>,		Ptr<CO_AC_RE_RigidActor> >		L__CO_AC_RE_RigidActor;

typedef Link<Ptr<L__CO_AC_AD_RigidActor>,	Ptr<CO_AC_AD_RigidBody> >		L__CO_AC_AD_RigidBody;
typedef Link<Ptr<L__CO_AC_PH_RigidActor>,	Ptr<CO_AC_PH_RigidBody> >		L__CO_AC_PH_RigidBody;
typedef Link<Ptr<L__CO_AC_RE_RigidActor>,	Ptr<CO_AC_RE_RigidBody> >		L__CO_AC_RE_RigidBody;

typedef Link<Ptr<L__CO_AC_AD_RigidBody>,	Ptr<CO_AC_AD_RigidDynamic> >	L__CO_AC_AD_RigidDynamic;
typedef Link<Ptr<L__CO_AC_PH_RigidBody>,	Ptr<CO_AC_PH_RigidDynamic> >	L__CO_AC_PH_RigidDynamic;
typedef Link<Ptr<L__CO_AC_RE_RigidBody>,	Ptr<CO_AC_RE_RigidDynamic> >	L__CO_AC_RE_RigidDynamic;

typedef Link<Ptr<L__CO_AC_AD_RigidDynamic>,	Ptr<CO_AC_AD_RigidDynamicBox> >	L__CO_AC_AD_RigidDynamicBox;
typedef Link<Ptr<L__CO_AC_PH_RigidDynamic>,	Ptr<CO_AC_PH_RigidDynamicBox> >	L__CO_AC_PH_RigidDynamicBox;
typedef Link<Ptr<L__CO_AC_RE_RigidDynamic>,	Ptr<CO_AC_RE_RigidDynamicBox> >	L__CO_AC_RE_RigidDynamicBox;

typedef Link<Ptr<CO_AC_AD_ActorBase>,		Ptr<CO_AC_AD_Controller> >		L__CO_AC_AD_Controller;
typedef Link<Ptr<CO_AC_PH_ActorBase>,		Ptr<CO_AC_PH_Controller> >		L__CO_AC_PH_Controller;
typedef Link<Ptr<CO_AC_RE_ActorBase>,		Ptr<CO_AC_RE_Controller> >		L__CO_AC_RE_Controller;



#endif





