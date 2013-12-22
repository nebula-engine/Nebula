#include <neb/packet/basic.h>

int	neb::packet::vec3::from_math(math::vec3 const & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	
	return 0;
}
math::vec3	neb::packet::vec3::to_math()
{
	math::vec3 v;
	
	v.x = x;
	v.y = y;
	v.z = z;
	
	return v;
}
int	neb::packet::quat::from_math(math::quat const & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	
	return 0;
}
math::quat	neb::packet::quat::to_math()
{
	math::quat v;
	
	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	
	return v;
}
int	neb::packet::transform::from_math(math::transform const & v)
{
	p.from_math(v.p);
	q.from_math(v.q);
	
	return 0;
}
math::transform		neb::packet::transform::to_math() {
	
	math::transform t(p.to_math(), q.to_math());
	
	return t;
}


