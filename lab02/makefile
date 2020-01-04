CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic
LDFLAGS = -s -pipe
OBJS := country.o info.o interface.o table.o
OBJS := $(addprefix obj/, $(OBJS))

.PHONY: all dirs clean copy

all: dirs app.exe

app.exe: $(OBJS) obj/main.o
	$(CC) $(LDFLAGS) -o bin/$@ $^

obj/%.o: src/%.c inc/%.h
	$(CC) $(CFLAGS) -Iinc -o $@ -c $<

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -Iinc -o $@ -c $<

dirs: obj bin

obj bin:
	mkdir -p $@

clean:
	rm -rf *.o *.exe obj bin 2>/dev/null

copy:
	cp dbt/* db
