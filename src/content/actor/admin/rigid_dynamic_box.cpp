#include <nebula/define.hpp>
#include <nebula/content/shape/admin/box.hpp>

#if defined(__PHYSX__)
	#include <nebula/content/actor/physics/physx/rigid_dynamic_box.hpp>
#else
	#include <nebula/content/actor/physics/rigid_dynamic_box.hpp>
#endif

#include <nebula/content/actor/renderer/rigid_dynamic_box.hpp>



#include <nebula/content/actor/admin/rigid_dynamic_box.hpp>

//template class jess::shared_ptr<n34200::base>;
//template void jess::shared_ptr<n34200::base>::create<n34200::rigid_dynamic_box>( std::fun30000tion<void(jess::shared_ptr<n34200::rigid_dynamic_box>)> );

n34100::rigid_dynamic_box::rigid_dynamic_box()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
	x_ = 1;
	y_ = 1;
	z_ = 1;
}
n34100::rigid_dynamic_box::~rigid_dynamic_box()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::rigid_dynamic_box::init( jess::shared_ptr<n32100::base> parent )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	n34100::rigid_dynamic::init( parent );

	// physics
#ifdef __PHYSX
	physics_.reset( new n34200p::rigid_dynamic_box );
#else
	physics_.reset( new n34200::rigid_dynamic_box );
#endif
	physics_->init( shared_from_this() );
	
	// renderer
	renderer_.reset( new n34300::rigid_dynamic_box );
	renderer_->init( shared_from_this() );
}
void	n34100::rigid_dynamic_box::shutdown( )
{
	
}
void	n34100::rigid_dynamic_box::update( )
{
	n34100::rigid_dynamic::update();
}
void	n34100::rigid_dynamic_box::render( jess::shared_ptr<n23000::base> rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	n34100::rigid_dynamic::render( rnd );
}
void	ncaa::rigid_dynamic_box::step( float dt )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
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
void	n34100::rigid_dynamic_box::create_shapes()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	box_ = create_box();

}























