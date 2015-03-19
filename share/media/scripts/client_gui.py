app = neb.get_app()


c0 = neb.net.msg.Codes.REQUEST_GAME_LIST
c1 = neb.net.msg.Codes.REQUEST_GAME_JOIN

m0 = neb.net.msg.Code()
m1 = neb.net.msg.Code()

m0.set_code(c0)

m1.set_code(c1)
m1.set_data(6)


def after_connect(c):
    print "after connect"
    c.send(m0)

def after_m0_response(m, c):
    print "m0 response"
    print m
    c.send(m1)

m0.set_func_after_response(after_m0_response)

c = app.create_client("127.0.0.1", 20002, after_connect)


