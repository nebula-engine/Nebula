#ifndef NEBULA_SIGNALS_HPP
#define NEBULA_SIGNALS_HPP

#include <boost/signals2.hpp>

typedef int ret_type;

namespace Neb {
	namespace Signals {
		typedef boost::signals2::signal<ret_type (int,int,int)>		MouseButtonFun;
		typedef boost::signals2::signal<ret_type (double,double)>	CursorPosFun;
		typedef boost::signals2::signal<ret_type (int)>			CursorEnterFun;
		typedef boost::signals2::signal<ret_type (double,double)>	ScrollFun;
		typedef boost::signals2::signal<ret_type (int,int,int,int)>	KeyFun;
		typedef boost::signals2::signal<ret_type (unsigned int)>	CharFun;
	}
}


#endif

