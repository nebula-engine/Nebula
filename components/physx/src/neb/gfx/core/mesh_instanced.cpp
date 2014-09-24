
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/mesh/instanced.hpp>
#include <neb/gfx/glsl/buffer/instanced.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/free.hpp>


void			neb::gfx::mesh::instanced::init(
		neb::gfx::mesh::instanced::program_type* program)
{
	//mesh_.init_buffer(program);
	
/*	typedef neb::gfx::glsl::buffer::instanced T;
	
	std::shared_ptr<T> buf(new T());
	
	buffers_[program] = buf;
	
	buf->init(program);
	
	bufferDataNull(buf.get());
*/

	buffer_tuple bt = getBufferTuple(program);

	bufferDataNull(bt);
}

GLsizeiptr*		neb::gfx::mesh::instanced::size_array() {

	for(unsigned int c = 0; c < BUFFER_COUNT; c++)
	{
		size_array_[c] = instances_->size_array();
	}

	return size_array_;
}
GLsizeiptr*		neb::gfx::mesh::instanced::size() {

	begin();
	end();

	for(unsigned int c = 0; c < BUFFER_COUNT; c++)
	{
		size_[c] = end_[c] - begin_[c] + 1;
	}

	return size_;
}
GLsizeiptr*		neb::gfx::mesh::instanced::end() {
	end_[0] = instances_->update_end_;
	end_[1] = instances_->update_end_;
	end_[2] = instances_->update_end_;
	end_[3] = instances_->update_end_;
	end_[4] = instances_->update_end_;
	end_[5] = instances_->update_end_;
	end_[6] = instances_->update_end_;
	return end_;
}
GLsizeiptr*		neb::gfx::mesh::instanced::begin() {
	begin_[0] = instances_->update_begin_;
	begin_[1] = instances_->update_begin_;
	begin_[2] = instances_->update_begin_;
	begin_[3] = instances_->update_begin_;
	begin_[4] = instances_->update_begin_;
	begin_[5] = instances_->update_begin_;
	begin_[6] = instances_->update_begin_;
	return begin_;
}
GLvoid** const		neb::gfx::mesh::instanced::data() {
	data_[0] = instances_->get<0, glm::mat4>();
	data_[1] = instances_->get<1, glm::vec4>();
	data_[2] = instances_->get<2, unsigned int>();
	data_[3] = instances_->get<3, glm::vec4>();
	data_[4] = instances_->get<4, glm::vec4>();
	data_[5] = instances_->get<5, glm::vec4>();
	data_[6] = instances_->get<6, GLfloat>();
	return data_;
}
void			neb::gfx::mesh::instanced::draw(
		neb::gfx::mesh::instanced::program_type* program)
{

	if(!buffers_[program])
	{	
		init(program);
	}
	auto buf = buffers_[program];

	if(!buf) return;
	
	auto bt = getBufferTuple(program);
	
	instances_->update_slots();

	//bufferData(buf);
	//bufferSubData(buf.get());
	//buf->bufferSubData(begin(), end(), size(), data());
	
	bufferSubData(bt);
	
	draw(program, buf);
}
void			neb::gfx::mesh::instanced::draw(
		neb::gfx::mesh::instanced::program_type*		program,
		std::shared_ptr<neb::gfx::glsl::buffer::instanced>	buf)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	//auto buf_mesh = mesh_.getBuffer(program);
	auto bt = mesh_.getBufferTuple(program);

	buf->vertexAttribPointer();
	//buf_mesh->vertexAttribPointer();
	
	mesh_.vertexAttribPointer(bt);

	LOG(lg, neb::gfx::sl, debug) << "instances size = " << instances_->size();
	LOG(lg, neb::gfx::sl, debug) << "mesh size      = " << mesh_.getNbIndices();

	mesh_.bind(bt);

	glDrawElementsInstanced(
			GL_TRIANGLES,
			mesh_.getNbIndices(),
			GL_UNSIGNED_SHORT,
			0,
			instances_->size());

	checkerror("glDrawElementsInstanced");

	mesh_.unbind(bt);
}

