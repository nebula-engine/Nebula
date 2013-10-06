#ifndef __NEBULA_CONTENT_SHAPE_PHYSICS_PHYSX_BOX_HPP__
#define __NEBULA_CONTENT_SHAPE_PHYSICS_PHYSX_BOX_HPP__



namespace ncs = nebula::content::shape;

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace physics
			{
				namespace physx
				{
					class box
					{
					public:
						box();
						~box();
						void							init(const jess::shared_ptr<ncs::admin::box>&);
						void							shutdown();
						void							create_shape();
						
						/// parent
						std::weak_ptr<ncs::admin::box>				parent_;

						/// PxShape
						::physx::PxShape*					px_shape_;
					};
				}
			}
		}
	}
}

#endif
