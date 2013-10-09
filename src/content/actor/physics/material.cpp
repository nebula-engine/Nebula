#include <jess/shared_ptr.hpp>

#include <nebula/ns.hpp>
#include <nebula/utilities/types/content/actor/types.hpp>
#include <nebula/content/actor/physics/material.hpp>



nca::physics::material::material()
{

}
void	nca::physics::material::init( jess::shared_ptr<ncaa::material> parent )
{
	parent_ = parent;
}









