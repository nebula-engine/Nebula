#ifndef __GLUTPP_SHAPE_H__
#define __GLUTPP_SHAPE_H__

#include <map>

#include <GLFW/glfw3.h>

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/transform.h>
#include <math/geo/polyhedron.h>

#include <glutpp/types.h>
#include <glutpp/shape_desc.h>
#include <glutpp/material.h>

namespace glutpp
{
	struct file_header
	{
		int len_vertices_;
		int len_indices_;
	};

	struct vertex
	{
		void		print();

		math::vec4	position;
		math::vec3	normal;
		math::vec2	texcoor;
	};
	struct buffers
	{
		GLuint		vbo_;
		GLuint		indices_;
	};
	class shape
	{
		public:
			shape();
			int		save(char const *);
			int		load();
			int		load(char const *);
			void		construct(math::geo::polyhedron*);

		private:
			void		init_buffer(window_t, std::shared_ptr<glutpp::glsl::program>);
		public:

			virtual int	draw(std::shared_ptr<glutpp::window>, math::mat44);
			void		model_load(math::mat44);


			// draw data
			file_header		fh_;
			glutpp::vertex*		vertices_;
			GLushort*		indices_;

			material		material_front_;

			math::transform		pose_;
			math::vec3		scale_;

			std::map<glutpp::window*,std::shared_ptr<glutpp::buffers> >	context_;

			glutpp::shape_desc	desc_;
	};
}

#endif
