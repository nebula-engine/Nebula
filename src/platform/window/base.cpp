#include <nebula/platform/renderer/base.hpp>

#include <nebula/platform/window/base.hpp>

n22000::base::base()
{
}
n22000::base::~base()
{
}
void	n22000::base::init( jess::shared_ptr<n21000::base> parent )
{
	parent_ = parent;
	//jess::clog << NEB_FUNCSIG << std::endl;

//	 =			DynCast<Void,AR_Init>( data )->app;
	// =	DynCast<Void,AR_Init>( data )->platform;
}
void	n22000::base::shutdown()
{
	//jess::clog << NEB_FUNCSIG << std::endl;

}
void	n22000::base::update()
{
	//jess::clog << NEB_FUNCSIG << std::endl;

}
int	n22000::base::lookup_key( int k )
{
	return keys_[k];
}







