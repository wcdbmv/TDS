CC := g++
CFLAGS := -std=c++17 -Iinc -Wall -Werror -Wno-reorder

OBJS := calculator.o
OBJS := $(addprefix obj/, $(OBJS))

.PHONY: all dir clean parser test_stack test_register_operations

all: dir bin/app.exe

bin/app.exe: $(OBJS) obj/interface.o
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.cpp inc/%.h inc/* src/parser.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

dir: obj bin

obj bin:
	mkdir -p $@

clean:
	rm -rf obj bin
