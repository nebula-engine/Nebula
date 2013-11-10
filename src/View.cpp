
#include <assert.h>

#include <GRU/Window.h>

#include <NEB/Scene.h>
#include <NEB/View.h>


void	NEB::View::SetWindow( GRU::Window* window )
{
	assert( window );
	
	window->CallBackDisplay_ = std::bind( NEB::View::Display, this );
}
void	NEB::View::Display()
{
	if( scene )
	{
		scene->Display();
	}
}

