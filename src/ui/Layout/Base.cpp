

#include <tinyxml/tinyxml.h>

#include <string>

#include <nebula/ui/object/base.hpp>

#include <nebula/ui/layout/base.hpp>

void	nul::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

}
void	nul::base::load_xml( std::string file_name )
{

}
void	nul::base::render( jess::shared_ptr<npr::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	jess::clog << "objects_.size()=" << objects_.map_.size() << std::endl;
	
	objects_.foreach
		(
		 std::bind( &nuo::base::render, std::placeholders::_1, rnd )
		);
}
