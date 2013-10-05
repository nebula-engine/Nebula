#ifndef _SAMPLE_H
#define _SAMPLE_H

//#include <NebulaAPI.h>

#include <nebula/api.hpp>

#include <nebula/framework/app.hpp>

#include <box_client/util/types/content/types.hpp>

#include <box_client/ns.hpp>

namespace box_client
{
	namespace framework
	{
		class app:
			public nf::app
		{
		public:
			app();
			void							init();



			boost::shared_ptr<bc0x300::universe::admin::base>	universe_;
			boost::shared_ptr<bc0x300::scene::admin::base>		scene_;
			boost::shared_ptr<ncvah::base>				view_human_;
			boost::shared_ptr<ncaa::rigid_dynamic_box>		m_rigidDynamicBox;
			boost::shared_ptr<ncaa::rigid_static_plane>		m_rigidStaticPlane;
			boost::shared_ptr<ncaa::controller>			m_controller;

		};
	}
}


#endif



