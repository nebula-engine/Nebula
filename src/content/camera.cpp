#include <boost/numeric/ublas/vector.hpp>

#include <nebula/content/actor/admin/controller.hpp>

#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/camera.hpp>

nebula::content::camera::camera()
{

}
void	nebula::content::camera::render( jess::shared_ptr<nebula::platform::renderer::base>& rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	boost::numeric::ublas::vector<FLOAT> e(3);
	boost::numeric::ublas::vector<FLOAT> c(3);
	boost::numeric::ublas::vector<FLOAT> u(3);
	
	e(0) = 0;
	e(1) = 1;
	e(2) = 7;
	
	c(0) = 0;
	c(1) = 0;
	c(2) = 0;

	u(0) = 0;
	u(1) = 1;
	u(2) = 0;
	
	//jess::clog << "hello" << std::endl;
	
	if ( controller_ )
	{
		controller_->look_at( rnd );
	}
	else
	{
		rnd->look_at(e, c, u);
	}

	jess::clog << NEB_FUNCSIG << " exit" << std::endl;
}





