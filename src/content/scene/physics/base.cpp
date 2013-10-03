#include <nebula/content/scene/physics/base.hpp>


nc_sc_p::base::base()
{
	
}
nc_sc_p::base::base(const nc_sc_p::base& cpy)
{
	//printf("Copy Constructor------");
}
nc_sc_p::base::~base()
{
	
}
nc_sc_p::base&			nc_sc_p::base::operator=(const nc_sc_p::base& cpy)
{
	return *this;
}
void				nc_sc_p::base::init(const boost::shared_ptr<nc_sc_a::base>&)
{

}
void				nc_sc_p::base::shutdown()
{

}
void				nc_sc_p::base::update()
{

}
void				nc_sc_p::base::step(FLOAT dt)
{
	
}
void				nc_sc_p::base::render(const boost::shared_ptr<nebula::platform::renderer::base>&)
{
	
}
void				nc_sc_p::base::register_actor( boost::shared_ptr<ncaa::actor> )
{

}








