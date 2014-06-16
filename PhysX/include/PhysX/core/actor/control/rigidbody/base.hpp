#ifndef PHYSX_CORE_ACTOR_CONTROL_RIGID_BODY_CONTROL_H__
#define PHYSX_CORE_ACTOR_CONTROL_RIGID_BODY_CONTROL_H__

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/signals2.hpp>

#include <Nebula/Util/typedef.hpp>
#include <Nebula/Graphics/Types.hh>
#include <Nebula/Core/TimeStep.hpp>

#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace control { namespace rigidbody {



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
				virtual ~base() = 0;
				base&				operator=(base const & base);

				virtual int			key_fun(sp::shared_ptr<neb::gfx::window::base>, int, int, int, int);

				virtual void			step(neb::core::TimeStep const & ts) = 0;
				virtual vec4			f() = 0;
				virtual vec4			t() = 0;

				virtual void			serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
				virtual void			serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version);
			private:

			public:
				sp::shared_ptr<phx::core::actor::rigidbody::base>		actor_;

				quat				q_target_;
				vec4				p_target_;

				vec4				f_;
				vec4				t_;

				vec4				force_;
				vec4				torque_;


				struct
				{
					boost::signals2::connection	key_fun_;
				} conn_;

				//gal::control::control		pid_;

		};
		class Manual: public phx::core::actor::control::rigidbody::base {
			void				step(neb::core::TimeStep const & ts);
			vec4				f();
			vec4				t();

		};
		class PD: public phx::core::actor::control::rigidbody::base {
			void				step(neb::core::TimeStep const & ts);
			vec4				f();
			vec4				t();
		};


}}}}}


#endif








