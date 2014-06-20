
#include <Nebula/util/terminal.hpp>

int main() {
	
	auto t = sp::make_shared<neb::util::terminal>();
	
	(*t) << "hello " << 3;

	t->enter();



	for(auto l : t->lines_) {
		std::cout << l << std::endl;
	}

}

