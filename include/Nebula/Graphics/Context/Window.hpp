#ifndef NEBULA_GRAPHICS_CONTEXT_WINDOW_HH
#define NEBULA_GRAPHICS_CONTEXT_WINDOW_HH

#include <memory>


#include <Nebula/Types.hh> // gru/config.hpp.in

#include <Nebula/Graphics/Types.hh>
#include <Nebula/Graphics/Context/Util/Cast.hh>
#include <Nebula/Graphics/GUI/Layout/Base.hh>
#include <Nebula/Graphics/Window/Base.hh>

#include <Nebula/Scene/Base.hh>

namespace Neb {
namespace Graphics {
namespace Context {
/** @brief Context
*
* A context with a window as the target.
*
* @todo allow for manual ordering of context::window objects in window's context map
* such that things like layouts are render ON TOP of existing scene.'
*/
class Base:
virtual public gal::std::shared,
virtual public Neb::Graphics::Context::Util::Cast
{
public:
Base();
Base(Neb::Graphics::Context::Util::Parent_s parent);
Base&	operator=(Base const & r);
void	init();
void	release();
void	resize(int w, int h);
void	render(double const & time, double const & dt);
public:
/** @brief %Parent
*
* @note WEAK
*/
sp::shared_ptr<Neb::Graphics::Context::Util::Parent>	parent_;
public:
/** @brief %Viewport
*
* sub-rectangle within target
*/
Neb::Graphics::Viewport	viewport_;
/** @brief View Space Camera
*
* @note OWNED
*/
sp::shared_ptr<Neb::Graphics::Camera::View::Base>	view_;
/** @brief Clip Space Camera
*
* @note OWNED
*/
sp::shared_ptr<Neb::Graphics::Camera::Projection::Base>	proj_;
/** @brief %Drawable
*
* @note WEAK
*
* content to draw
*/
sp::shared_ptr<Neb::Graphics::Drawable::Base>	drawable_;
};
}
}
}
#endif

