CC := g++
CFLAGS := -std=c++17 -Iinc -Wall -Werror -Wno-reorder

OBJS := request.o handler.o
OBJS := $(addprefix obj/, $(OBJS))

.PHONY: all dir clean

all: dir bin/app.exe

bin/app.exe: $(OBJS) obj/main.o
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.cpp inc/*
	$(CC) $(CFLAGS) -o $@ -c $<

dir: obj bin

obj bin:
	mkdir -p $@

clean:
	rm -rf obj bin
