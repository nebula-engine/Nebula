#include <nebula/define.hpp>

#include <jess/ostream.hpp>

#include <nebula/ui/object/textview.hpp>

#include <box_client/ui/layout/base.hpp>

void	bc51000::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	std::shared_ptr<n52000::textview> tv1( new n52000::textview() );
	
	tv1->x_ = 100;
	tv1->y_ = 100;
	tv1->set_label( "hello" );
	
	objects_.push<n52000::textview>( tv1 );
	
}


