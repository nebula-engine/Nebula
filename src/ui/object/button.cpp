#include <nebula/platform/renderer/base.hpp>

#include <nebula/ui/object/button.hpp>

void nebula::ui::object::button::render( std::shared_ptr<n23000::base>& rnd )
{
    rnd->draw_window_quad( x_, y_, w_, h_ );
}






