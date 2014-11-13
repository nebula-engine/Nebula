#ifndef NEB_GFX_OGL_PNG_HPP
#define NEB_GFX_OGL_PNG_HPP

void	save_png(const char * filename, int w, int h);
bool	save_png_libpng(const char *filename, uint8_t *pixels, int w, int h);

#endif

