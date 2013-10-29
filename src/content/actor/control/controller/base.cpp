#include <jess/scoped_ostream.hpp>

#include <nebula/platform/window/base.hpp>

#include <nebula/content/actor/control/controller/base.hpp>

n34400::controller::base::base( jess::shared_ptr<n34100::base> parent ):
	n34400::base( parent )
{
	jess::scoped_ostream sos( &jess::cout, NEB_FUNCSIG );

}
n34400::controller::base::~base()
{
	jess::scoped_ostream sos( &jess::cout, NEB_FUNCSIG );

}


