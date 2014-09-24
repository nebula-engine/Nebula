
#include <gal/console/backend/unix.hpp>
#include <gal/console/frontend/stdio.hpp>

class console: virtual public gal::console::unix, virtual public gal::console::frontend::stdio {
};

int main() {
	
	auto t = sp::make_shared<console>();
	
	(*t) << "hello " << 3;
	
	t->push('h');
	
	t->enter();
	
	
	
/*	for(auto l : t->lines_) {
		std::cout << l << std::endl;
	}
*/
}

