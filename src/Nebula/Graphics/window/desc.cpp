#include <algorithm>

#include <string.h>

#include <gru/Graphics/window/desc.hpp>

glutpp::window::raw::raw():
	i_(-1),
	flag_(0),
	x_(0),
	y_(0),
	w_(0),
	h_(0)
{
	memset(title_, 0, title_length_max);
}

glutpp::window::desc::desc(int w, int h, int x, int y, const char * title) {
	raw_.flag_ = 0;

	raw_.w_ = w;
	raw_.h_ = h;
	raw_.x_ = x;
	raw_.y_ = y;

	size_t len = std::min(strlen(title), (size_t)raw::title_length_max);

	memcpy(raw_.title_, title, len);
}

