#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <jess/free.hpp>
#include <jess/ostream.hpp>

#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/actor/physics/controller.hpp>

namespace bnu = boost::numeric::ublas;
namespace nca = nebula::content::actor;

nca::physics::controller::controller()
{
}
nca::physics::controller::~controller()
{
}
void	nca::physics::controller::init( jess::shared_ptr<ncaa::base>& parent )
{
	ncap::base::init( parent );
}
void	nca::physics::controller::shutdown()
{

}
void	nca::physics::controller::update()
{

}
void	nca::physics::controller::step(FLOAT dt)
{
	update_move();
	
	
	/*
	// create rotation
	Math::Vec4f yaw( Math::Vec3f(0,1,0), controller->m_a_yaw );
	
	/// transform m_move into global frame
	controller->m_move *= yaw;
	
	controller->m_pos += controller->m_move * s->dt;
	*/
}
void	nca::physics::controller::update_move()
{
	jess::shared_ptr<nca::admin::controller> parent = boost::dynamic_pointer_cast<nca::admin::controller>(parent_.lock());
	
	
	/** \todo
	* add gravity
	* make \a head and \a m a static member variable or at least a member variables
	*/

	// the following scheme provides equal magnitude for each direction and uniformly spaced directions (i.e. diagonal is at exactly 45 degrees)
	FLOAT s = 1;
	FLOAT d = 0.707;
	
	s *= 1.5;
	d *= 1.5;
	
	bnu::matrix<FLOAT> head(8,3);
	head(0,0) = 0;		head(0,1) = 0;		head(0,2) = -s;
	head(1,0) = d;		head(1,1) = 0;		head(1,2) = -d;
	head(2,0) = s;		head(2,1) = 0;		head(2,2) = 0;
	head(3,0) = d;		head(3,1) = 0;		head(3,2) = d;
	head(4,0) = 0;		head(4,1) = 0;		head(4,2) = s;
	head(5,0) = -d;		head(5,1) = 0;		head(5,2) = d;
	head(6,0) = -s;		head(6,1) = 0;		head(6,2) = 0;
	head(7,0) = -d;		head(7,1) = 0;		head(7,2) = -d;

	
	std::map<int,int> m;
	m[nca::admin::controller::flag::eNORTH							] = 0;
	m[nca::admin::controller::flag::eNORTH	|	nca::admin::controller::flag::eEAST	] = 1;
	m[						nca::admin::controller::flag::eEAST	] = 2;
	m[nca::admin::controller::flag::eSOUTH	|	nca::admin::controller::flag::eEAST	] = 3;
	m[nca::admin::controller::flag::eSOUTH							] = 4;
	m[nca::admin::controller::flag::eSOUTH	|	nca::admin::controller::flag::eWEST	] = 5;
	m[						nca::admin::controller::flag::eWEST	] = 6;
	m[nca::admin::controller::flag::eNORTH	|	nca::admin::controller::flag::eWEST	] = 7;
	
	/// find vector for move flag
	auto it = m.find( parent->flag_ );
	
	if ( it != m.end() )
	{
		parent->move_ = bnu::matrix_row<bnu::matrix<FLOAT> >(head,it->second);
		

		jess::cout << "move_";
		jess::cout << std::endl;
		jess::cout << parent->move_ << std::endl;
	}
	else
	{
		parent->move_ = bnu::zero_vector<FLOAT>(3);
		
		jess::cout << "move_" << std::endl << parent->move_ << std::endl;
	}
}








