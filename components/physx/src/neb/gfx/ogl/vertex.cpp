
#include <neb/gfx/free.hpp>
#include <neb/gfx/opengl/vertex.hpp>

void			neb::gfx::ogl::bufferData(
		const GLenum		target,
		const GLuint		buffer,
		const GLsizeiptr	datasize,
		const GLsizeiptr	size,
		GLvoid* const		data,
		const GLenum		usage)
{

	glBindBuffer(
			target,
			buffer);

	checkerror("glBindBuffer");

	glBufferData(
			target,
			size * datasize,
			data,
			usage);

	checkerror("glBufferSubData");

	glBindBuffer(target, 0);

	checkerror("glBindBuffer");

}
void			neb::gfx::ogl::bufferDataNull(
		const GLenum		target,
		GLuint			buffer,
		const GLsizeiptr	datasize,
		GLsizeiptr		size,
		const GLenum		usage)
{

	glBindBuffer(target, buffer);

	checkerror("glBindBuffer");

	glBufferData(
			target,
			size * datasize,
			NULL,
			usage);

	checkerror("glBufferData");

	glBindBuffer(target, 0);

	checkerror("glBindBuffer");
}
void			neb::gfx::ogl::bufferSubData(
		const GLenum		target,
		GLuint			buffer,
		GLintptr		begin,
		GLintptr		end,
		const GLsizeiptr	datasize,
		GLsizeiptr		size,
		GLvoid* const		data)
{

	GLsizeiptr offset;


	offset = begin * datasize;

	//LOG(lg, neb::gfx::sl, debug)
	//	<< std::setw(16) << offset
	//	<< std::setw(16) << siz * BUFFER::datasize;

	glBindBuffer(
			target,
			buffer);
	checkerror("glBufferSubData");

	GLvoid* d = (GLvoid*)((GLintptr)data + offset);

	glBufferSubData(
			target,
			offset,
			size * datasize,
			d);

	checkerror(
			"glBufferSubData\n"
			"target   %i\n"
			"offset   %i\n"
			"size     %i\n"
			"datasize %i\n"
			"data     %x\n",
			target, offset, size, datasize, d);

	glBindBuffer(target, 0);
	checkerror("glBindBuffer");


}




