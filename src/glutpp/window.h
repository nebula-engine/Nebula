#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>
#include <vector>

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


#define LIGHTS_MAX 20

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
				ORTHO				= 1 << 9
			};
			
			window(int, int, int, int, const char * );
			~window();

			void			StartSpinning();
			void			CallBackDisplayFunc();
			void			CallBackIdleFunc(void);


			virtual void		CallBackKeyboardFunc(unsigned char key, int x, int y);
			virtual void		CallBackMotionFunc(int x, int y);
			virtual void		CallBackMouseFunc(int button, int state, int x, int y);
			virtual void		CallBackPassiveMotionFunc(int x, int y);
			virtual void		CallBackReshapeFunc(int w, int h);   
			virtual void		CallBackSpecialFunc(int key, int x, int y);   
			virtual void		CallBackVisibilityFunc(int visible);

			void			display_ortho();
			void			display_dim();
			void			display_bright();
			
			void			RenderReflection();
			void			lights_for_each(std::function<void(glutpp::light*)>);
			void			SetWindowID(int newWindowID);
			int			GetWindowID(void);
			void			Display();
			void			display_all_but(object*);
			
			virtual void		DisplayOrtho();
			virtual void		Idle();

			int			height;
			int			width;
			int			initPositionX;
			int			initPositionY;

			camera			camera_;

			std::vector<light*>	lights_;
			std::vector<texture*>	shadow_maps_;

			uniform*		uniform_light_count_;
			uniform*		uniform_model_;
			uniform*		uniform_view_;
			uniform*		uniform_proj_;

			shader*			shaders_;
			program*		program_;


			std::vector<object*>	objects_;
	};
}

void	checkerror(char const *);

#endif








