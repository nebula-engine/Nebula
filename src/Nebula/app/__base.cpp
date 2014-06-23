#include <thread>

#include <gal/log/log.hpp>

#include <Nebula/app/__base.hpp>

void		neb::app::__base::init() {
	
	BOOST_LOG_CHANNEL_SEV(lg, "neb app", debug) << __PRETTY_FUNCTION__;
	
	if(!flag_.any(neb::app::util::flag::INIT___BASE)) {
		BOOST_LOG_CHANNEL_SEV(lg, "neb app", debug) << "launch ios thread";
	
		std::thread t([&](){
			boost::asio::io_service::work w(ios_);
			ios_.run();

			BOOST_LOG_CHANNEL_SEV(lg, "neb app", debug) << "ios stopped";
		});
		t.detach();

		flag_.set(neb::app::util::flag::INIT___BASE);
	}
}

