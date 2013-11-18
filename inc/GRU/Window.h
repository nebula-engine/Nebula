#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>


#include <Maths/MATRIX4X4.h>
#include <Maths/VECTOR4D.h>
#include <Maths/VECTOR3D.h>

#include <GRU/Master.h>


namespace GRU
{
	class Window
	{
		protected:

			int          windowID;

		public:
			Window( GRU::Master* , int setWidth, int setHeight, int, int, const char * );
			~Window();

			int			height;
			int			width;
			int			initPositionX;
			int			initPositionY;


			virtual void		StartSpinning();

			virtual void		CallBackDisplayFunc();
			virtual void		CallBackIdleFunc(void);
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


			std::function<void()>	CallBackDisplay_;
			std::function<void()>	CallBackIdle_;


			MATRIX4X4		lightProjectionMatrix;
			MATRIX4X4		lightViewMatrix;
			MATRIX4X4		cameraProjectionMatrix;
			MATRIX4X4		cameraViewMatrix;



			void	update_camera_matrix(VECTOR3D eye,VECTOR3D center, VECTOR3D up);
			void	update_light_matrix();

	};
}

#endif








