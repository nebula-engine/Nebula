#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>

#include <glutpp/texture.h>
#include <glutpp/uniform.h>
#include <glutpp/attribute.h>
#include <glutpp/material.h>


namespace glutpp
{

	struct file_header
	{
		GLint len_vertices_;
		GLint len_indices_;
	};
	
	struct vertex
	{
		void		print();
		
		math::vec4	position;
		math::vec3	normal;
		math::vec2	texcoor;
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
			};
			
			object(window*);
			GLuint		png_texture_load(const char *, int* , int*);
			int		save(char const *);
			int		load(char const *);
			void		init_buffer();
			void		model_load();
			void		model_unload();

			virtual void	draw();
			virtual void	render_reflection();
			


			int		type_;
			unsigned int	flgs_;


			attribute		attrib_position_;
			attribute		attrib_normal_;
			attribute		attrib_texcoor_;
			//GLint location_image_;
			
			texture			texture_image_;
			uniform			uniform_image_;
			
			GLuint			vbo_;
			GLuint			buffer_indices_;
			
			math::mat44		model_;
	
			// draw data
			file_header		fh_;
			glutpp::vertex*		vertices_;
			GLushort*		indices_;

			material		material_front_;
			
			window*			window_;
	};
}

#endif
