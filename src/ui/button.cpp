

void UI::Button::Render(Platform::Renderer::Base* renderer)
{
    renderer->draw_window_quad(x_,y_,w_,h_);
}
