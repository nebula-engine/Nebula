#include <gal/log/log.hpp>

#include <neb/core/math/geo/polyhedron.hh>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/glsl/buffer/tri1.hpp>
#include <neb/gfx/glsl/program/threed.hpp>


//constexpr GLenum		neb::gfx::glsl::buffer::tri1::target_[BUFFER_COUNT];// = {
//constexpr GLenum		neb::gfx::glsl::buffer::tri1::usage_[BUFFER_COUNT];// = {
//constexpr GLsizeiptr		neb::gfx::glsl::buffer::tri1::datasize_[BUFFER_COUNT];// = {
//constexpr GLint			neb::gfx::glsl::buffer::tri1::size_array_[ATTRIB_COUNT];// = {
//constexpr GLenum		neb::gfx::glsl::buffer::tri1::type_[ATTRIB_COUNT];// = {
//constexpr GLboolean		neb::gfx::glsl::buffer::tri1::normalized_[ATTRIB_COUNT];// = {
constexpr GLvoid*		neb::gfx::glsl::buffer::tri1::pointer_[ATTRIB_COUNT];// = {
//constexpr GLsizei		neb::gfx::glsl::buffer::tri1::stride_[ATTRIB_COUNT];// = {
//constexpr unsigned int		neb::gfx::glsl::buffer::tri1::buffer_index_[ATTRIB_COUNT];// = {
constexpr GLuint			neb::gfx::glsl::buffer::tri1::divisor_[ATTRIB_COUNT];// = {
constexpr neb::gfx::glsl::attribs::e	neb::gfx::glsl::buffer::tri1::attribute_[ATTRIB_COUNT];




/*void			neb::gfx::glsl::buffer::tri1::init(
		neb::gfx::glsl::buffer::tri1::program_shared program)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	base_type::init();

	vertexAttribPointer();

}
*/


