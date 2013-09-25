#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_MATERIAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_MATERIAL_HPP__


namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				class material
				{
				public:
					material();
					virtual void						init(const boost::shared_ptr<nebula::content::actor::admin::material>&);
					virtual void						shutdown();
				};
			}
		}
	}
}




#endif

