
def create_maze(app, window, context):
	
        #auto app = neb::fin::app::base::global();

	# create map

	#scene = loadXML<scene_t>(NEB_SHARE_DIR"/media/scenes/scene.xml");
        #app->neb::core::core::scene::util::parent::insert(scene);
        #scene->init(app.get());
        #std::dynamic_pointer_cast<actor_dyn_t>(scene->neb::core::core::actor::util::parent::map_.find("player"));

        #scene = app.createSceneDLL("maze/build/libnebula_ext_maze.so")
        scene = app.createScene()

	#::maze::description<D> desc(size_);
	#::maze::dfs<D> m(desc);
	#m.run();
	
	#float width = 5.0;
	
	#auto lambda = [&] (::maze::traits<D>::vec v) {
	#	auto actor = createActorRigidStaticCube(neb::fnd::math::pose(v), width);
	#};
	
	#for(int i = 0; i < prod<D>(desc.size_); ++i) {
	#	auto v = ::vector<D>(i, desc.size_);
	#	if(!m.get_ispath(v)) {
	#		lambda(::maze::traits<D>::vec(v) * (float)width);
	#	}
	#}
	#// outer walls
	#glm::vec3 pos;
	#glm::vec3 s;
	#for(int d = 0; d < D; d++)
	#{
	#	pos = glm::vec3(
	#			((float)desc.size_[1] - 1.0) / 2.0,
	#			((float)desc.size_[1] - 1.0) / 2.0,
	#			((float)desc.size_[2] - 1.0) / 2.0
	#		     );
        #		s = glm::vec3(desc.size_);
	#	s[d] = 1.0;
		#pos[d] = -1;
	#	createActorRigidStaticCuboid(neb::fnd::math::pose(pos * width), s * width);
	#	pos[d] = (float)desc.size_[0];
	#	createActorRigidStaticCuboid(neb::fnd::math::pose(pos * width), s * width);
	#}

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

	return scene

windows = app.get_windows()

window = windows[0]

context = window.createContextThree()

game = app.createGame()

scene = create_maze(app, window, context)

game.add_scene(scene)
        
context.set_drawable(scene);



