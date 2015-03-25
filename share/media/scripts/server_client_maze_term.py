# create game
gd = neb.game.game.Desc()
gd.net_type = 1

game = app.createGame(gd)

m = game.create_map_dll("../mod/maze/build/dynamic/libnebula_ext_maze.so")

scene = m.create_scene()

print "0"

# server stuff

app.create_server_1(20000)

print "1"

# client stuff

c0 = neb.net.msg.Codes.REQUEST_GAME_LIST
c1 = neb.net.msg.Codes.REQUEST_GAME_JOIN
print "2"

m0 = app.create_msg_code()
m1 = app.create_msg_code()
print "3"

m0.set_code(c0)

m1.set_code(c1)
#m1.set_data(15)
print "1"

def after_connect(c):
    print "after connect"
    c.send(m0)

def after_m0_response(m, c):
    print "m0 response"
    print m
    print c
    lst = m.get_list()
    for l in lst:
        print l.p,l.i
    
    if lst:
        l = lst[0]
        m1.set_data(l)
        c.send(m1)
    else:
        print "no games"

print "1"
m0.set_func_after_response(after_m0_response)
print "1"

c = app.create_client("127.0.0.1", 20000, after_connect)

print "2"

# gui stuff

windows = app.get_windows()

window = windows[0]

context = window.createContextWindow()

environ = context.create_environ_scene_default()



actor_player = scene.createActorRigidDynamicCuboid()

m.spawn_actor(actor_player);

weap = actor_player.createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0)

control = actor_player.createControlManual(window)




environ.create_view_ridealong(actor_player)

environ.set_drawable(scene);

print "script complete"

