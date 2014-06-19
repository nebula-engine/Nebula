#ifndef NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_REMOTE_HH
#define NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_REMOTE_HH

#include <Nebula/Actor/Actor/Remote.hh>
#include <Nebula/Actor/RigidActor/Base.hh>

namespace neb { namespace core { namespace actor { namespace rigidactor {



		class remote:
			virtual public neb::core::actor::rigidactor::base,
			virtual public neb::core::actor::actor::remote
		{
			public:
				remote(sp::shared_ptr<neb::core::actor::util::parent> parent);

				virtual void		step(neb::core::TimeStep const & ts);
		};




}}}}

#endif





