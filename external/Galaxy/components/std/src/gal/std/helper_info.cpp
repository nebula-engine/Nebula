#include <iostream>

#include <gal/dll/helper_info.hpp>

gal::dll::helper_info::helper_info():
	hc(0)
{

}

gal::dll::helper_info::helper_info(std::string f, std::string o, std::type_index nti):
	file_name(f),
	object_name(o)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	name = nti.name();
	hc = nti.hash_code();

	std::cout << "name " << name << std::endl;
	std::cout << "hc   " << hc << std::endl;
}

gal::dll::helper_info::helper_info(gal::dll::helper_info const & h):
	file_name(h.file_name),
	object_name(h.object_name)
{
	name = h.name;
	hc = h.hc;
}





	







