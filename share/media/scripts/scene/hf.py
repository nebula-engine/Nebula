
def create_maze(app, window, context):
	
        #auto app = neb::fin::app::base::global();

	# create map

	#scene = loadXML<scene_t>(NEB_SHARE_DIR"/media/scenes/scene.xml");
        #app->neb::core::core::scene::util::parent::insert(scene);
        #scene->init(app.get());
        #std::dynamic_pointer_cast<actor_dyn_t>(scene->neb::core::core::actor::util::parent::map_.find("player"));

        scene = app.createSceneDLL("hf/build/libnebula_ext_hf.so")
       
        actor_hf = scene.createActorHeightField()

        scene.createLightPoint()

        actor_player = scene.createActorRigidDynamicCube()

	
	#assert(actor_player);
	
	#// weapon
	#if(window0 && actor_player)
        #{
        
	weap = actor_player.createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0)

	# camera

	actor_player.createControlManual(window)

	environ = context.getEnviron().isSceneDefault()

	environ.createViewridealong(actor_player)

	#}	
	#//	light->initShadow(environ1);

	#//create_enemy();


	return scene


#window = app.createWindow()
windows = app.get_windows()

window = windows[0]

context1 = window.createContextThree()
#context2 = window.createContextTwo()
        
#layout = app.createLayout(window, context2)
        
#gameDesc = neb.core.game.game.Desc()
        #game = app->createGame(gameDesc);

game = app.createGame()
        
# scene

scene = create_maze(app, window, context1)

game.setScene(scene)
        
context1.setDrawable(scene);


