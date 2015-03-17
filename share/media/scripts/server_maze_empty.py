
# create game
gd = neb.game.game.Desc()
gd.net_type = 1

game = app.createGame(gd)

m = game.create_map_dll("../mod/maze/build/dynamic/libnebula_ext_maze.so")

scene = m.create_scene()


# server stuff

app.create_server(20002)

#client stuff

app.test()

