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



			jess::shared_ptr<bc0x300::universe::admin::base>	universe_;
			jess::shared_ptr<bc0x300::scene::admin::base>		scene_;
			jess::shared_ptr<ncvah::base>				view_human_;
			jess::shared_ptr<ncaa::rigid_dynamic_box>		m_rigidDynamicBox;
			jess::shared_ptr<ncaa::rigid_static_plane>		m_rigidStaticPlane;
			jess::shared_ptr<ncaa::controller>			m_controller;

		};
	}
}


#endif



