#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <assert.h>

//#include <galaxy/config.hpp>
#include <gru/network/message.hpp>

gal::network::message::message(): body_length_(0)
{
	head_ = body();
}
const char*		gal::network::message::data() const
{
	return data_;
}
char*			gal::network::message::data()
{
	return data_;
}
std::size_t		gal::network::message::length() const
{
	return header_length + body_length_;
}
const char*		gal::network::message::body() const
{
	return data_ + header_length;
}
char*			gal::network::message::body()
{
	return data_ + header_length;
}
std::size_t		gal::network::message::body_length() const
{
	return body_length_;
}
void			gal::network::message::body_length(std::size_t new_length) {
	assert(new_length <= max_body_length);
	
	body_length_ = new_length;
	if (body_length_ > max_body_length)
	{
		body_length_ = max_body_length;
	}
}
void		gal::network::message::encode_header() {
	//char header[header_length + 1] = "";
	//std::sprintf(header, "%4d", int(body_length_));
	std::memcpy(data_, (void*)&body_length_, header_length);
}
void gal::network::message::set(void const * const v, unsigned int len) {
	//GALAXY_DEBUG_1_FUNCTION;
	
	assert(v);
	
	assert(len < max_body_length);
	
	memcpy(body(), v, len);
	
	body_length(len);
	encode_header();
}
void gal::network::message::reset_head() {
	ss.seekp(0);
}
void		gal::network::message::write(void const * const v, size_t len) {
	assert(v);
	
	ss.write(v,len);
}
void		gal::network::message::read(void * const v, size_t len) {
	assert(v);
	
	ss.read(v,len);
	
	if(ss.fail()) abort();
}



