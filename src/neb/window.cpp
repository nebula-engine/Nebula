#include <neb/app.h>
#include <neb/window.h>

neb::window::window(int w, int h, int x, int y, char const * title):
        glutpp::window(w,h,x,y,title)
{
}
void	neb::window::step(double time)
{
        printf("%s\n", __PRETTY_FUNCTION__);

        app_.lock()->step(time);
}









