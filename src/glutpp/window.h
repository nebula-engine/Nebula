#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>


#include <math/mat44.h>
#include <math/vec4.h>
#include <math/vec3.h>

#include <glutpp/texture.h>
#include <glutpp/camera.h>
#include <glutpp/light.h>
#include <glutpp/master.h>

namespace glutpp
{
	class window
	{
		protected:

			int          windowID;

		public:
			enum
			{
				SHADOWS = 1 << 0,
				ORTHO = 1 << 1
			};

			window(int, int, int, int, const char * );
			~window();

			int			height;
			int			width;
			int			initPositionX;
			int			initPositionY;


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


			void			Reshape();

			void			SetWindowID(int newWindowID);
			int			GetWindowID(void);


			virtual void		Display();
			virtual void		DisplayOrtho();
			virtual void		Idle();


			//math::mat44		lightProjectionMatrix;
			//math::mat44		lightViewMatrix;
			//math::mat44		cameraProjectionMatrix;
			//math::mat44		cameraViewMatrix;

			camera			camera_;
			light			light_;

			texture			texture_shadow_map_;

			unsigned int		flags_;
	};
}

#endif








