#include <nebula/define.hpp>


#include <box_client/framework/app.hpp>


int main( int argc, char** argv )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	boost::shared_ptr<box_client::framework::app> a( new box_client::framework::app() );
	
	//app->GetOpt( argc, argv, "h" );
	
	
	a->init();
	
	a->MainLoopSequ();
	
	a->shutdown();
	
	return 1;
}









