
windows = app.get_windows()

window = windows[0]

context = window.createContextThree()

game = app.createGame()

m = game.create_map_dll("../mod/maze/build/dynamic/libnebula_ext_maze.so")

scene = app.create_scene()

m.set_scene(scene)

#createActorLightPoint(glm::vec3(0,0,10));

#actor_hf = scene.createActorHeightField()

scene.createLightPoint()

actor_player = scene.createActorRigidDynamicCuboid()

#assert(actor_player);

#// weapon
#if(window0 && actor_player)
#{

weap = actor_player.createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0)

# camera

actor_player.createControlManual(window)

environ = context.get_environ().is_environ_scene_base()

environ.create_view_ridealong(actor_player)

context.set_drawable(scene);



