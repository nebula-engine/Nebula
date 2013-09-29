#include <platform/Renderer/PL_RE_Renderer.h>

#include <content/actor/Admin/ncaa::base.h>





#include <content/animation/frame.h>


void	nebula::content::animation::frame::Step(FLOAT dt)
{
	auto it = m_children.begin();
	for ( ; it != m_children.end(); it++ ) {
		(*it)->Step(dt);
	}
}
void	nebula::content::animation::frame::AddChild(nebula::content::animation::frame* f) {
	m_children.push_back(f);
}
void	nebula::content::animation::frame::Addactor(nebula::content::actor::admin::base* a) {
	m_actors.push_back(a);
}


	nebula::content::animation::translation::translation(boost::numeric::ublas::vector<FLOAT>& v) {
	m_rate = v;
}
void	nebula::content::animation::translation::Step(FLOAT dt) {
	//m_pose.p += m_rate * dt;

	nebula::content::animation::frame::Step(dt);
}






