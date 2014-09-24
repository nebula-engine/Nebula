#include <iostream>


#include <gal/itf/shared.hpp>

#include <gal/dll/deleter.hpp>

#include <gal/dll/helper.hpp>

gal::dll::deleter::~deleter()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}


gal::dll::deleter::deleter(
		std::shared_ptr<helper_base> h,
		helper_info hi):
	_M_helper(h),
	hi_(hi)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	assert(h);
	
	std::cout << "name " << hi_.name << std::endl;
	std::cout << "hc   " << hi_.hc << std::endl;
}

gal::dll::deleter::deleter(deleter const & d):
	_M_helper(d._M_helper),
	hi_(d.hi_)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::cout << "name " << hi_.name << std::endl;
	std::cout << "hc   " << hi_.hc << std::endl;
}
gal::dll::deleter::deleter(deleter&& d):
	_M_helper(std::move(d._M_helper)),
	hi_(std::move(d.hi_))
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::cout << "name " << hi_.name << std::endl;
	std::cout << "hc   " << hi_.hc << std::endl;
}



void			gal::dll::deleter::operator()(gal::itf::shared* p) {
	p->release();
	_M_helper->destroy(p);
}

gal::dll::helper_info const	gal::dll::deleter::getHelperInfo()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::cout << "name " << hi_.name << std::endl;
	std::cout << "hc   " << hi_.hc << std::endl;


	return hi_;
}

