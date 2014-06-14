#ifndef __NEBULA_CONTROL_RIGID_BODY_CONTROL_H__
#define __NEBULA_CONTROL_RIGID_BODY_CONTROL_H__

#include <Nebula/Actor/RigidActor/Base.hh>
#include <Nebula/config.hh>

namespace px { namespace core {
	namespace actor {
		namespace control {
			namespace rigidbody {
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
						Base();
						virtual ~Base() = 0;
						Base&				operator=(Base const & base);
						virtual int			key_fun(int,int,int,int);
						
						virtual void			step(double const & time, double const & dt) = 0;
						virtual vec3			f() = 0;
						virtual vec3			t() = 0;

						virtual void			serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
						virtual void			serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version);
					private:

					public:
						neb::core::actor::Base_w		actor_;

						quat			q_target_;
						vec3			p_target_;

						vec3			f_;
						vec3			t_;

						vec3			force_;
						vec3			torque_;

		
						struct
						{
							boost::signals2::connection	key_fun_;
						} conn_;

						//gal::control::control		pid_;

				};
				class Manual: public neb::core::actor::Control::RigidBody::Base {
					void				step(double dt);
					vec3			f();
					vec3			t();

				};
				class PD: public neb::core::actor::Control::RigidBody::Base {
					void				step(double dt);
					vec3			f();
					vec3			t();
				};
			}
		}
	}
}
#endif








