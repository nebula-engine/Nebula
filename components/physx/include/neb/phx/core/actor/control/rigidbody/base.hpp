#ifndef PHYSX_CORE_ACTOR_CONTROL_RIGID_BODY_CONTROL_H__
#define PHYSX_CORE_ACTOR_CONTROL_RIGID_BODY_CONTROL_H__

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/signals2.hpp>

#include <gal/etc/timestep.hpp>

#include <neb/core/util/typedef.hpp>

#include <neb/phx/core/actor/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace control { namespace rigidbody {



		/** @brief Rigid Body
		 * An object (what did I mean by 'object' here, an actor?) makes no distinction between local and remote.
		 * In a remote scene, the actor will send a control update message.
		 * In a local scene, the actor will call upon stored values; it makes no difference to the
		 * actor whether these value were set by calls to key_fun or by a control update message.
		 * This creates requirements for how control works. All infomation needed to determine 
		 * force and torque at a given point in time must be stored in raw.
		 **/
		class base {
			public:
				base();
				virtual ~base() {}
				base&				operator=(base const & base);

				virtual int			key_fun(std::shared_ptr<neb::gfx::window::base>, int, int, int, int);

				virtual void			step(gal::etc::timestep const & ts) = 0;
				virtual vec3			f_body() = 0;
				virtual vec3			t_body() = 0;
				virtual vec3			f_global() = 0;
				virtual vec3			t_global() = 0;

				virtual void			serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
				virtual void			serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version);
			private:

			public:
				std::weak_ptr<neb::phx::core::actor::rigidbody::base>		actor_;

				quat				q_target_;
				vec3				p_target_;

				vec3				f_;
				vec3				t_;

				vec3				force_;
				vec3				torque_;


				struct
				{
					boost::signals2::connection	key_fun_;
				} conn_;

				//gal::control::control		pid_;

		};
		class manual: public neb::phx::core::actor::control::rigidbody::base {
			public:
				virtual ~manual() {}
				void				step(gal::etc::timestep const & ts);
				virtual vec3			f_body();
				virtual vec3			t_body();
				virtual vec3			f_global();
				virtual vec3			t_global();

		};
		class pd: public neb::phx::core::actor::control::rigidbody::base {
			public:
				virtual ~pd() {}
				void				step(gal::etc::timestep const & ts);

				vec3				getOrientationError();

				virtual vec3			f_body();
				virtual vec3			t_body();
				virtual vec3			f_global();
				virtual vec3			t_global();
		};


}}}}}}


#endif








