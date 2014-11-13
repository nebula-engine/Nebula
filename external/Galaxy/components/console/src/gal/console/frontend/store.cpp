#include <gal/console/frontend/store.hpp>

gal::console::frontend::store::store():
	lines_max_(1000)
{}

void			gal::console::frontend::store::write_line(::std::string const & s) {
	
	lines_.push_back(s);

	while(lines_.size() > lines_max_) {
		lines_.pop_front();
	}
	
	
	
}
void					gal::console::frontend::store::enter() {

	
	operator<<(prompt_end_) << line_.container;
	
	eval(line_.container);
	
	line_.clear();
	
	return;



}
