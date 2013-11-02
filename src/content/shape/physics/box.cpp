#include <jess/ostream.hpp>

#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/shape/physics/box.hpp>

n35200::box::box( std::shared_ptr<n35100::base> parent ):
	n35200::base( parent )
{

}
n35200::box::~box()
{

}
void	n35200::box::init()
{
	n35200::base::init();

	create_shape();
}
void	n35200::box::shutdown()
{

}
void	n35200::box::create_shape()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}




