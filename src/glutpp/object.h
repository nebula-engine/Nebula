#ifndef __OBJECT_H__
#define __OBJECT_H__

static GLuint location_position = 0;
static GLuint location_normal = 1;

struct file_header
{
	GLuint len_positions_;
	GLuint len_normals_;
	GLuint len_indices_;
};

class object
{
public:
	GLuint buffer_position_;
	GLuint buffer_normal_;
	GLuint buffer_indices_;

	GLfloat*	vertex_positions_;
	GLfloat*	vertex_normals_;
	GLushort*		vertex_indices_;


	int	load(char const *);
	void	init_buffer();
	void	draw();
};

#endif
