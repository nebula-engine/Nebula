
#include <Nebula/util/terminal.hpp>
#include <Nebula/util/command_set.hpp>


neb::util::terminal::terminal():
	lines_max_(10)
{}

void					neb::util::terminal::operator<<(::std::string s) {
	lines_.push_back(s);
}
void					neb::util::terminal::operator<<(char c) {
	line_.push_back(c);
}
int					neb::util::terminal::enter() {

	auto self = sp::dynamic_pointer_cast<neb::util::terminal>(shared_from_this());

	operator<<("$ " + line_);
	
	//neb::app::base::global()->command(self, line_);
	assert(cs_);
	(*cs_)(self, line_);

	line_.clear();

	while(lines_.size() > lines_max_) {
		lines_.pop_front();
	}

	return 1;
}



