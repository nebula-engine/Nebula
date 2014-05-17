#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>
#include <vector>
#include <map>

#include <Nebula/config.hh>
#include <Nebula/Types.hh>
#include <Nebula/Scene/Util/Types.hh>

#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Graphics/Context/Util/Parent.hh>
#include <Nebula/Graphics/Types.hh>
#include <Nebula/Graphics/texture.hh>
#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/glsl/program.hh>
#include <Nebula/Graphics/glsl/shader.hh>
#include <Nebula/Graphics/GUI/Layout/Base.hh>
#include <Nebula/Graphics/Window/Util/Flag.hh>

#include <Nebula/Signals.hh>



namespace Neb {
	namespace Graphics {
		namespace Window {
			class Base:
				public Neb::Graphics::Context::Util::Parent
			{
				public:
					Base();
					Base(Neb::Graphics::Window::Util::Parent_s parent);
					virtual ~Base() {}
				
				public:
					struct flag {
						enum e {
							SHOULD_RELEASE = 1 << 0,
						};
					};
	
					int const			i() const;
					void				i(int const & ni);
	
	
					void				init();
	
	
					/** @name Main Loop @{ */
					void				render(double time);
					void				step(double time);
					/** @} */
					void		resize();
					/** @ brief Set Layout.
					 * @param layout @c shared_ptr what will be moved
					 */
					void		set_layout(Neb::Graphics::GUI::Layout::Base_s & layout);
					void		set_scene(Neb::Scene::Base_s & scene);
	
					void	callback_window_pos_fun(GLFWwindow*,int,int);
					void	callback_window_size_fun(GLFWwindow*,int,int);
					void	callback_window_close_fun(GLFWwindow*);
					void	callback_window_refresh_fun(GLFWwindow*);
					void	callback_mouse_button_fun(GLFWwindow*,int,int,int);
					void	callback_key_fun(GLFWwindow*,int,int,int,int);
				public:
					// input signals
					struct
					{
						Neb::Signals::KeyFun		key_fun_;
						Neb::Signals::MouseButtonFun	mouse_button_fun_;
					} sig_;
	
	
	
					int					i_;
					Neb::Graphics::Window::Util::Flag	flag_;
					int					x_;
					int					y_;
					int					w_;
					int					h_;
					std::string				title_;
					
					
					GLFWwindow*		window_;
					
					//int			windowID;
	
				public:

			};
		}
	}
}


#endif








