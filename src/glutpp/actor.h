#ifndef __GLUTPP_ACTOR_H__
#define __GLUTPP_ACTOR_H__
#include <memory>
#include <vector>
#include <map>

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/geo/polyhedron.h>
#include <math/transform.h>

#include <glutpp/texture.h>
//#include <glutpp/uniform.h>
//#include <glutpp/attribute.h>
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
	class scene;
	class light;
	namespace glsl
	{
		class program;
	}
	class actor_buffers
	{
		public:
			GLuint			vbo_;
			GLuint			buffer_indices_;	


	};
	class actor: public std::enable_shared_from_this<actor>
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

			actor();
			void		init(std::shared_ptr<scene>);
			std::shared_ptr<scene>	get_scene();

			void		construct(math::geo::polyhedron*);
			void		uniforms();
			int		save(char const *);
			int		load(char const *);

		private:
			void		init_buffer(std::shared_ptr<glutpp::window>, std::shared_ptr<glutpp::glsl::program>);
		public:

			void		model_load();


			virtual int	draw(std::shared_ptr<glutpp::window>);

			virtual int	release();


			virtual void	render_reflection();


			int		i_;
			int		type_;


			//attribute		attrib_position_;
			//attribute		attrib_normal_;
			//attribute		attrib_texcoor_;
			//GLint location_image_;

			texture			texture_image_;

			//uniform			uniform_image_;



			//math::mat44		model_;
			math::transform		pose_;
			math::vec3		s_;

			// draw data
			file_header		fh_;
			glutpp::vertex*		vertices_;
			GLushort*		indices_;

			material		material_front_;

			std::weak_ptr<scene>	scene_;

			std::vector<int>	actors_;
			std::vector<int>	lights_;

			std::map<glutpp::window*,std::shared_ptr<glutpp::actor_buffers> >	context_;
	};
}

#endif
