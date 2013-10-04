#include <memory>


//#include <NebulaAPI.h>



#include <box_client/framework/app.hpp>


int main( int argc, char** argv )
{
	//PRINTSIG;
	
	boost::shared_ptr<box_client::framework::app> a( new box_client::framework::app() );
	
	//app->GetOpt( argc, argv, "h" );
	
	
	a->init();
	
	a->MainLoopSequ();
	
	a->shutdown();
	
	return 1;
}









