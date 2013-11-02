#include <jess/free.hpp>

#include <nebula/platform/renderer/base.hpp>
#include <nebula/platform/renderer/scoped_matrix.hpp>
#include <nebula/content/actor/admin/rigid_actor.hpp>
#include <nebula/content/shape/admin/plane.hpp>

#include <nebula/content/shape/renderer/plane.hpp>

n35300::plane::plane( std::shared_ptr<n35100::base> parent ):
	n35300::base( parent )
{
	
}
n35300::plane::~plane()
{
	
}
void	n35300::plane::init()
{
	n35300::base::init();
}
void	n35300::plane::shutdown()
{

}
void	n35300::plane::render( std::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	std::shared_ptr<n35100::plane> parent = std::dynamic_pointer_cast<n35100::plane>( parent_.lock() );
	
	{
		n23000::scoped_matrix scoped_matrix( rnd );
		
		rnd->mult_matrix( parent->pose_ );
		rnd->scale( parent->get_scale() );
		rnd->draw_quad();
	}
}











