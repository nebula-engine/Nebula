#ifndef NEBULA_MESSAGE_TYPES
#define NEBULA_MESSAGE_TYPES

namespace neb {
	/** @brief %Message */
	namespace message {

		class base;
		class IBase;
		class OBase;

		/** @brief %Actor */
		namespace actor {

			class Create;
			class ICreate;
			class OCreate;

			class Update;
			class IUpdate;
			class OUpdate;


			/** @brief %Control */
			namespace Control {
				/** @brief %rigidbody */
				namespace rigidbody {
					class Create;
					class ICreate;
					class OCreate;

					class Update;
					class IUpdate;
					class OUpdate;

				}
			}
		}
	}
}

#endif

