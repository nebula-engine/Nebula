#ifndef __JESS_ASIO_NETWORK_SOCKET_COMMUNICATING_HPP__
#define __JESS_ASIO_NETWORK_SOCKET_COMMUNICATING_HPP__

#include <cstdlib>
#include <deque>
#include <vector>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <memory>

#include <sys/socket.h>

#include <boost/asio.hpp>

namespace ip = boost::asio::ip;

#include <gal/itf/shared.hpp>

#include <gal/net/decl.hpp>
#include <gal/net/basic.hpp>
#include <gal/net/message.hpp>

namespace gal {
	namespace net {
		/** @brief %communicating
		 */
		class communicating: virtual public gal::itf::shared {
			public:
				typedef int				header_type;
				enum { MAX_MESSAGE_LENGTH = 10000 };
			public:
				/** @brief ctor
				 *
				 * @param socket socket
				 */
				communicating(boost::asio::io_service& io_service, ip::tcp::socket&& socket);
				/** @brief ctor
				 *
				 * @param io_serive io_service
				 */
				communicating(boost::asio::io_service& io_service);
				/** @brief write
				 *
				 * send %message to socket
				 * @param %message %message to send
				 */
				void					write(std::shared_ptr<omessage> message);
				/** @brief close
				 *
				 * close the socket and terminate threads
				 */
				void					close();
			private:
				communicating(communicating const &) = default;
				communicating(communicating &&) = default;
				communicating&				operator=(communicating const &) = default;
				communicating&				operator=(communicating &&) = default;

				virtual void				process(std::shared_ptr<gal::net::imessage>) = 0;
			public:
				void					do_read_header();
			private:
				void					do_write();
				void					thread_write(std::shared_ptr<gal::net::omessage> msg);
				void					thread_do_write_header(
						boost::system::error_code ec,
						size_t length,
						std::shared_ptr<gal::net::omessage> msg);
				void					thread_do_write_body(
						boost::system::error_code ec,
						size_t length);
				/** @brief thread read
				 */
				void						thread_read();
				/** @brief thread read header
				 */
				void						thread_read_header(boost::system::error_code ec, size_t length);
				void						do_read_body();
				/** @brief thread read body
				 */
				void						thread_read_body(boost::system::error_code ec, size_t);
				/** @brief handle write
				 */
				void						handle_do_write();
			protected:
				ip::tcp::socket						socket_;
				boost::asio::io_service&				io_service_;
			private:
				/** @name Read Data Members @{ */
				std::shared_ptr< gal::net::imessage >			read_msg_;
				header_type						read_header_;
				char							read_buffer_[MAX_MESSAGE_LENGTH];
				/** @} */
				header_type						write_header_;
				/** message deque
				 */
				::std::deque< std::shared_ptr< omessage > >		write_msgs_;
				/** process body
				 */
				/** thread write
				*/
				::std::thread					write_thread_;
				/** thread read
				*/
				::std::thread					read_thread_;
				/** condition variable
				*/
				//std::condition_variable				cv_ready_;
				//std::mutex					mutex_start_;
		};
	}
}




#endif





