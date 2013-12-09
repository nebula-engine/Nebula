
#include <assert.h>

#include <glutpp/window.h>

#include <neb/scene.h>
#include <neb/view.h>
#include <neb/camera.h>

neb::view::view():
	scene_( NULL )
{

}
void	neb::view::delete_scene()
{
	scene_.reset();
}

