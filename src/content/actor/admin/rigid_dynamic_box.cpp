#include <boost/bind.hpp>

#include <nebula/content/shape/admin/box.hpp>

#include <nebula/content/actor/physics/rigid_dynamic_box.hpp>
#include <nebula/content/actor/physics/physx/rigid_dynamic_box.hpp>
#include <nebula/content/actor/renderer/rigid_dynamic_box.hpp>



#include <nebula/content/actor/admin/rigid_dynamic_box.hpp>

template class jess::shared_ptr<ncap::base>;
template void jess::shared_ptr<ncap::base>::create<ncap::rigid_dynamic_box>( boost::function<void(boost::shared_ptr<ncap::rigid_dynamic_box>)> );

ncaa::rigid_dynamic_box::rigid_dynamic_box()
{
	//PRINTSIG;
	
	x_ = 1;
	y_ = 1;
	z_ = 1;
}
ncaa::rigid_dynamic_box::~rigid_dynamic_box()
{
	//PRINTSIG;
}
void	ncaa::rigid_dynamic_box::init( const boost::shared_ptr<nc_sc_a::base>& parent )
{
	//PRINTSIG;
	ncaa::rigid_dynamic::init( parent );

	// physics
#ifdef __PHYSX
	physics_.create<ncapp::rigid_dynamic_box>( boost::bind( &ncapp::rigid_dynamic_box::init, _1, shared_from_this() ) );
#else
	physics_.create<ncap::rigid_dynamic_box>( boost::bind( &ncap::rigid_dynamic_box::init, _1, shared_from_this() ) );
#endif
	
	// renderer
	renderer_.create<ncar::rigid_dynamic_box>( boost::bind( &ncar::rigid_dynamic_box::init, _1, shared_from_this() ) );
}
void	ncaa::rigid_dynamic_box::shutdown( )
{
	
}
void	ncaa::rigid_dynamic_box::update( )
{
	ncaa::rigid_dynamic::update();
}
void	ncaa::rigid_dynamic_box::render( const boost::shared_ptr<npr::base>& rnd )
{
	//PRINTSIG;

	ncaa::rigid_actor::render( rnd );
}
void	ncaa::rigid_dynamic_box::step(  )
{
	//PRINTSIG;
	/*
	AR_Step* s = DynCast<Void,AR_Step>( v );
	
	if ( m_transform.p.y > 0.5 ) {
		m_transform.p.x += -2 * s->dt;
	} else {
		m_transform.p.x += 2 * s->dt;
	}

	if ( m_transform.p.x > 3 ) {
		m_transform.p.y = 1;
	} else if ( m_transform.p.x < -3 ) {
		m_transform.p.y = 0;
	}
	*/
}
void	ncaa::rigid_dynamic_box::create_shapes()
{
	//PRINTSIG;

	create_box( box_ );

}























