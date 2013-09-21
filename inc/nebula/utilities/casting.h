#ifndef _UTILITIES_CASTING_H
#define _UTILITIES_CASTING_H

#include <jess/except/except.hpp>




template <class FROM, class TO> TO* DynCast( FROM* f )
{
	TO* t = 0;
	
	if ( !f ) throw except("null pointer");
	
	t = dynamic_cast<TO*>( f );
	
	if ( f==0 ) throw except("dynamic_cast failed");

	return t;
}



#endif




