#include <jess/scoped_ostream.hpp>

#include <nebula/platform/window/base.hpp>

#include <nebula/content/actor/control/base.hpp>

n34400::base::base( std::shared_ptr<n34100::base> parent ):
parent_( parent )
{
	jess::scoped_ostream sos( &jess::cout, NEB_FUNCSIG );

	NEB_ASSERT( !parent_.expired() );
}
n34400::base::~base()
{
	jess::scoped_ostream sos( &jess::cout, NEB_FUNCSIG );

}

