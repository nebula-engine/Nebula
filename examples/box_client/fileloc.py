import sys
#print len(sys.argv)

if len(sys.argv) < 4:
	print "usage fileloc.py <fliename> <string> <loc>"
	sys.exit()

f = open(sys.argv[1],'r')

str = sys.argv[2]

loc = int(sys.argv[3])

line_num = 1

start = 0

for line in f:
	if start == 0:
		if str in line:
			print line
			start = 1
	
	if start == 1:
		if len(line) > loc:
			col_num = loc
			break
		loc -= len(line)
	
	line_num += 1

print "%i:%i" % ( line_num, col_num )

