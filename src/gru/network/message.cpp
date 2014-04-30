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
void			gal::network::message::body_length(std::size_t new_length)
{
	assert(new_length <= max_body_length);
	
	body_length_ = new_length;
	if (body_length_ > max_body_length)
	{
		body_length_ = max_body_length;
	}
}
bool			gal::network::message::decode_header()
{
	//char header[header_length + 1] = "";
	
	//std::strncat(header, data_, header_length);
	
	std::memcpy((void*)&body_length_, data_, header_length);
	
	//body_length_ = std::atoi(header);
	
	//printf("decoded header: %X %i\n", (unsigned char)body_length_, (int)body_length_);
	
	if (body_length_ > max_body_length)
	{
		body_length_ = 0;
		return false;
	}
	
	return true;
}
void			gal::network::message::encode_header()
{
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
	head_ = body();
}
void gal::network::message::write(void const * const v, size_t len) {
	//GALAXY_DEBUG_2_FUNCTION;
	
	assert(v);
	
	size_t new_length = body_length() + len;
	
	if((head_ + len) > (body() + max_body_length))
	{
		printf("body length %i exceeds %i\n", (int)new_length, (int)max_body_length);
		abort();
	}
	
	memcpy(head_, v, len);
	
	head_ += len;
	
	body_length(new_length);
	encode_header();
}
void gal::network::message::read(void * const v, size_t len) {
	
	assert(v);
	
	assert((head_ + len) < (body() + max_body_length));
	
	memcpy(v, head_, len);
	
	head_ += len;
}



