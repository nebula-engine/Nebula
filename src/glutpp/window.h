#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>
#include <vector>

#define STR(x) #x
#define PNT(x) STR(x)
#define GLUTPP_OBJECT_PREFIX__ GLUTPP_PREFIX/glutpp/objects/
#define GLUTPP_SHADER_PREFIX__ GLUTPP_PREFIX/glutpp/shaders/
#define GLUTPP_OBJECT_PREFIX PNT(GLUTPP_OBJECT_PREFIX__)
#define GLUTPP_SHADER_PREFIX PNT(GLUTPP_SHADER_PREFIX__)


#include <glutpp/texture.h>
#include <glutpp/camera.h>
#include <glutpp/light.h>
#include <glutpp/master.h>
#include <glutpp/plane.h>
#include <glutpp/program.h>
#include <glutpp/shader.h>

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
			
			void			StartSpinning();
			void			CallBackDisplayFunc();
			void			CallBackIdleFunc(void);



			void			display_ortho();
			
			void			callback_display_ortho();
			void			display_dim();
			void			display_bright();
			void			display();
			void			display_all_but(object*);
			
			void			RenderReflection();
			void			lights_for_each(std::function<void(glutpp::light*)>);
			void			objects_for_each(std::function<void(glutpp::object*)>);

			void			SetWindowID(int newWindowID);
			int			GetWindowID(void);
			
			void			uniforms();
			void			shaders();
			GLint			get_program();
			
			// virtual
			virtual void		Idle();
			virtual void		CallBackKeyboardFunc(unsigned char key, int x, int y);
			virtual void		CallBackMotionFunc(int x, int y);
			virtual void		CallBackMouseFunc(int button, int state, int x, int y);
			virtual void		CallBackPassiveMotionFunc(int x, int y);
			virtual void		CallBackReshapeFunc(int w, int h);   
			virtual void		CallBackSpecialFunc(int key, int x, int y);   
			virtual void		CallBackVisibilityFunc(int visible);


			char const *		title_;
			int			height;
			int			width;
			int			initPositionX;
			int			initPositionY;
			
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


		private:
			program*		program_;
	};
}

void	checkerror(char const *);

#endif








