#include <nebula/define.hpp>


#include <box_client/framework/app.hpp>


int main( int argc, char** argv )
{
	NEB_LOG_FUNC
	/*
	jess::clog << NEB_FUNCSIG << std::endl;
	
	std::shared_ptr<bc10000::app> a( new bc10000::app() );
		
	try
	{
		a->init();

		a->MainLoopSequ();

		a->shutdown();
	}
	catch ( std::exception& e )	
	{
		printf( "caught: %s\n", e.what() );
	}
	*/
		
	std::shared_ptr<n10000::kernel> k( new n10000::kernel() );
	
	std::shared_ptr<n10000::module_desc> d( new n10000::module_desc() );
	
	d->type = n10000::module::type::view;
	
	
	
	
	std::shared_ptr<n10000::module> m = k->request_module( d );
	
	return 0;
}









