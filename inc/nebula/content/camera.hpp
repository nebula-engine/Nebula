#ifndef __NEBULA_CONTENT_CAMERA_HPP__
#define __NEBULA_CONTENT_CAMERA_HPP__


namespace nebula
{
	namespace content
	{
		/// camera
		class camera
		{
		public:
			/// ctor
			camera();
			/// render
			void									render( std::shared_ptr<n23000::base> );

			/// controller
			std::shared_ptr<n34100::controller::base>		controller_;
		};
	}
}



#endif

