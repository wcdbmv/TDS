CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic
OBJS := io_ext.o dir_ext.o single_linked_list.o sparse_matrix.o matrix.o interface.o info.o
OBJS := $(addprefix obj/, $(OBJS))

ifeq ($(mode), release)
	CFLAGS += -g0 -DNDEBUG
endif

.PHONY: all clean dirs report _report

all: dirs app.exe

app.exe: $(OBJS) obj/main.o
	$(CC) -Iinc -o bin/$@ $^

test.exe: $(OBJS) obj/test.o
	$(CC) -Iinc -o bin/$@ $^

obj/%.o: src/%.c inc/%.h
	$(CC) $(CFLAGS) -Iinc -o $@ -c $<

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -Iinc -o $@ -c $<

dirs: obj bin

obj bin:
	mkdir -p $@

report:
	make -s _report

_report:
	echo "Works only if you have typora"
	echo "[file -> export -> PDF]"
	cd doc && typora report.md 2>/dev/null

clean:
	rm -rf obj bin 2>/dev/null
