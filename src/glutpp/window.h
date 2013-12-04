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
				SHADOW				= 1 << 0,
				SHADOW_TEXTURE			= 1 << 1,
				ORTHO				= 1 << 2,
				PLANAR_REFLECTION		= 1 << 3,
				PLANAR_REFLECTION_STENCIL	= 1 << 4,
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

			void			PrepRenderCamera(glutpp::camera);
			//void			RenderLightPOV();
			//void			RenderShadow();
			void			RenderOrtho();
			void			RenderReflection();
			void			DisplayDim();
			//void			PostRenderShadow();
			void			display_bright();
			void			lights_for_each(std::function<void(glutpp::light*)>);
			void			Reshape();
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

			shader*			shaders_;
			program*		program_;
		

			std::vector<object*>	objects_;
	};
}

void	checkerror(char const *);

#endif








