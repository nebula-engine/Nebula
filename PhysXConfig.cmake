
INCLUDE_DIRECTORIES("/scratch/physx-3.3.1_linux_sdk_core/Include")

LINK_DIRECTORIES("/scratch/physx-3.3.1_linux_sdk_core/Lib/linux64")

SET(PhysX_LIBRARIES
	LowLevelCHECKED
	LowLevelClothCHECKED
	PhysX3CHECKED
	PhysX3CharacterKinematicCHECKED
	PhysX3CommonCHECKED
	PhysX3CookingCHECKED
	PhysX3ExtensionsCHECKED
	PhysX3VehicleCHECKED
	PhysXProfileSDKCHECKED
	PhysXVisualDebuggerSDKCHECKED
	PvdRuntimeCHECKED
	PxTaskCHECKED
	SceneQueryCHECKED
	SimulationControllerCHECKED
	)

#RepX3CHECKED
