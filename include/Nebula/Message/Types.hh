#ifndef NEBULA_MESSAGE_TYPES
#define NEBULA_MESSAGE_TYPES

namespace neb {
	/** @brief %Message */
	namespace Message {

		class Base;
		class IBase;
		class OBase;


		typedef std::shared_ptr<Base>		Base_s;
		typedef std::shared_ptr<IBase>		IBase_s;
		typedef std::shared_ptr<OBase>		OBase_s;

		/** @brief %Actor */
		namespace Actor {

			class Create;
			class ICreate;
			class OCreate;

			class Update;
			class IUpdate;
			class OUpdate;

			typedef std::shared_ptr<Create>			Create_s;
			typedef std::shared_ptr<ICreate>		ICreate_s;
			typedef std::shared_ptr<OCreate>		OCreate_s;

			typedef std::shared_ptr<Update>			Update_s;
			typedef std::shared_ptr<IUpdate>		IUpdate_s;
			typedef std::shared_ptr<OUpdate>		OUpdate_s;


			/** @brief %Control */
			namespace Control {
				namespace RigidBody {
					class Create;
					class ICreate;
					class OCreate;

					class Update;
					class IUpdate;
					class OUpdate;

					typedef std::shared_ptr<Create>			Create_s;
					typedef std::shared_ptr<ICreate>		ICreate_s;
					typedef std::shared_ptr<OCreate>		OCreate_s;

					typedef std::shared_ptr<Update>			Update_s;
					typedef std::shared_ptr<IUpdate>		IUpdate_s;
					typedef std::shared_ptr<OUpdate>		OUpdate_s;

				}
			}
		}
	}
}

#endif

