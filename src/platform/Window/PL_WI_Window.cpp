
#include <nebula/platform/window/base.hpp>

npw::base::base()
{
}
npw::base::~base()
{
}
void	npw::base::init( const boost::shared_ptr<npp::base>& parent )
{
	parent_ = parent;
	//PRINTSIG;

//	 =			DynCast<Void,AR_Init>( data )->app;
	// =	DynCast<Void,AR_Init>( data )->platform;
}
void	npw::base::shutdown()
{
	//PRINTSIG;

}
void	npw::base::update()
{
	//PRINTSIG;

}








