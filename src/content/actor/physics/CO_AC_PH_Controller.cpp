#include <jess/free.hpp>

#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/actor/physics/controller.hpp>

namespace nca = nebula::content::actor;

nca::physics::controller::controller()
{
}
nca::physics::controller::~controller()
{
}
void	nca::physics::controller::init(const boost::shared_ptr<nca::admin::controller>& parent)
{
	jess::assertion(parent);
	parent_ = parent;
}
void	nca::physics::controller::shutdown()
{

}
void	nca::physics::controller::update()
{

}
void	nca::physics::controller::step(FLOAT dt)
{
	UpdateMove();
	
	
	/*
	// create rotation
	Math::Vec4f yaw( Math::Vec3f(0,1,0), controller->m_a_yaw );
	
	/// transform m_move into global frame
	controller->m_move *= yaw;
	
	controller->m_pos += controller->m_move * s->dt;
	*/
}
void	nca::physics::controller::UpdateMove() {
	nca::admin::controller* controller = Ptr<CO_AC_AD_Controller>::Get_Or_Error();


	/// TODO: add gravity

	/// TODO: make static member variables
	FLOAT s = 1;
	FLOAT d = 0.707;

	s *= 1.5;
	d *= 1.5;

	FLOAT h000 = s;
	FLOAT h045 = d;
	FLOAT h090 = s;
	FLOAT h135 = d;
	FLOAT h180 = s;
	FLOAT h225 = d;
	FLOAT h270 = s;
	FLOAT h315 = d;

	map<int,Math::Vec3f> m;
	m[nca::admin::controller::Flag::eFORWARD] =										Math::Vec3f(  0,    0, -h000 );
	m[nca::admin::controller::Flag::eFORWARD	| CO_AC_AD_Controller::Flag::eRIGHT] =	Math::Vec3f(  h045, 0, -h045 );
	m[nca::admin::controller::Flag::eRIGHT] =											Math::Vec3f(  h090, 0,  0 );
	m[nca::admin::controller::Flag::eBACKWARD	| CO_AC_AD_Controller::Flag::eRIGHT] =	Math::Vec3f(  h135, 0,  h135 );
	m[nca::admin::controller::Flag::eBACKWARD] =										Math::Vec3f(  0,    0,  h180 );
	m[nca::admin::controller::Flag::eBACKWARD	| CO_AC_AD_Controller::Flag::eLEFT] =	Math::Vec3f( -h225, 0,  h225 );
	m[nca::admin::controller::Flag::eLEFT] =											Math::Vec3f( -h270, 0,  0 );
	m[nca::admin::controller::Flag::eFORWARD	| CO_AC_AD_Controller::Flag::eLEFT] =	Math::Vec3f( -h315, 0, -h315 );

	/// find vector for move flag
	auto it = m.find(controller->m_flag);

	if ( it != m.end() ) {
		controller->m_move = it->second;

		//printf("move ");
		//controller->m_move.print();
	}
	else {
		controller->m_move = Math::Vec3f();

		//printf("default move ");
		//controller->m_move.print();
	}
}








