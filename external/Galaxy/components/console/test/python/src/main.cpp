
#include <gal/console/backend/python.hpp>
#include <gal/console/frontend/stdio.hpp>
#include <gal/console/temp.hpp>

using namespace std;

int main() {

	auto t = make_shared< gal::console::temp<gal::console::backend::python, gal::console::frontend::stdio> >();

	t->init();

	//t->push('h');

	//t->enter();

	t->loop();

	return 0;
}

