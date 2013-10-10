#include <nebula/define.hpp>

#include <jess/ostream.hpp>

#include <nebula/platform/renderer/base.hpp>

#include <nebula/ui/object/textview.hpp>

void	n52000::textview::render( jess::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	rnd->draw_text( x_, y_, label_ );
}

