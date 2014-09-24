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

#include <boost/bind.hpp>

#include <gal/net/message.hpp>
#include <gal/net/communicating.hpp>

#define LOG ::std::cout << __PRETTY_FUNCTION__

gal::net::communicating::communicating(boost::asio::io_service& io_service, ip::tcp::socket&& socket):
	socket_(::std::move(socket)),
	io_service_(io_service),
	read_msg_(new gal::net::imessage)
{

}
gal::net::communicating::communicating(boost::asio::io_service& io_service):
	socket_(io_service),
	io_service_(io_service),
	read_msg_(new gal::net::imessage)
{

}
void		gal::net::communicating::do_read_header() {

	auto self(std::dynamic_pointer_cast<gal::net::communicating>(shared_from_this()));

	boost::asio::async_read(socket_,
			boost::asio::buffer(&read_header_, sizeof(header_type)),
			boost::bind(&gal::net::communicating::thread_read_header, self, _1, _2)
			);

}
void		gal::net::communicating::write(std::shared_ptr<gal::net::omessage> msg) {	

	auto self(std::dynamic_pointer_cast<gal::net::communicating>(shared_from_this()));

	io_service_.post(boost::bind(&gal::net::communicating::thread_write, self, msg));
}
void		gal::net::communicating::thread_write(std::shared_ptr<gal::net::omessage> msg) {

	bool write_in_progress = !write_msgs_.empty();

	write_msgs_.push_back(msg);

	if(!write_in_progress) {
		do_write();
	}
}
void		gal::net::communicating::do_write() {

	auto msg = write_msgs_.front();
	write_msgs_.pop_front();

	::std::string str(msg->ss_.str());

	//printf("DEBUG: sending message of length %i\n", (int)str.size());

	header_type header = str.size();

	auto self(std::dynamic_pointer_cast<gal::net::communicating>(shared_from_this()));

	boost::asio::async_write(socket_,
			boost::asio::buffer(&header, sizeof(header_type)),
			boost::bind(
				&gal::net::communicating::thread_do_write_header,
				self,
				_1,
				_2,
				msg)
			);
}
void		gal::net::communicating::thread_do_write_header(boost::system::error_code ec, size_t length, std::shared_ptr<gal::net::omessage> msg) {

	::std::string str(msg->ss_.str());

	auto self(std::dynamic_pointer_cast<gal::net::communicating>(shared_from_this()));

	boost::asio::async_write(socket_,
			boost::asio::buffer(str.c_str(), str.size()),
			boost::bind(
				&gal::net::communicating::thread_do_write_body,
				self,
				_1,
				_2)
			);
}
void		gal::net::communicating::thread_do_write_body(boost::system::error_code ec, size_t length) {
	if (!ec) {
		if (!write_msgs_.empty()) {
			do_write();
		}
	} else {
		LOG  << " error" << ::std::endl;
		socket_.close();
	}
}
void	gal::net::communicating::close() {	

	io_service_.post([this]() { socket_.close(); });

}
/*void		gal::net::communicating::notify_bits(unsigned int bits) {
	{
		std::lock_guard<std::mutex> lk(mutex_);
		bits_ |= bits;
	}
	cv_.notify_all();
}*/
/*void		gal::net::communicating::thread_write_body(boost::system::error_code ec, size_t length, std::shared_ptr<gal::net::omessage> message) {

	std::string str(message->ss_.str());

	int result = boost::asio::write(socket_, boost::asio::buffer(str.c_str(), str.size()));

	if(result < 0) {
		perror("send:");
		notify_bits(TERMINATE & ERROR);
		return;
	}

	if(result < (int)str.size()) {
		printf("unknown error\n");
		notify_bits(TERMINATE & ERROR);
		return;
	}
}*/
void	gal::net::communicating::thread_read_header(boost::system::error_code ec, size_t length) {

	if(ec) {
		LOG << __PRETTY_FUNCTION__ << ": " << ec.message() << ::std::endl;
		return;
	}

	if(length != sizeof(header_type)) {
		LOG << __PRETTY_FUNCTION__ << ": unknwon error" << ::std::endl;
	}

	do_read_body();

}
void	gal::net::communicating::do_read_body() {

	auto self(std::dynamic_pointer_cast<gal::net::communicating>(shared_from_this()));

	boost::asio::async_read(socket_,
			boost::asio::buffer(read_buffer_, read_header_),
			boost::bind(&gal::net::communicating::thread_read_body, self, _1, _2)
			);

}
void	gal::net::communicating::thread_read_body(boost::system::error_code ec, size_t) {

	if (!ec) {
		// process message
		read_msg_->reset_head();
		read_msg_->ss_.write(read_buffer_, read_header_);
		process(read_msg_);

		// restart read process
		do_read_header();
	} else {
		// error
		LOG << __PRETTY_FUNCTION__ << " error" << ::std::endl;
		return;
	}

}




