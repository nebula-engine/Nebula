#include <algorithm>

#include <string.h>

#include <glutpp/window/desc.h>

glutpp::window::desc::desc(int w, int h, int x, int y, const char * title)
{
	raw_.flag_ = 0;
	
	raw_.w_ = w;
	raw_.h_ = h;
	raw_.x_ = x;
	raw_.y_ = y;
	
	size_t len = std::min(strlen(title), (size_t)raw::title_length_max);
	
	memcpy(raw_.title_, title, len);
}

