#include <cstring>
#include <algorithm>

#include <nebula/ui/object/base.hpp>

n52000::base::base():
	label_length_(16),
	label_( new char [ label_length_ + 1 ] )
{

}
void	n52000::base::set_label( char const * cstr )
{
	if ( label_ )
	{
		std::memcpy( label_, cstr, std::min( ::strlen( cstr ), label_length_ ) );
	}
}

