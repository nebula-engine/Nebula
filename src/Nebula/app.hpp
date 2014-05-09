#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

//#include <galaxy/flag.hpp>
//#include <galaxy/timer/timer_set.hpp>

#include <Nebula/Graphics/window/window.hpp>

#include <Nebula/Types.hpp>
#include <Nebula/Util/Shared.hpp>
#include <Nebula/network2/server.hpp>
#include <Nebula/network2/client.hpp>


namespace Neb {
	class app: virtual public Neb::Shared, public gal::flag {
		public:
			struct flag {
				enum e {
					SHOULD_RELEASE = 1 << 0,			
				};
			};
			app();
			void				init();

			Neb::weak_ptr<Neb::window::window>		create_window(int, int, int, int, char const *);

			Neb::Scene::scene_w				load_scene_local(Neb::Scene::desc_w);
			Neb::Scene::scene_w				load_scene_remote(Neb::Scene::desc_w);

			void				load_layout(int,char const *);

			int				step(double);
			int				loop();

			/** @name Accessors @{ */
			Neb::window::window_w			get_window(int);
			Neb::Scene::scene_w			get_scene(int);
			Neb::Scene::scene_w			get_scene(Neb::Scene::addr_w);
			Neb::Actor::Base_w			get_actor(Neb::Actor::addr_w);
			/** @} */

			void				set_should_release();

			int				activate_scene(int,int);
			int				deactivate_scene(int);
			int				activate_layout(int,int);
			int				deactivate_layout(int);


			/** @name %Network @{ */
			void				reset_server(unsigned short);
			void				reset_client(char const *, unsigned short);		
			void				send_server(boost::shared_ptr<gal::network::omessage>);
			void				send_client(boost::shared_ptr<gal::network::omessage>);
			
			int				transmit_scenes(boost::shared_ptr<gal::network::communicating>);
			
			/** @todo consider putting following functions into the messages themselves: would be cleaner that way. */
			void				recv_scene_create(std::shared_ptr<gal::network::message>);
			void				recv_actor_create(std::shared_ptr<gal::network::message>);
			void				recv_actor_update(std::shared_ptr<gal::network::message>);
			void				recv_actor_event(std::shared_ptr<gal::network::message>);
			void				recv_control_create(std::shared_ptr<gal::network::message>);
			void				recv_control_update(std::shared_ptr<gal::network::message>);
			/** @} */

			void				f(unsigned int);
			gal::flag::flag_type			f();
		public:
			unsigned int			flag_;

			//Neb::Map<Neb::window::window>	windows_;
			Neb::Map<Neb::gui::layout>		layouts_;
			Neb::Map<Neb::Scene::scene>		scenes_;

			// timer
			//gal::timer::timer_set		timer_set_;

		private:
			// network
			Neb::unique_ptr<Neb::network::server>		server_;
			Neb::unique_ptr<Neb::network::client>		client_;
	};
}

#endif





