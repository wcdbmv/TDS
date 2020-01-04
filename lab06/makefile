CC := g++
CFLAGS := -std=c++17 -Iinc -Wall -Werror -Wno-multichar

OBJS := avl_tree_node binary_tree_node display hash_table interface
OBJS := $(addsuffix .o, $(OBJS))
OBJS := $(addprefix obj/, $(OBJS))

.PHONY: all dir clean

all: dir bin/app.exe

bin/app.exe: $(OBJS) obj/main.o
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.cpp inc/%.h
	$(CC) $(CFLAGS) -o $@ -c $<

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

dir: obj bin

obj bin:
	mkdir -p $@

clean:
	rm -rf obj bin 2>/dev/null
