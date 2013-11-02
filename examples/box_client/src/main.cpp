#include <nebula/define.hpp>


#include <box_client/framework/app.hpp>


int main( int argc, char** argv )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	std::shared_ptr<box_client::framework::app> a( new box_client::framework::app() );
	
	//app->GetOpt( argc, argv, "h" );
	
	try
	{
	a->init();
	
	a->MainLoopSequ();
	
	a->shutdown();
	}
	catch ( std::exception& e )	
	{
		std::cout << "caught: " << e.what() << std::endl;
	}


	return 1;
}









