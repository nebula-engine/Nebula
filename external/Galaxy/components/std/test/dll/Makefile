
all:
	g++ -fPIC -shared myclass1.cc -o myclass1.so
	g++ -fPIC -shared myclass2.cc -o myclass2.so
	g++ -Wl,-rpath,. class_user.cc -ldl -o class_user
	
clean:
	rm -f myclass1.so myclass2.so class_user
