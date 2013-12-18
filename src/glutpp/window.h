#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>
#include <vector>
#include <map>

#include <glutpp/config.h>
#include <glutpp/texture.h>
#include <glutpp/camera.h>
#include <glutpp/light.h>
#include <glutpp/master.h>
//#include <glutpp/plane.h>
#include <glutpp/glsl/program.h>
#include <glutpp/glsl/shader.h>

#include <gal/sig/signal.h>

#include <math/mat44.h>
#include <math/vec4.h>
#include <math/vec3.h>

#include <gal/flag.h>


#define LIGHT_MAX 20

namespace glutpp
{
	class object;
	class renderable;
	class window: public gal::flag, public std::enable_shared_from_this<window>
	{
		protected:
			int          windowID;

		public:
			window(int, int, int, int, const char * );
			~window();
			
			void			init();
			int			prepare();

			void			callback_window_pos_fun(GLFWwindow*,int,int);
			void			callback_window_size_fun(GLFWwindow*,int,int);
			void			callback_window_close_fun(GLFWwindow*);
			void			callback_window_refresh_fun(GLFWwindow*);
			void			callback_mouse_button_fun(GLFWwindow*,int,int,int);
			void			callback_key_fun(GLFWwindow*,int,int,int,int);



			int			set_scene(std::shared_ptr<glutpp::scene>);



			void			loop();
			virtual void		step(double);
			void			render(double);
			void			draw();
			void			draw_ortho();
			void			resize(int,int);



			void			display_dim();
			void			display_bright();
			void			display_all_but(object*);


			void			SetWindowID(int newWindowID);
			int			GetWindowID(void);


			void			idle();


			// input signals
			struct
			{
				gal::sig::signal<int,int,int,int>			key_fun_;
				gal::sig::signal<int,int,int>				mouse_button_fun_;
			} sig_;


			char const *		title_;
			int			w_;
			int			h_;
			int			x_;
			int			y_;

			std::shared_ptr<renderable>	renderable_;

		public:
			GLFWwindow*			window_;

	};
}

void	checkerror(char const *);

#endif








