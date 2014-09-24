#ifndef NEB_CORE_INPUT_SINK_HPP
#define NEB_CORE_INPUT_SINK_HPP

#include <boost/signals2.hpp>

#include <gal/itf/shared.hpp>

namespace neb { namespace core { namespace input {

	class source;

	class sink:
		virtual public gal::itf::shared
	{
		public:
			virtual ~sink();

			void		connectKeyFun(std::shared_ptr<neb::core::input::source> const & src, int i);
			void		connectCharFun(std::shared_ptr<neb::core::input::source> const & src, int i);
			void		connectMouseButtonFun(std::shared_ptr<neb::core::input::source> const & src, int i);

			virtual int			mouseButtonFun(
					std::shared_ptr<neb::core::input::source> const &,
					int button,
					int action,
					int mods);
			virtual int			keyFun(
					std::shared_ptr<neb::core::input::source> const &,
					int,
					int,
					int,
					int);
			virtual int			charFun(
					std::shared_ptr<neb::core::input::source> const &,
					unsigned int codepoint);

			// connections
			struct
			{
				boost::signals2::connection		mouse_button_fun_;
				boost::signals2::connection		key_fun_;
				boost::signals2::connection		charFun_;
			} conns_;
	};

}}}

#endif

