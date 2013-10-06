#include <nebula/platform/renderer/base.hpp>

#include <nebula/platform/window/base.hpp>

npw::base::base()
{
}
npw::base::~base()
{
}
void	npw::base::init( const jess::shared_ptr<npp::base>& parent )
{
	parent_ = parent;
	//jess::clog << NEB_FUNCSIG << std::endl;

//	 =			DynCast<Void,AR_Init>( data )->app;
	// =	DynCast<Void,AR_Init>( data )->platform;
}
void	npw::base::shutdown()
{
	//jess::clog << NEB_FUNCSIG << std::endl;

}
void	npw::base::update()
{
	//jess::clog << NEB_FUNCSIG << std::endl;

}
int	npw::base::lookup_key( int k )
{
	return keys_[k];
}







