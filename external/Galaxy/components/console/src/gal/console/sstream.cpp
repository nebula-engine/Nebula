
#include <gal/console/sstream.hpp>

gal::console::stringstream::stringstream(std::shared_ptr<gal::console::__base> b): b_(b) {
	assert(b_);
}
gal::console::stringstream::stringstream(gal::console::stringstream&& ss):
	b_(::std::move(ss.b_))
{}
gal::console::stringstream::~stringstream() {

	
	
	if(b_) {

		::std::cout << 'x';

		b_->write_line(b_->ss_.str()); //b_->lines_.push_back(b_->ss_.str());
		b_->ss_.str(::std::string());
	}
}



