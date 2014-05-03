#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <assert.h>

//#include <galaxy/config.hpp>
#include <gru/network/message.hpp>

gal::network::message::message() {
}
/*void gal::network::message::set(void const * const v, unsigned int len) {
	//GALAXY_DEBUG_1_FUNCTION;
	
	assert(v);
	
	assert(len < Neb::Network::MAX_MESSAGE_LENGTH);
	
	memcpy(body(), v, len);
	
	body_length(len);
	encode_header();
}*/
void gal::network::message::reset_head() {
	ss_.seekp(0);
}
void		gal::network::message::write(void const * const v, size_t len) {
	assert(v);
	
	ss_.write((char*)v,len);
}
void		gal::network::message::read(void * const v, size_t len) {
	assert(v);
	
	ss_.read((char*)v,len);
	
	if(ss_.fail()) abort();
}



