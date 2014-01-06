#ifndef __NEBULA_CONFIG_H__
#define __NEBULA_CONFIG_H__

#define NEB_INSTALL_DIR "/usr/local"

#define NEBULA_DEBUG_0_FUNCTION printf("%s\n", __PRETTY_FUNCTION__);
#define NEBULA_DEBUG_1_FUNCTION

#include <memory>

#include <gal/map.h>

namespace neb
{
	class shape;

	namespace network
	{
		class server;
		class client;
		typedef std::shared_ptr<server>		server_shared;
		typedef std::shared_ptr<client>		client_shared;
	}
	namespace packet
	{
		struct packet;
	}
	namespace active_transform
	{
		struct node_raw;
		class node;
		struct set_raw;
		class set;
	}

	class app;
	typedef std::shared_ptr<app>	app_shared;
	typedef std::weak_ptr<app>	app_weak;

	namespace scene
	{
		class scene;
		typedef std::shared_ptr<scene>	scene_shared;
		typedef std::weak_ptr<scene>	scene_weak;
		typedef gal::map<scene>		scene_map;
	}
	class simulation_callback;
	namespace actor
	{
		class Base;
		class Actor;
		class Rigid_Actor;
		class Rigid_Body;
		class Rigid_Dynamic;
		class Rigid_Static;
		class empty;


		typedef std::shared_ptr<Base> Base_shared;
		typedef std::weak_ptr<Base> Base_weak;
	}
}

#endif
