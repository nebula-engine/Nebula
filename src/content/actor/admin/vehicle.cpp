#include <nebula/content/actor/admin/vehicle.hpp>

n34100::vehicle::vehicle( std::shared_ptr<n32100::base> parent ):
base( parent )
{

}
n34100::vehicle::~vehicle()
{

}
void	n34100::vehicle::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	n34100::base::init();
}
void	n34100::vehicle::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n34100::vehicle::update()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::vehicle::render( std::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n34100::vehicle::step( float dt ) {
	//jess::clog << NEB_FUNCSIG << std::endl;

}






