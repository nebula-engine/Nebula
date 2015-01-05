
scene = neb.createSceneDLL("hf/libnebula_ext_hf_0.so")


#typedef neb::core::core::actor::rigiddynamic::desc actor_desc;

#actor_desc* ad = new actor_desc;

actor = scene.createActorRigidDynamic()

cuboid_desc = neb.shape.cuboid.Desc(1,1,1)

shape = actor.createShapeCuboid(cuboid_desc)

#shape->createLightSpot(glm::vec3(0,0,-1));

#actor->_M_name = std::string("player");

print neb.getScenes()

