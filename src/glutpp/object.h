#ifndef __OBJECT_H__
#define __OBJECT_H__

namespace glutpp
{

	struct file_header
	{
		GLint len_vertices_;
		GLint len_indices_;
	};
	
	struct vertex
	{
		math::vec4	position;
		math::vec3	normal;
		math::vec2	texcoor;
		math::vec4	color;
	};
	
	class window;
	class object
	{
		public:
			enum
			{
				VAO = 1 << 0
			};
			enum
			{
				NONE = 0,
				LIGHT,
				PLANE
			};
			
			object(window*);
			GLuint		png_texture_load(const char *, int* , int*);
			int		save(char const *);
			int		load(char const *);
			void		init_buffer(GLint);
			virtual void	draw();
			virtual void	render_reflection();



			int		type_;
			unsigned int	flgs_;


			//GLint location_position_;
			//GLint location_normal_;
			//GLint location_texcoor_;

			//GLint location_image_;

			GLuint texture_image_;

			GLuint		vbo_;
			GLuint		buffer_indices_;

			file_header	fh_;
			
			glutpp::vertex*	vertices_;
			GLushort*	indices_;
			
			window*		window_;


	};
}

#endif
