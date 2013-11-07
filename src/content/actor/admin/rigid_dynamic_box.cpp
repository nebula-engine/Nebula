#include <nebula/define.hpp>
#include <nebula/content/shape/admin/box.hpp>
	#include <nebula/content/actor/physics/rigid_dynamic_box.hpp>
#include <nebula/content/actor/renderer/rigid_dynamic_box.hpp>

#include <nebula/content/actor/admin/rigid_dynamic_box.hpp>

n34100::rigid_dynamic_box::rigid_dynamic_box( std::shared_ptr<n32100::base> parent ):
rigid_dynamic( parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	size_ = physx::PxVec3(1,1,1);
}
n34100::rigid_dynamic_box::~rigid_dynamic_box()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::rigid_dynamic_box::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n34100::rigid_dynamic::init();

	// renderer
	renderer_.reset( new n34300::rigid_dynamic_box( shared_from_this() ) );
	renderer_->init();
	
}
void	n34100::rigid_dynamic_box::shutdown( )
{
	
}
void	n34100::rigid_dynamic_box::update( )
{
	n34100::rigid_dynamic::update();
}
void	n34100::rigid_dynamic_box::render( std::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	n34100::rigid_dynamic::render( rnd );
}
void	n34100::rigid_dynamic_box::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	
	/*
	if ( m_transform.p.y > 0.5 )
	{
		m_transform.p.x += -2 * dt;
	}
	else
	{
		m_transform.p.x += 2 * dt;
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
	jess::clog << NEB_FUNCSIG << std::endl;
	
	/// \todo request module box
	//box_ = create_box();

}























