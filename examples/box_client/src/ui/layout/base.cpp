#include <nebula/define.hpp>

#include <jess/ostream.hpp>

#include <nebula/ui/object/textview.hpp>

#include <box_client/ui/layout/base.hpp>

void	bc51000::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	jess::shared_ptr<n52000::textview> tv1( new n52000::textview() );
	tv1->x_ = 100;
	tv1->y_ = 100;
	tv1->label_ = "hello";
	
	objects_.push( tv1 );
	
	
}


