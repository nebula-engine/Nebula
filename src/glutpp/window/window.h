#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>
#include <vector>
#include <map>

#include <glutpp/config.h>
#include <glutpp/window/desc.h>
#include <glutpp/texture.h>
#include <glutpp/camera.h>
#include <glutpp/light/light.h>
#include <glutpp/master.h>
#include <glutpp/glsl/program.h>
#include <glutpp/glsl/shader.h>
#include <glutpp/gui/layout.h>

#include <math/mat44.h>
#include <math/vec4.h>
#include <math/vec3.h>

#include <gal/sig/signal.h>
#include <gal/flag.h>

void	checkerror(char const *);

namespace glutpp
{
	namespace window
	{
		class window:
			public gal::flag<unsigned int>,
			public std::enable_shared_from_this<window>
		{
			protected:
				int          windowID;

			public:
				window(glutpp::window::desc_s);
				//window(int, int, int, int, const char * );
				~window();
				void			i(int);
				void			init();

				void			callback_window_pos_fun(GLFWwindow*,int,int);
				void			callback_window_size_fun(GLFWwindow*,int,int);
				void			callback_window_close_fun(GLFWwindow*);
				void			callback_window_refresh_fun(GLFWwindow*);
				void			callback_mouse_button_fun(GLFWwindow*,int,int,int);
				void			callback_key_fun(GLFWwindow*,int,int,int,int);



				int			set_scene(std::shared_ptr<glutpp::scene::scene>);
				int			set_layout(std::shared_ptr<glutpp::gui::layout>);



				int			step(double);
				void			render(double);
				void			draw();
				void			draw_ortho();
				void			resize();



				void			display_dim();
				void			display_bright();


				void			SetWindowID(int newWindowID);
				int			GetWindowID(void);


				void			idle();
			private:
				unsigned int		f();
				void			f(unsigned int);
			public:
				// input signals
				struct
				{
					gal::sig::signal<int,int,int,int>	key_fun_;
					gal::sig::signal<int,int,int>		mouse_button_fun_;
				} sig_;

				int			i_;
				glutpp::window::raw	raw_;

				/*				char const *			title_;
								int				w_;
								int				h_;
								int				x_;
								int				y_;
				 */
				std::shared_ptr<renderable>	renderable_;

			public:
				GLFWwindow*			window_;

		};
	}
}


#endif








