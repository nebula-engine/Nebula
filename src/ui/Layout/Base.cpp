

#include <tinyxml/tinyxml.h>

#include <string>

#include <nebula/ui/object/base.hpp>

#include <nebula/ui/layout/base.hpp>

void	n51000::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	n51000::base::load_xml( std::string file_name )
{

}
void	n51000::base::render( jess::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	jess::clog << "objects_.size()=" << objects_.map_.size() << std::endl;
	
	objects_.foreach
		(
		 std::bind( &n52000::base::render, std::placeholders::_1, rnd )
		);
}
