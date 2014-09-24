#include <iomanip>

#include <gal/log/log.hpp>

#include <neb/gfx/free.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/buffer/instanced.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/glsl/attrib.hh>

//constexpr GLenum			neb::gfx::glsl::buffer::instanced::usage_[BUFFER_COUNT];
//constexpr GLsizeiptr			neb::gfx::glsl::buffer::instanced::datasize_[BUFFER_COUNT];
//constexpr GLenum			neb::gfx::glsl::buffer::instanced::target_[BUFFER_COUNT];
//constexpr GLint				neb::gfx::glsl::buffer::instanced::size_array_[ATTRIB_COUNT];
//constexpr GLsizei			neb::gfx::glsl::buffer::instanced::stride_[ATTRIB_COUNT];
//constexpr GLenum			neb::gfx::glsl::buffer::instanced::type_[ATTRIB_COUNT];
//constexpr GLboolean			neb::gfx::glsl::buffer::instanced::normalized_[ATTRIB_COUNT];
//constexpr unsigned int			neb::gfx::glsl::buffer::instanced::buffer_index_[ATTRIB_COUNT];
constexpr GLuint			neb::gfx::glsl::buffer::instanced::divisor_[ATTRIB_COUNT];
constexpr void*				neb::gfx::glsl::buffer::instanced::pointer_[ATTRIB_COUNT];
constexpr neb::gfx::glsl::attribs::e	neb::gfx::glsl::buffer::instanced::attribute_[ATTRIB_COUNT];


