#ifndef __JESS_ASIO_NETWORK_SOCKET_COMMUNICATING_HPP__
#define __JESS_ASIO_NETWORK_SOCKET_COMMUNICATING_HPP__

#include <cstdlib>
#include <deque>
#include <vector>
#include <iostream>
#include <thread>
#include <condition_variable>

#include <sys/socket.h>

#include <gru/network/message.hpp>

namespace gal {
	namespace network {
		/** %socket %communicating
		 */
		class communicating {
			public:
				typedef gal::network::message			message_t;
				typedef std::shared_ptr<communicating>		shared_t;
				typedef std::vector<shared_t>			vector_t;
			public:
				/** ctor
				 */
				communicating( int socket );
				/** write
				 */
				void					write(message_t::shared_t );
				/** close
				 */
				void					close();
				//	protected:
				/** thread write
				 */
				void					start();
				virtual void				process(message_t::shared_t) = 0;
				void					thread_write(message_t::shared_t );
				/** thread write dispath
				 */
				void					thread_write_dispatch();
				/** thread read
				 */
				void					thread_read();
				/** thread read header
				 */
				void					thread_read_header();
				/** thread read body
				 */
				void					thread_read_body();
				/** handle read header
				 */
				void					handle_do_read_header();
				/** handle read body
				 */
				void					handle_do_read_body();
				/** handle write
				 */
				void					handle_do_write();
				//	protected:
			protected:			
				/** socket
				 */
				int					socket_;
			private:
				/** message
				 */
				message_t::shared_t			read_msg_;
				HEADER_TYPE				read_header_;
				char					read_buffer_[MAX_MESSAGE_LENGTH]
				
				HEADER_TYPE				write_header_;
				/** message deque
				 */
				message_t::deque_t			write_queue_;
				/** process body
				 */
				bool					terminate_;
				/** thread write
				 */
				std::thread				write_thread_;
				/** thread read
				 */
				std::thread				read_thread_;
				/** condition variable
				 */
				std::condition_variable			cv_;
				std::condition_variable			cv_ready_;
				/** mutex
				 * mutex for write_queue_ and terminate_
				 */
				std::mutex				mutex_;
				std::mutex				mutex_start_;
		};
	}
}




#endif





