#include <nebula/platform/renderer/base.hpp>



npr::base::base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
npr::base::~base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::init( jess::shared_ptr<npw::base> parent )
{
		// log
	jess::clog << NEB_FUNCSIG << std::endl;


parent_ = parent;
}
void	npr::base::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::update()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::begin_render()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::end_render()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::swap()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::resize(int,int)
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::look_at( bnu::vector<float> eye, bnu::vector<float> center, bnu::vector<float> up )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::draw_quad()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::draw_window_quad( int x, int y, int w, int h )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::draw_cube()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	npr::base::draw_sphere()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::push_matrix()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::mult_matrix( bnu::matrix<float, bnu::column_major> mat )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::scale( bnu::vector<float> v )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::pop_matrix()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::light()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	npr::base::unproject( int, int, int, double*, double*, double* )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}






