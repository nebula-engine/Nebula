#include <nebula/content/actor/physics/rigid_dynamic.hpp>

n34200::rigid_dynamic::rigid_dynamic( std::shared_ptr<n34100::base> parent ):
	actor( parent ),
	rigid_body( parent )
{

}
n34200::rigid_dynamic::~rigid_dynamic()
{

}
void	n34200::rigid_dynamic::init()
{
	n34200::rigid_body::init();
}
void	n34200::rigid_dynamic::shutdown()
{

}
void	n34200::rigid_dynamic::update()
{

}
void	n34200::rigid_dynamic::step(float)
{
	
}
void	n34200::rigid_dynamic::render( std::shared_ptr<n23000::base> rnd )
{

}
void	n34200::rigid_dynamic::create_shape()
{

}








