#include <memory>


//#include <NebulaAPI.h>



#include <Framework/Sample.h>

using namespace std;

int main( int argc, char** argv )
{
	//PRINTSIG;
	
	boost::shared_ptr<Sample> a( new Sample() );
	
	//app->GetOpt( argc, argv, "h" );
	
	
	a->init();
	
	a->MainLoopSequ();
	
	a->shutdown();
	
	return 1;
}









