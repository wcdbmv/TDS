CFLAGS := -Wall -Werror -std=c99 -pedantic

ifeq ($(mode), debug)
	CFLAGS += -g3
else ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

app.exe: bigfloat.o info.o interface.o main.o
	gcc -o $@ $^

test.exe: bigfloat.o test.o
	gcc -o $@ $^

%.o: %.c *.h
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o *.exe 2>/dev/null
