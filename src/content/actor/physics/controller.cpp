#include <nebula/define.hpp>

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <nebula/utilities/free.hpp>
#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/actor/physics/controller.hpp>

n34200::controller::controller()
{
	jess::clog << NEB_FUNCSIG << std::endl;

}
n34200::controller::~controller()
{
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n34200::controller::init( jess::shared_ptr<n34100::base> parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	n34200::base::init( parent );
}
void	n34200::controller::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n34200::controller::update()
{
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n34200::controller::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	update_move();

	jess::shared_ptr<n34100::controller> parent = std::dynamic_pointer_cast<n34100::controller>( parent_.lock() );

		physx::PxQuat yaw( parent->yaw_, physx::PxVec3(0,1,0) );

	parent->move_ = yaw.rotate( parent->move_ );

	//jess::clog << "move_=" << parent->move_ << std::endl;

	//parent->pos_ += parent->move_ * dt;

	::physx::PxVec3 disp = parent->move_;
	::physx::PxF32 minDist = 0.1;
	::physx::PxF32 elapsedTime = dt;
	::physx::PxControllerFilters filters = 0;
	::physx::PxObstacleContext* obstacles = 0;

	//::physx::PxU32 collisionFlags = 
	px_controller_->move( disp, minDist, elapsedTime, filters, obstacles );





	// gravity for a flat world
	float y_eye = 1.0;
	float v = parent->velocity_.x;
	float y = parent->pos_.y - y_eye;

	if( y > 0 )
	{
		v -= 9.81 * dt;

		y += v * dt;

		if( y <= 0 )
		{
			y = 0;
			v = 0;
		}
	}

	parent->velocity_.y = v;
	parent->pos_.y = y + y_eye;

}
void	n34200::controller::update_move()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	jess::shared_ptr<n34100::controller> parent = std::dynamic_pointer_cast<n34100::controller>(parent_.lock());



	/** \todo
	 * add gravity
	 * make \a head and \a m a static member variable or at least a member variables
	 */

	// the following scheme provides equal magnitude for each direction and uniformly spaced directions (i.e. diagonal is at exactly 45 degrees)
	float s = 1;
	float d = 0.707;

	s *= 1.5;
	d *= 1.5;

	std::map<int,physx::PxVec3> head;
	head[0] = physx::PxVec3(  0, 0, -s );
	head[1] = physx::PxVec3(  d, 0, -d );
	head[2] = physx::PxVec3(  s, 0,  0 );
	head[3] = physx::PxVec3(  d, 0,  d );
	head[4] = physx::PxVec3(  0, 0,  s );
	head[5] = physx::PxVec3( -d, 0,  d );
	head[6] = physx::PxVec3( -s, 0,  0 );
	head[7] = physx::PxVec3( -d, 0, -d );


	std::map<int,int> m;
	m[n34100::controller::flag::eNORTH						] = 0;
	m[n34100::controller::flag::eNORTH	|	n34100::controller::flag::eEAST	] = 1;
	m[						n34100::controller::flag::eEAST	] = 2;
	m[n34100::controller::flag::eSOUTH	|	n34100::controller::flag::eEAST	] = 3;
	m[n34100::controller::flag::eSOUTH						] = 4;
	m[n34100::controller::flag::eSOUTH	|	n34100::controller::flag::eWEST	] = 5;
	m[						n34100::controller::flag::eWEST	] = 6;
	m[n34100::controller::flag::eNORTH	|	n34100::controller::flag::eWEST	] = 7;

	// ignore all other flags
	int f = parent->flag_ & (
			n34100::controller::flag::eNORTH |
			n34100::controller::flag::eSOUTH |
			n34100::controller::flag::eEAST |
			n34100::controller::flag::eWEST );

	// find vector for move flag
	auto it = m.find( f );

	if ( it != m.end() )
	{
		parent->move_ = head[it->second];

		//jess::cout << "move_=" << parent->move_ << std::endl;
	}
	else
	{
		parent->move_ = physx::PxVec3(0,0,0);

		//jess::cout << "move_=" << parent->move_ << std::endl;
	}
}


