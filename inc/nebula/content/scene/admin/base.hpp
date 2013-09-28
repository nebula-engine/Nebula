#ifndef __NEBULA_CONTENT_SCENE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_SCENE_ADMIN_BASE_HPP__

#include <boost/shared_ptr.hpp>

#include <nebula/ns.hpp>


namespace nebula
{
	namespace content
	{
		namespace scene
		{
			namespace admin
			{
				/// base
				/*
				* \todo Create trigger object (might need to go in physics). Need to see if PhysX already has an object/functionality for this.
				* 
				*/
				class base
				{
				public:
					/// ctor
					base();
					~base();
					
					/// init
					virtual void									init(const boost::shared_ptr<ncua::base>& parent);
					/// shutdown
					virtual void									shutdown();
					/// update
					virtual void									update();
				};
			}
		}
	}
}


#endif
