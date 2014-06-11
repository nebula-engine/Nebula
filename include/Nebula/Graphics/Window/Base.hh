#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>
#include <vector>
#include <map>

#include <Nebula/config.hh>
#include <Nebula/Types.hh>
#include <Nebula/Core/TimeStep.hpp>
#include <Nebula/Scene/Util/Types.hh>

#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Graphics/Context/Util/Parent.hh>
#include <Nebula/Graphics/Types.hh>
#include <Nebula/Graphics/texture.hh>
#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/glsl/program.hh>
#include <Nebula/Graphics/glsl/shader.hh>
#include <Nebula/Graphics/GUI/Layout/Base.hh>
#include <Nebula/Graphics/Window/__base.hpp>
#include <Nebula/Graphics/Window/Util/Flag.hh>
#include <Nebula/Graphics/Window/Util/Cast.hh>

#include <Nebula/Signals.hh>



namespace Neb {
	namespace Graphics {
		namespace Window {
			class Base:
				virtual public Neb::Graphics::Window::__base,
				virtual public Neb::Graphics::Context::Util::Parent,
				virtual public Neb::Graphics::Window::Util::Cast
			{
				public:
					Base();
					Base(Neb::Graphics::Window::Util::Parent_s parent);
					virtual ~Base();
				
				public:
					virtual void				init();
					virtual void				release();
	
					/** @name Main Loop @{ */
					void					render();
					void					step(Neb::Core::TimeStep const & ts);
					/** @} */
					void					resize();
	
					void					callback_window_pos_fun(GLFWwindow*,int,int);
					void					callback_window_size_fun(GLFWwindow*,int,int);
					void					callback_window_close_fun(GLFWwindow*);
					void					callback_window_refresh_fun(GLFWwindow*);
					void					callback_mouse_button_fun(GLFWwindow*,int,int,int);
					void					callback_key_fun(GLFWwindow*,int,int,int,int);
				public:
					Neb::Graphics::Window::Util::Parent_s			parent_;
					/** @brief self
					 *
					 * avoid casting shared_from_this
					 */
					sp::shared_ptr<Neb::Graphics::Window::Base>		self_;

					// input signals
					struct
					{
						Neb::Signals::KeyFun		key_fun_;
						Neb::Signals::MouseButtonFun	mouse_button_fun_;
					} sig_;


					
					
	
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








