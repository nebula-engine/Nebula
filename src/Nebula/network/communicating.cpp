#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

//#include <math/free.hpp>

//#include <galaxy/config.hpp>
//#include <gal/free.hpp>

#include <gru/network/message.hpp>
#include <gru/network/communicating.hpp>

gal::network::communicating::communicating( int socket ):
	socket_(socket),
	read_msg_(new gal::network::message),
	terminate_(false)
{
	//GALAXY_DEBUG_0_FUNCTION;
	
	printf("socket = %i\n", socket);
}
void	gal::network::communicating::start()
{
	//GALAXY_DEBUG_0_FUNCTION;
	//printf("lock mutex_start_\n");

	std::unique_lock<std::mutex> lk(mutex_start_);
	
	write_thread_ = std::thread(std::bind(&communicating::thread_write_dispatch, this ) );
	
	//printf("wait for cv_ready_\n");
	cv_ready_.wait(lk);
	
	//printf("cv_ready_ notified\n");
	
	read_thread_ = std::thread(std::bind(&communicating::thread_read, this ) );
}
void		gal::network::communicating::write(boost::shared_ptr<gal::network::message> & msg) {	
	//GALAXY_DEBUG_1_FUNCTION;
	
	{
		std::lock_guard<std::mutex> lk(mutex_);
		
		// take ownership of the message
		write_queue_.push_back( std::move(msg) );
	}
	
	//printf("notify one\n");
	
	cv_.notify_one();
}
void	gal::network::communicating::close() {	
	//GALAXY_DEBUG_0_FUNCTION;
	
	{
		std::lock_guard<std::mutex> lk( mutex_ );

		terminate_ = true;
	}
	cv_.notify_all();

	write_thread_.join();
	read_thread_.join();

	::close( socket_ );
}
void	gal::network::communicating::thread_write_dispatch() {
	//GALAXY_DEBUG_1_FUNCTION;
	
	//printf("lock mutex_start_\n");

	mutex_start_.lock();

	//printf("unlock mutex_start_\n");
	mutex_start_.unlock();
	
	//printf("lock mutex_\n");
	std::unique_lock<std::mutex> lk(mutex_);
	
	//printf("cv_ready_.notify_all()\n");
	cv_ready_.notify_all();

	while ( 1 )
	{
		//printf("wait\n");

		do
		{
			cv_.wait(lk);
		}
		while ( write_queue_.empty() && !terminate_ );

		//printf("notified\n");

		//cv_.wait( lk, [&] { return ( !write_queue_.empty() || terminate_ ); } );

		if ( terminate_ )
		{
			printf("terminated\n");
			return;
		}		

		//printf("create write thread\n");

		std::thread t(
				std::bind(
					&gal::network::communicating::thread_write,
					this,
					write_queue_.front()));
		t.detach();

		write_queue_.pop_front();
	}
}
void		gal::network::communicating::thread_write(boost::shared_ptr<gal::network::message> message) {
	//GALAXY_DEBUG_1_FUNCTION;
	

	std::string str(message->ss_.str());
	
	printf("DEBUG: sending message of length %i\n", (int)str.size());
	
	int result = ::send(socket_, str.c_str(), str.size(), 0 );
	
	if ( result < 0 ) {
		perror("send:");
		exit(0);
		/// \todo pass exception to main thread ( or whoever )
	}

	if ( result < (int)str.size() ) {
		// ???
		printf("unknown error\n");
		exit(0);
	}
}
void	gal::network::communicating::thread_read() {
	//GALAXY_DEBUG_1_FUNCTION;

	while (1) {
		{
			std::lock_guard<std::mutex> lk( mutex_ );

			if ( terminate_ )
			{
				return;
			}
		}
		
		try {
			thread_read_header();
		} catch(...) {
			/// \todo pass exception to main thread ( or whoever )
		}
	}
}
void	gal::network::communicating::thread_read_header() {
	//GALAXY_DEBUG_1_FUNCTION;
	
	//if ( !socket_->is_open() ) exit(0);//gal::cerr << "SOCKET NOT OPEN" << endl;
	
	
	//printf("waiting for %i bytes\n", message::header_length);
	
	// wail until all data is available
	int bytes = ::recv(socket_, &read_header_, sizeof(HEADER_TYPE), MSG_WAITALL);
	
	if (bytes < 0) {
		perror("recv:");
		exit(0);
	}
	
	if (bytes == 0) {
		printf("connection is closed\n");
		exit(0);
	}
	
	if (bytes < (int)sizeof(HEADER_TYPE)) {
		printf("%s\n", __PRETTY_FUNCTION__);
		printf("not enough data\n");
		exit(0);
	}
	
	handle_do_read_header();
}
void	gal::network::communicating::thread_read_body() {
	//GALAXY_DEBUG_1_FUNCTION;
	
	// wail until all data is available
	int bytes = ::recv(socket_, read_buffer_, read_header_, MSG_WAITALL);
	
	if(bytes < 0)
	{
		perror("recv:");
		exit(0);
	}


	if(bytes == 0) {
		printf("connection is closed\n");
		exit(0);
	}
	
	if(bytes < (int)sizeof(HEADER_TYPE)) {
		printf("not enough data\n");
		exit(0);
	}
	
	printf("DEBUG: received %i bytes\n", read_header_);
	//math::hexdump(read_msg_->body(), read_msg_->body_length());
	
	handle_do_read_body();
}

void	gal::network::communicating::handle_do_read_header() {
	//GALAXY_DEBUG_1_FUNCTION;
	
	if (read_msg_) {
		thread_read_body();
	} else {
		printf("header decode failed\n");

		std::thread(&gal::network::communicating::close, this).detach();
	}
}
void	gal::network::communicating::handle_do_read_body() {
	//GALAXY_DEBUG_1_FUNCTION;
	
	//gal::network::message_s msg(new gal::network::message);
	
	// copy buffer to message
	
	read_msg_->reset_head();
	
	read_msg_->ss_.write(read_buffer_, read_header_);
	
	process(read_msg_);
	
	thread_read_header();
}



