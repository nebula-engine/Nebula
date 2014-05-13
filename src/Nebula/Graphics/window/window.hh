#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>
#include <vector>
#include <map>

#include <Nebula/config.hh>
#include <Nebula/Types.hh>
#include <Nebula/renderable.hh>
#include <Nebula/Graphics/window/desc.hh>
#include <Nebula/Graphics/texture.hh>
//#include <Nebula/camera.hh>
#include <Nebula/Graphics/Light/light.hh>
//#include <Nebula/master.hh>
#include <Nebula/Graphics/glsl/program.hh>
#include <Nebula/Graphics/glsl/shader.hh>
#include <Nebula/Graphics/gui/layout.hh>
#include <Nebula/Signals.hh>
/*
#include <math/mat44.hpp>
#include <math/vec4.hpp>
#include <math/vec3.hpp>
*/
//#include <galaxy/sig/signal.hpp>
//#include <galaxy/flag.hpp>



namespace Neb {
	namespace window {
		class window: public std::enable_shared_from_this<window>, public gal::flag {
			public:
				window(Neb::window::desc_s desc);
				~window();
			
			public:
				struct flag {
					enum e {
						SHOULD_RELEASE = 1 << 0,
					};
				};


				unsigned int const &		f() const;
				void				f(unsigned int const & flag);
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
				void		set_layout(Neb::gui::layout_s & layout);
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


				/*				char const *			title_;
								int				w_;
								int				h_;
								int				x_;
								int				y_;
				 */
				Neb::renderable_u		renderable_;


				int			i_;
				Neb::window::raw	raw_;

				GLFWwindow*		window_;
				
				//int			windowID;

			public:

		};
	}
}


#endif








