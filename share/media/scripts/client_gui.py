app = neb.get_app()

c = app.create_client("127.0.0.1", 20002)

m = neb.net.msg.Code()

m.set_code(neb.net.msg.codes.REQUEST_GAME_LIST)

c.send("hi")
c.send("hi")

