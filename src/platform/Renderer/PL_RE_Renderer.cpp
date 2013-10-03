#include <nebula/platform/renderer/base.hpp>



npr::base::base()
{
	
}
npr::base::~base()
{
	
}
void	npr::base::init( boost::shared_ptr<npw::base> parent )
{
	parent_ = parent;
}
void	npr::base::shutdown()
{

}
void	npr::base::update()
{
	
}
void	npr::base::begin_render()
{
	
}
void	npr::base::end_render()
{
	
}
void	npr::base::swap()
{
	
}
void	npr::base::resize(int,int)
{
	
}
void	npr::base::look_at( bnu::vector<float> eye, bnu::vector<float> center, bnu::vector<float> up )
{
	
}
void	npr::base::draw_quad()
{
	
}
void	npr::base::draw_window_quad( int x, int y, int w, int h )
{

}
void	npr::base::draw_cube()
{
	
}
void	npr::base::draw_sphere()
{
	
}
void	npr::base::push_matrix()
{
	
}
void	npr::base::mult_matrix( bnu::matrix<float> mat )
{
	
}
void	npr::base::scale( bnu::vector<float> v )
{
	
}
void	npr::base::pop_matrix()
{
	
}
void	npr::base::light()
{
	
}
void	npr::base::unproject( int, int, int, double*, double*, double* )
{
	
}






