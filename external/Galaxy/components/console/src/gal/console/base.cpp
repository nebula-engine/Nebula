
#include <gal/console/base.hpp>

<<<<<<< HEAD

=======
void	gal::console::__base::release()
{
}
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

gal::console::base::base()
{}
void					gal::console::base::push(char c) {
	char ch[2];
	ch[0] = c;
	ch[1] = 0;
	line_.insert(ch);
}




