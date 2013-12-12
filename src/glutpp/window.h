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
#include <glutpp/plane.h>
#include <glutpp/program.h>
#include <glutpp/shader.h>

#include <gal/sig/signal.h>

#include <math/mat44.h>
#include <math/vec4.h>
#include <math/vec3.h>

#include <gal/flag.h>


#define LIGHT_MAX 20

namespace glutpp
{
	class object;
	class window:
		public gal::flag
	{
		protected:

			int          windowID;

		public:
			enum
			{
				RAY_TRACE			= 1 << 0,
				LIGHTING			= 1 << 1,
				SHADOW				= 1 << 2,
				SHADOW_MAP			= 1 << 3,
				REFLECT				= 1 << 4,
				REFLECT_PLANAR			= 1 << 5,
				REFLECT_CURVED			= 1 << 6,
				TEX_IMAGE			= 1 << 7,
				TEX_NORMAL_MAP			= 1 << 8,
				ORTHO				= 1 << 9,
				SHADER				= 1 << 10
			};
			
			window(int, int, int, int, const char * );
			~window();
			
			void			init();
			void			add_object(object*);
			void			add_light(light*);
			

			void			callback_window_pos_fun(GLFWwindow*,int,int);
			void			callback_window_size_fun(GLFWwindow*,int,int);
			void			callback_window_close_fun(GLFWwindow*);
			void			callback_window_refresh_fun(GLFWwindow*);
			void			callback_key_fun(GLFWwindow*,int,int,int,int);
			
			void			loop();
			virtual void		step(double);
			void			render(double);
			void			draw();
			void			draw_ortho();
			void			resize();
			
			void			display_dim();
			void			display_bright();
			void			display_all_but(object*);
			
			void			lights_for_each(std::function<void(glutpp::light*)>);
			void			objects_for_each(std::function<void(glutpp::object*)>);

			void			SetWindowID(int newWindowID);
			int			GetWindowID(void);
			
			void			uniforms();
			void			shaders();
			GLint			get_program();
			
			void			idle();


			
			// input signals
			std::map<unsigned char,gal::sig::signal<> >	map_sig_key_down_;
			std::map<unsigned char,gal::sig::signal<> >	map_sig_key_up_;
			
			
			
			
			// idle signal
			std::function<void(double)>	func_idle_;
			



			char const *		title_;
			int			w_;
			int			h_;
			int			x_;
			int			y_;
			
			camera			camera_;
			
			light*			lights_[LIGHT_MAX];
			int			light_count_;
			
			uniform			uniform_light_count_;
			uniform			uniform_model_;
			uniform			uniform_view_;
			uniform			uniform_proj_;

			shader*			shaders_;
			int			shader_count_;
			


			std::vector<object*>	objects_;


		public:
			GLFWwindow*		window_;
			program*		program_;
	};
}

void	checkerror(char const *);

#endif








