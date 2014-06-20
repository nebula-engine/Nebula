
#include <Nebula/util/terminal.hpp>
#include <Nebula/util/command_set.hpp>

neb::util::stringstream::stringstream(sp::shared_ptr<neb::util::__terminal_data> t): t_(t) {
	assert(t_);
}
neb::util::stringstream::stringstream(neb::util::stringstream&& ss):
	t_(::std::move(ss.t_))
{}
neb::util::stringstream::~stringstream() {
	if(t_) {
		t_->lines_.push_back(t_->ss_.str());
		t_->ss_.str(::std::string());
	}
}





neb::util::terminal::terminal():
	lines_max_(10)
{}
void					neb::util::terminal::push(char c) {
	line_.push_back(c);
}
int					neb::util::terminal::enter() {

	auto self = sp::dynamic_pointer_cast<neb::util::terminal>(shared_from_this());
	
	operator<<("$ ") << line_;
	
	//neb::app::base::global()->command(self, line_);
	
	if(cs_) {
		(*cs_)(self, line_);
	} else {
		operator<<("no command set.");
	}

	line_.clear();

	while(lines_.size() > lines_max_) {
		lines_.pop_front();
	}

	return 1;
}



