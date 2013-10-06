#ifndef __NEBULA_CONTENT_SHAPE_PHYSICS_BASE_HPP__
#define __NEBULA_CONTENT_SHAPE_PHYSICS_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/utilities/types/content/shape/types.hpp>

namespace nebula
{
namespace content
{
namespace shape
{
namespace physics
{
class base
{
public:
	base();
	~base();
	void							init(const jess::shared_ptr<nebula::content::shape::admin::base>&);
	void							shutdown();
};
}
}
}
}

#endif
