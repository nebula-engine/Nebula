#include <jess/ostream.hpp>

#include <nebula/platform/renderer/base.hpp>



n23000::base::base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
n23000::base::~base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::init( std::shared_ptr<n22000::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	parent_ = parent;
}
void	n23000::base::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::update()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::begin_render()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::end_render()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::swap()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::resize(int,int)
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::look_at( physx::PxVec3 eye, physx::PxVec3 center, physx::PxVec3 up )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::draw_quad()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::draw_window_quad( int x, int y, int w, int h )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::draw_cube()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n23000::base::draw_sphere()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::push_matrix()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::mult_matrix( physx::PxMat44 mat )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::scale( physx::PxVec3 v )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::pop_matrix()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::light()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n23000::base::unproject( int, int, int, double*, double*, double* )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}






