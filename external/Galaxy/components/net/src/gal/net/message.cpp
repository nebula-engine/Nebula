#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <assert.h>

//#include <galaxy/config.hpp>
#include <gal/net/message.hpp>

gal::net::message::message() {
}
gal::net::message::~message() {
}
/*void gal::net::message::set(void const * const v, unsigned int len) {
	//GALAXY_DEBUG_1_FUNCTION;
	
	assert(v);
	
	assert(len < Neb::Network::MAX_MESSAGE_LENGTH);
	
	memcpy(body(), v, len);
	
	body_length(len);
	encode_header();
}*/
void gal::net::message::reset_head() {
	ss_.seekp(0);
}
/*void		gal::net::message::write(void const * const v, size_t len) {
	assert(v);
	
	ss_.write((char*)v,len);
}
void		gal::net::message::read(void * const v, size_t len) {
	assert(v);
	
	ss_.read((char*)v,len);
	
	if(ss_.fail()) abort();
}*/







