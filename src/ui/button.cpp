#include <nebula/platform/renderer/base.hpp>

#include <nebula/ui/object/button.hpp>

void nebula::ui::object::button::render( jess::shared_ptr<npr::base>& rnd )
{
    rnd->draw_window_quad( x_, y_, w_, h_ );
}






