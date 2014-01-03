#ifndef __NEBULA_CONFIG_H__
#define __NEBULA_CONFIG_H__

#define NEB_INSTALL_DIR "/usr/local"

#define NEBULA_DEBUG_0_FUNCTION printf("%s\n", __PRETTY_FUNCTION__);
#define NEBULA_DEBUG_1_FUNCTION

#include <memory>

namespace neb
{
	class shape;
	
	namespace actor
	{
		class Base;
		typedef std::shared_ptr<Base> Base_shared;
		typedef std::shared_ptr<Base> Base_weak;
	}
}

#endif
