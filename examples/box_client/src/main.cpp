#include <memory>


//#include <NebulaAPI.h>



#include <Framework/Sample.h>

using namespace std;

int main( int argc, char** argv )
{
	//PRINTSIG;
	
	Sample* app = new Sample();
	
	//app->GetOpt( argc, argv, "h" );
	
	AR_Init i;
	i.app = app;

	app->VInit( &i );
	
	app->MainLoopSequ();
	
	app->VShutDown();
	
	delete app;
	
	return 1;
}









