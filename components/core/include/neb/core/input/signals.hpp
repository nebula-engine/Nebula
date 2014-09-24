#ifndef NEBULA_SIGNALS_HPP
#define NEBULA_SIGNALS_HPP

#include <boost/signals2.hpp>

#include <neb/core/util/combiner.hpp>

namespace neb { namespace core {

	namespace input {
		class source;

		namespace signals
		{
			typedef int							ret_type;
			typedef std::shared_ptr<neb::core::input::source> const &	wnd_type;

			typedef boost::signals2::signal<ret_type (wnd_type, int,int,int),	neb::util::combiner>	MouseButtonFun;
			typedef boost::signals2::signal<ret_type (wnd_type, double,double),	neb::util::combiner>	CursorPosFun;
			typedef boost::signals2::signal<ret_type (wnd_type, int),		neb::util::combiner>	CursorEnterFun;
			typedef boost::signals2::signal<ret_type (wnd_type, double,double),	neb::util::combiner>	ScrollFun;
			typedef boost::signals2::signal<ret_type (wnd_type, int,int,int,int),	neb::util::combiner>	KeyFun;
			typedef boost::signals2::signal<ret_type (wnd_type, unsigned int),	neb::util::combiner>	CharFun;
		}
	}
}}


#endif

