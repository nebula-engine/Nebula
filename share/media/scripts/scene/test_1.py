
scene = neb.createSceneDLL("hf/libnebula_ext_hf_0.so")


#typedef neb::core::core::actor::rigiddynamic::desc actor_desc;

actor_desc* ad = new actor_desc;

auto actor = scene->createActorRigidDynamic(ad).lock();

cuboid_desc = neb.shape.cuboid.Desc(1,1,1)

auto shape = actor->createShapeCuboid(neb::core::core::shape::cuboid::desc(glm::vec3(1))).lock();

#shape->createLightSpot(glm::vec3(0,0,-1));

actor->_M_name = std::string("player");

print neb.getScenes()

