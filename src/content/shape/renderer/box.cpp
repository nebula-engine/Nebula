#include <jess/free.hpp>

#include <nebula/content/actor/admin/rigid_actor.hpp>
#include <nebula/content/shape/admin/box.hpp>

#include <nebula/platform/renderer/base.hpp>
#include <nebula/platform/renderer/scoped_matrix.hpp>

#include <nebula/content/shape/renderer/box.hpp>
#include <nebula/ns.hpp>

n35300::box::box()
{

}
n35300::box::~box()
{

}
void	n35300::box::init( jess::shared_ptr<n35100::box> parent )
{
	parent_ = parent;
}
void	n35300::box::shutdown()
{

}
void	n35300::box::render( jess::shared_ptr<nebula::platform::renderer::base> rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	jess::shared_ptr<n35100::box> parent = std::dynamic_pointer_cast<n35100::box>( parent_.lock() );
	
	jess::assertion( bool( rnd ) );	
	
	{
		n23000::scoped_matrix scoped_matrix( rnd );

		rnd->mult_matrix( parent->get_pose() );
		rnd->scale( parent->get_scale() );
		rnd->draw_cube();
	}
}











