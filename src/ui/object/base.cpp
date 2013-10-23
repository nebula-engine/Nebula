#include <cstring>
#include <algorithm>

#include <nebula/ui/object/base.hpp>

n52000::base::base():
	label_(0)
{
	label_ = new char[16];
	
	memset( (void *)label_, '\0', 16 );
}
void	n52000::base::set_label( char const * cstr )
{
	memcpy( (void *)label_, (const void *)cstr, std::min( strlen( cstr ), strlen( label_ ) ) );
}

