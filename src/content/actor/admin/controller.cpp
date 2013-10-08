#include <boost/numeric/ublas/io.hpp>

#include <nebula/define.hpp>

#include <nebula/utilities/free.hpp>

#include <nebula/platform/renderer/base.hpp>
#include <nebula/platform/key.hpp>
#include <nebula/platform/window/base.hpp>

#include <nebula/content/actor/physics/controller.hpp>
#include <nebula/content/actor/renderer/controller.hpp>


#include <nebula/content/actor/admin/controller.hpp>

ncaa::controller::controller()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
ncaa::controller::~controller()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
ncaa::controller::controller( ncaa::controller const & act )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	ncaa::controller::init( jess::shared_ptr<nc_sc_a::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	// init parent
	ncaa::base::init( parent );

	
	flag_ = 0;

	yaw_ = 0;
	pitch_ = 0;
	
	pos_ = bnu::zero_vector<FLOAT>(3);
	pos_(2) = 2.0;
	
	key_flag_[nebula::platform::key::w] = flag::eNORTH;
	key_flag_[nebula::platform::key::s] = flag::eSOUTH;
	key_flag_[nebula::platform::key::a] = flag::eWEST;
	key_flag_[nebula::platform::key::d] = flag::eEAST;
	
	key_down_event_[nebula::platform::key::r] = event::eRESET_VIEW_ANGLES;

	jess::shared_ptr<ncaa::base> this_ptr( shared_from_this() );
	
	//jess::cout << "not reached" << std::endl;
	
	// physics
	physics_.reset( new ncap::controller );
	physics_->init( this_ptr );
	
	// renderer
	renderer_.reset( new ncar::controller );
	renderer_->init( this_ptr );	
}
void	ncaa::controller::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	ncaa::controller::update()
{
	ncaa::base::update();
}
void	ncaa::controller::step( FLOAT dt )
{
	ncaa::base::step( dt );
}
void	ncaa::controller::render( jess::shared_ptr<npr::base> rnd )
{
}
void	ncaa::controller::create_shapes()
{

}
void	ncaa::controller::look_at( jess::shared_ptr<npr::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	bnu::matrix<float> rot = bnu::identity_matrix<FLOAT,bnu::column_major>( 3 );
	
	//jess::clog << pitch_ << " " << yaw_ << std::endl;
	//std::cout << "rot=" << rot << std::endl;





	rot = prod( rot, nebula::utilities::matrix_yaw( yaw_ ) );
	
	//std::cout << "rot=" << rot << std::endl;


	
	rot = prod( rot, nebula::utilities::matrix_pitch( pitch_ ) );

	//std::cout << "rot=" << rot << std::endl;

		
	

	//rnd->mult_matrix( pose_ );
	
	//bnu::  math::quaternion rot(0,0,0,1);
	
	//boost::math::quaternion	yaw( 0, 1, 0, yaw_ );
	//boost::math::quaternion pitch( 1, 0, 0, pitch_ );
	
	//rot *= pitch;
	//rot *= yaw;
	
	up_ = bnu::unit_vector<float>(3,1); //Math::Vec3f(0,1,0);
	look_ = bnu::unit_vector<float>(3,2); //Math::Vec3f(0,0,-1);
	look_ *= -1.0;
	
	//jess::clog << up_ << std::endl;
	//jess::clog << look_ << std::endl;
	
	up_ = prod( rot, up_ );
	look_ = prod( rot, look_ );

	//jess::clog << up_ << std::endl;
	//jess::clog << look_ << std::endl;
	//jess::clog << pos_ + look_ << std::endl;
	
	rnd->look_at( pos_, pos_ + look_, up_ );
}
void	ncaa::controller::process_event( int evnt )
{
	switch ( evnt )
	{
	case event::eRESET_VIEW_ANGLES:
		printf("reset viewing angles\n");
		yaw_ = 0;
		pitch_ = 0;
		break;
	}
}
void	ncaa::controller::handle_key_up(int k, int window_no)
{

	jess::clog << NEB_FUNCSIG << std::endl;

	// unset flag
	UINT f = key_flag_[k];
	flag_ &= ~( f );
	
	// trigger event
	int evnt = key_up_event_[k];
	process_event(evnt);

}
void	ncaa::controller::handle_key_down(int k, int window_no)
{

	jess::clog << NEB_FUNCSIG << std::endl;
	
	// set flag
	UINT f = key_flag_[k];
	flag_ |= f;
	
	// trigger event
	int evnt = key_down_event_[k];
	process_event(evnt);
}
void	ncaa::controller::handle_pointer_motion( int x, int y )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	yaw_ -= x * 0.001;
	pitch_ -= y * 0.001;
}

























