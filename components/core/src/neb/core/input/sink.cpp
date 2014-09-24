
#include <neb/core/util/log.hpp>
#include <neb/core/input/sink.hpp>
#include <neb/core/input/source.hpp>


typedef neb::core::input::sink THIS;

THIS::~sink()
{
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__ << " " << this;
}
void		THIS::connectKeyFun(std::shared_ptr<neb::core::input::source> const & src, int i)
{
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__ << " " << this;

	conns_.key_fun_ = src->sig_.keyFun_.connect(
			i,
			neb::core::input::signals::KeyFun::slot_type(
				&THIS::keyFun,
				this,
				_1,
				_2,
				_3,
				_4,
				_5
				).track_foreign(shared_from_this())
			);
}
void		THIS::connectCharFun(std::shared_ptr<neb::core::input::source> const & src, int i)
{
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__ << " " << this;

	conns_.charFun_ = src->sig_.charFun_.connect(
			i,
			neb::core::input::signals::CharFun::slot_type(
				&THIS::charFun,
				this,
				_1,
				_2
				).track_foreign(shared_from_this())
			);
}
void		THIS::connectMouseButtonFun(std::shared_ptr<neb::core::input::source> const & src, int i)
{
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__ << " " << this;

	conns_.mouse_button_fun_ = src->sig_.mouseButtonFun_.connect(
			i,
			neb::core::input::signals::MouseButtonFun::slot_type(
				&THIS::mouseButtonFun,
				this,
				_1,
				_2,
				_3,
				_4
				).track_foreign(shared_from_this())
			);

}



int			THIS::mouseButtonFun(
		std::shared_ptr<neb::core::input::source> const &,
		int button,
		int action,
		int mods)
{
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__ << " " << this;
	return 0;
}
int			THIS::keyFun(
		std::shared_ptr<neb::core::input::source> const &,
		int,
		int,
		int,
		int)
{
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__ << " " << this;
	return 0;
}
int			THIS::charFun(
		std::shared_ptr<neb::core::input::source> const &,
		unsigned int codepoint)
{
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__ << " " << this;
	return 0;
}




