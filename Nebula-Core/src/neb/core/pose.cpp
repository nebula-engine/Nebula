
#include <neb/core/pose.hpp>

neb::core::pose::pose():
	pos_(0.0,0.0,0.0,1.0)
{};
neb::core::pose::pose(neb::core::pose const & rhs):
	pos_(rhs.pos_),
	rot_(rhs.rot_)
{}
neb::core::pose::pose(neb::core::pose&& rhs):
	pos_(::std::move(rhs.pos_)),
	rot_(::std::move(rhs.rot_))
{}
neb::core::pose::pose(vec3 p):
	pos_(p,1.0)
{}
neb::core::pose::pose(quat q):
	pos_(0.0,0.0,0.0,1.0),
	rot_(q)
{}
neb::core::pose::pose(vec3 p, quat q):
	pos_(p,1.0),
	rot_(q)
{}
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

