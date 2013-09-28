#ifndef __NEBULA_CONTENT_SCENE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_SCENE_ADMIN_BASE_HPP__

#include <ctime>

#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <jess/shared_ptr.hpp>

#include <nebula/utilities/types/content/types.hpp>
#include <nebula/utilities/types/content/scene/types.hpp>
#include <nebula/utilities/types/content/universe/types.hpp>

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
				class base:
					public boost::enable_shared_from_this<nc_sc_a::base>
				{
				public:
					/// ctor
					base();
					/// dtor
					~base();
					
					/// init
					virtual void									init( const boost::shared_ptr<ncua::base>& parent );
					/// shutdown
					virtual void									shutdown();
					/// update
					virtual void									update();
					
					/// get content
					boost::shared_ptr<nebula::content::base>					get_content();
					
					/// parent
					boost::weak_ptr<ncua::base>							parent_;

					/// time of last update
					std::time_t									last_;
					/// step size
					FLOAT										step_size_;
					FLOAT										accumulator_;

					
					jess::shared_ptr<nc_sc_p::base>							physics_;
					jess::shared_ptr<nc_sc_r::base>							renderer_;	
				};
			}
		}
	}
}


#endif
