#include <nebula/content/scene/physics/base.hpp>

namespace nc_sc = nebula::content::scene;
namespace nc_sc_p = nc_sc::physics;
namespace nc_sc_a = nc_sc::admin;

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
void				nc_sc_p::base::update() {

}
void				nc_sc_p::base::step(FLOAT dt)
{
	
}
void				nc_sc_p::base::render(const boost::shared_ptr<nebula::platform::renderer::base>&)
{
	
}









