
#include <boost/version.hpp>

#include <neb/py/core/pose.hpp>
#include <neb/py/core/scene/base.hpp>
#include <neb/py/config.hpp>

/*
#if BOOST_VERSION==105500
#	warning 1_55
#elif BOOST_VERSION==104900
#	warning 1_49
#else
#	error
#endif
*/

BOOST_PYTHON_MODULE(PY_LIB_NAME)
{
	export_pose();
	export_scene();
}

