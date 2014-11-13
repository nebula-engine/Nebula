#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/util/typedef.hpp>

#include <neb/gfx/Viewport.hpp>
#include <neb/gfx/util/log.hpp>

neb::gfx::Viewport::Viewport():
	x_(0),
	y_(0),
	w_(0),
	h_(0),
	aspect_(0)
{}
void		neb::gfx::Viewport::load() {
	glViewport(x_, y_, w_, h_);
}
void		neb::gfx::Viewport::resize(int w, int h) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	w_ = w;
	h_ = h;
	
	aspect_ = (real)w_ / (real)h_;
}

