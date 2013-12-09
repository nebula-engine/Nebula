
x = 1

file = foo bar

x = $(foreach f, $(file), $(shell expr $(x) + 1))

all:
	@echo $(x)
