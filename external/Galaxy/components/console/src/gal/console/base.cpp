
#include <gal/console/base.hpp>



gal::console::base::base()
{}
void					gal::console::base::push(char c) {
	char ch[2];
	ch[0] = c;
	ch[1] = 0;
	line_.insert(ch);
}




