
#include <Nebula/Core/pose.hpp>

neb::core::pose::pose(): pos_(0,0,0,1) {};
neb::core::pose::pose(quat q, vec4 p): pos_(p), rot_(q) {}
neb::core::pose&		neb::core::pose::operator=(neb::core::pose const & rhs) {
	pos_ = rhs.pos_;
	rot_ = rhs.rot_;
	return *this;
}
neb::core::pose			neb::core::pose::operator*(neb::core::pose const & rhs) const {
	pose ret;
	ret.pos_ = pos_ + rot_ * rhs.pos_;
	ret.rot_ = rot_ * rhs.rot_;
	return ret;
}

mat4		neb::core::pose::mat4_cast() const {
	//mat4 ret(glm::mat4_cast(rot_));
	//return glm::translate(ret, vec3(pos_));
	
	mat4 ret = glm::translate(mat4(), vec3(pos_)) * glm::mat4_cast(rot_);
	
	return ret;

}

