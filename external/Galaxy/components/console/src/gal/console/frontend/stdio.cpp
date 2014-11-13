#include <gal/console/frontend/stdio.hpp>


void			gal::console::frontend::stdio::write_line(::std::string const & s) {

	::std::cout << s << ::std::endl;

}
void			gal::console::frontend::stdio::enter() {
	
	//operator<<(prompt_end_) << line_;
	
	eval(line_.container);
	
	line_.clear();
	
	::std::cout << prompt_end_;
	
	return;

}

void			gal::console::frontend::stdio::loop() {

	char c;

	::std::cout << prompt_end_;

	while(1) {

		//std::cout << '(' << (int)c << ')';

		c = ::std::cin.get();

		if(c == -1) {
			//std::cout << "terminate" << std::endl;
			break;
		}


		if(c == 10) {
			enter();
		} else {
			push(c);
		}

	}
}



