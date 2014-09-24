#ifndef GAL_CONSOLE_TEMP_HPP
#define GAL_CONSOLE_TEMP_HPP

namespace gal { namespace console {

	template<typename FRONTEND, typename BACKEND> class temp:
		virtual public FRONTEND,
		virtual public BACKEND
	{};

}}

#endif
