#!/usr/bin/env python

import subprocess

command = ["make"]

proc = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
(out, err) = proc.communicate()
print "program output:", out

