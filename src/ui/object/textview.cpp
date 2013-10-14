#include <nebula/define.hpp>

#include <jess/ostream.hpp>

#include <nebula/platform/renderer/base.hpp>

#include <nebula/ui/object/textview.hpp>

void	n52000::textview::render( jess::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	rnd->draw_text( x_, y_, label_ );
}
bool	n52000::textview::key_down( int k )
{
	if ( k == n20000::key::eBACKSPACE )
	{
		label_.pop_back();
		return true;
	}
	else if ( ( k >= n20000::key::a ) && ( k <= n20000::key::z ) )
	{
		label_.push_back( k );
		return true;
	}
	else if ( k == n20000::key::linefeed )
	{
		on_linefeed();
		return true;
	}
	
	return false;
}
bool	n52000::textview::key_up( int k )
{
	return false;
} 

