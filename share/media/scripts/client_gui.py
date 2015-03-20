app = neb.get_app()


c0 = neb.net.msg.Codes.REQUEST_GAME_LIST
c1 = neb.net.msg.Codes.REQUEST_GAME_JOIN

m0 = app.create_msg_code()
m1 = app.create_msg_code()

m0.set_code(c0)

m1.set_code(c1)
#m1.set_data(15)

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

m0.set_func_after_response(after_m0_response)

c = app.create_client("127.0.0.1", 20002, after_connect)


