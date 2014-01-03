#ifndef __GLUTPP_SHAPE_H__
#define __GLUTPP_SHAPE_H__

#include <map>

#include <GLFW/glfw3.h>

#include <gal/flag.h>

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/transform.h>
#include <math/geo/polyhedron.h>

#include <glutpp/config.h>
#include <glutpp/types.h>
#include <glutpp/shape/desc.h>
#include <glutpp/material.h>

namespace glutpp
{
	namespace shape
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
		class shape: public std::enable_shared_from_this<shape>, public gal::flag
		{
			public:
				enum flag
				{
					SHOULD_DELETE = 1 << 0
				};

				virtual ~shape();

				typedef std::shared_ptr<glutpp::shape::buffers>		buffer_t;
				typedef std::map<glutpp::window*,buffer_t>		map_t;


				shape(glutpp::actor::actor_shared, glutpp::shape::desc*);

				void			init();
				void			release();
				void			cleanup();

				math::mat44		get_pose();

				int			save(char const *);
				int			load(char const *);
				void			construct(math::geo::polyhedron*);
			private:
				void			init_buffer(
						window_t,
						std::shared_ptr<glutpp::glsl::program>);
			public:

				virtual void		draw(
						std::shared_ptr<glutpp::window>,
						math::mat44);
				virtual void		draw_elements(
						std::shared_ptr<glutpp::window>,
						math::mat44);

				void			load_lights(int&);

				void			model_load(math::mat44);


				// draw data
				file_header			fh_;
				glutpp::shape::vertex*		vertices_;
				GLushort*			indices_;

				material			material_front_;

				map_t				context_;

				glutpp::shape::desc*		desc_;

				light_vec			lights_;
				glutpp::shape::shape_vec	shapes_;

				glutpp::actor::actor_weak	actor_;
		};
	}
}

#endif
