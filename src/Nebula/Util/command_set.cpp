
#include <Nebula/util/terminal.hpp>
#include <Nebula/util/command.hpp>
#include <Nebula/util/command_set.hpp>


void		neb::util::command_set::init() {

	// default help command
	auto help = sp::make_shared<neb::util::command>();

	help->func_ = [&] (sp::shared_ptr<neb::util::terminal> term, bpo::variables_map vm) {

		list_commands(term);

	};

	map_["help"] = help;

}
void		neb::util::command_set::list_commands(sp::shared_ptr<neb::util::terminal> term) {

	for(auto item : map_) {
		term->operator<<(item.first);
	}

}
void	neb::util::command_set::operator()(sp::shared_ptr<neb::util::terminal> term, ::std::string str) {

	::std::istringstream iss(str);

	::std::vector< ::std::string > tokens;

	::std::copy(
			::std::istream_iterator< ::std::string >(iss),
			::std::istream_iterator< ::std::string >(),
			::std::back_inserter< ::std::vector< ::std::string > >(tokens));

	if(tokens.empty()) return;

	int ac = tokens.size();
	char const ** av = new char const *[ac];
	char const ** pc = av;
	for(auto t : tokens) {
		*pc = t.c_str();
		pc++;
	}



	// find command
	auto it = map_.find(tokens.front());

	if(it != map_.end()) {
		it->second->operator()(term,ac,av);
	} else {
		(*term) << (tokens.front() + ": Command not found.");
	}
}





