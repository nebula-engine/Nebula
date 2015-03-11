app = neb.get_app()
s = app.create_server(20002)
c = app.create_client("127.0.0.1", 20002)

print s
print c

c.send("hello");

