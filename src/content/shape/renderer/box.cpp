#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <jess/free.hpp>

#include <nebula/content/actor/admin/rigid_actor.hpp>
#include <nebula/content/shape/admin/box.hpp>

#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/shape/renderer/box.hpp>
#include <nebula/ns.hpp>

ncsr::box::box()
{

}
ncsr::box::~box()
{

}
void	ncsr::box::init( jess::shared_ptr<ncs::admin::box> parent )
{
	parent_ = parent;
}
void	ncsr::box::shutdown()
{
	
}
void	ncsr::box::render( jess::shared_ptr<nebula::platform::renderer::base>& rnd )
{
	jess::shared_ptr<ncs::admin::box> parent = std::dynamic_pointer_cast<ncs::admin::box>( parent_.lock() );
	
	jess::assertion( bool(rnd) ); // throw Except("renderer is null");
	
	
	jess::assertion( bool(parent) ); // throw Except("m_co_sh_ad_box is null");


	jess::shared_ptr<nca::admin::rigid_actor> grandparent = parent->parent_.lock();
	
	//jess::assertion( bool(grandparent) ); // throw Except("m_co_sh_ad_box->Get_ncaa::rigid_actor() is null");
	
	// store transform
	bnu::matrix<FLOAT> pose = grandparent->get_pose();
	
	
	rnd->push_matrix();
	rnd->mult_matrix( pose );
	rnd->scale( parent->get_scale() );
	rnd->draw_cube();
	rnd->pop_matrix();
}











